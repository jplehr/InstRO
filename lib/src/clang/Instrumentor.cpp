#include "llvm/Support/CommandLine.h"
#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/CommonOptionsParser.h"

#include "instro/clang/ClangInstrumentor.h"

/*
 * This is meant as something where one can simply look up
 * syntax and to check whether instantiations would compile :)
 */

static llvm::cl::OptionCategory MyTool("my tool");

int main(int argc, char **argv) {
	std::cout << "Start" << std::endl;
	InstRO::Clang::ClangInstrumentor instro(argc, const_cast<const char **>(argv), (void*)&MyTool);
	auto fac = instro.getFactory();
	auto fDefSel = fac->createFunctionDefinitionSelector();
	fac->createCygProfileAdapter(fDefSel);
	instro.apply();
	std::cout << "End" << std::endl;
	return 0;
}