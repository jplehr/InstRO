#ifndef INSTRO_UTILITY_ENVIRONMENT_H
#define INSTRO_UTILITY_ENVIRONMENT_H

// This holds definitions from configure -- important for convenience ;)
//#include "instro/config.h"

#include <string>
#include <fstream>
#include <iostream>

#include "boost/filesystem.hpp"
#include "instro/utility/Logger.h"

#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

namespace InstRO {
namespace Utility {

/* Reads the content of the passed environment variable and returns it as a string. */
std::string getEnvironmentVariable(std::string envVar);
/** Returns the configure-time installation directory of the instro library */
std::string getInstroInstallationPathname();
/** Returns the configure-time runtime library path (either prefix or build directory) */
std::string getInstroRTLibraryPathname();
/** Returns the configure-time include path (either prefix or source directory) */
std::string getInstroRTIncludePathname();

///@cond
//** Should be used internally - if absolutely necessary. Executes a programm (assumed to be in PATH) and returns the
// output in a string */
template <typename... T>
void runExecutable(std::string progName, T... args) {
	auto pID = fork();
	// no child process created
	if (pID == -1) {
		throw std::string("Forking went wrong");
	}

	if (pID == 0) {
		// child - replace the image with another program
		int err = execlp(progName.c_str(), progName.c_str(), (args.c_str())..., NULL);
		if (err == -1) {
			// if returned error
			logIt(ERROR) << "Running sub program. Msg: " << std::string(strerror(errno)) << std::endl;
			exit(-1);
		}
		exit(0);	// exit child process if no error occured
	} else {
		// parent
		int status;
		if (waitpid(pID, &status, 0) == -1) {
			throw std::string("Waiting for child process went wrong...");
		}
	}
}

/// @cond
template <typename... T>
std::string runExecutableAndReturnResult(T... args) {
	// TODO Generate unique file name with pid
	std::string instroTempFile(".instro_tmp_out");
	try {
		runExecutable(args...);

		std::ifstream in(instroTempFile);

		if (!in.is_open()) {
			logIt(ERROR) << "Was not able to open file" << std::endl;
		}

		std::string line;
		std::getline(in, line);
		in.close();
		std::remove(instroTempFile.c_str());

		return line;
	} catch (std::string &s) {
		logIt(ERROR) << s << std::endl;
	}

	return std::string();
}

/** Executes and retrieves the output for the scorep-config */
template<typename T>
T getScorepIncludeFlags() {
	auto version = runExecutableAndReturnResult(std::string("/bin/sh"), std::string("-c"),
																							std::string("scorep-config --version > .instro_tmp_out"));

	std::string cxxFlags("--cxxflags");	// for scorep 1.4.2
	if (version.compare("1.2.2") == 0) {
		cxxFlags = std::string(" --cppflags");
	}

	auto s = runExecutableAndReturnResult(std::string("/bin/sh"), std::string("-c"),
																				std::string("scorep-config " + cxxFlags + " > .instro_tmp_out"));
	return s;
}
}
}
#endif
