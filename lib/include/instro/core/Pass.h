#ifndef INSTRO_CORE_PASS_H
#define INSTRO_CORE_PASS_H

#include <map>
#include <string>
#include <iostream>
#include <cassert>

#include <vector>
#include <unordered_map>

#include "instro/core/ConstructSet.h"
#include "instro/core/PassExecuter.h"
#include "instro/core/PassImplementation.h"

#include "instro/core/ConstructSetManagement.h"
#include "instro/core/ConstructLevelManagrment.h"

namespace InstRO {
/* PassFactory: Interface for the mandatory InstRO Passes. */
namespace PassManagement {
class PassManager;
}

/*
 * The Pass class is the administration class used within the pass manager.
 * It holds information necessary in order to singalize the pass implementation
 * whether it can be run or not.
 * Also it exposes a clear interface to the PassManager
 */

class Pass : public InstRO::Core::PassConstructSetManagement, public InstRO::Core::ConstructLevelManagement {
 public:
	//CI empty pass construction disallowed. Each Pass is an container for the corresponding PassImplementation Object from the ToolingSpace
	Pass() = delete;
	Pass(PassImplementation *pImpl): 
		passImplementation(pImpl),
		passInitialized(false),
		passExecuted(false),
		passFinalize(false),
		passOutputReleased(false),
		inputReady(false){
	};
	PassImplementation *getPassImplementation() { return passImplementation; };
	~Pass() {
		delete (passImplementation);
		passImplementation = NULL;
	}
	//CI: Tell the pass, that is is allowed to initialize itself
	void initPass();
	//CI: Execute the pass, this generates the output-constructset
	void executePass();

//CI: Refactoring to remove the Executor stuff|	void execute(InstRO::PassManagement::PassExecuter *executer);

	void finalizePass();
	
//2015-06-19 - Deprecated:	void releaseOutput();

	// CI: Enable Input is called externally to indicate, that  the input passes
	// have beend processed and that the current pass can now use the
	// getInput(Pass*) to obtain the construct sets of its predecessors
	void setInputEnabled() { inputReady = true; };
	// CI: Disable Input is called externally to indicate, that the input passes
	// have cleared their internal state AND their output construct set such that
	// the
	//     getInput(Pass*) does not provide a vaild construct set. The provided
	//     construct set may no longer be used as it could have been deallocated
	void setInputDisabled() { inputReady = false; };
	// CI: queryFunction to determin, if the input is enabled
	bool isInputEnabled() { return true; };
	bool isOutputEnabled() { return passExecuted && !passOutputReleased; }

	// Info Functions:
	bool providesOutput() { return passProvidesOutputFlag; }
	bool requiresInput() { return passRequiresInputFlag; }
	void setProvidesOutput(bool value = true) { passProvidesOutputFlag = value; };
	void setRequiresInput(bool value = true) { passRequiresInputFlag = value; };

	virtual std::string passName() { return passNameString; };
	void setPassName(std::string passName) { passNameString = passName; };

	void setOutputLevel(Core::ConstructLevelType level) { outputLevel = level; };
	Core::ConstructLevelType getOutputLevel() { return outputLevel; };

	void registerInputPass(Pass *pass, Core::ConstructLevelType level) {
		inputPasses.push_back(pass);
		setInputLevelRequirement(pass, level);
	}

	std::vector<Pass *> getInputPasses() { return inputPasses; };

	void setInputLevelRequirement(Pass *pass, Core::ConstructLevelType level) { inputRequiredLevels[pass] = level; }

	Core::ConstructLevelType getInputLevelRequirement(Pass *pass) { return inputRequiredLevels[pass]; };

 private:
	bool passRequiresInputFlag, passProvidesOutputFlag;
	bool passInitialized, passExecuted, passFinalize, passOutputReleased;
	bool inputReady;
	std::string passNameString;

	PassImplementation *passImplementation;

	std::vector<Pass *> inputPasses;
	Core::ConstructLevelType outputLevel;
	std::unordered_map<Pass *, Core::ConstructLevelType> inputRequiredLevels;
};
//}// Core
}	// InstRO
#endif
