#include "instro/clang/ClangInstrumentor.h"

InstRO::Clang::ClangInstrumentor::ClangInstrumentor(int argc, const char** argv, llvm::cl::OptionCategory& llvmThing)
		: argc(argc), argv(argv), cop(argc, argv, llvmThing), tool(cop.getCompilations(), cop.getSourcePathList()) {}

InstRO::Clang::PassFactory* InstRO::Clang::ClangInstrumentor::getFactory(CompilationPhase phase) {
	if (fac == nullptr) {
		fac.reset(new InstRO::Clang::PassFactory(getPassManager(), tool.getReplacements()));
		//		fac = std::move(t);
	}
	return fac.get();
}

void InstRO::Clang::ClangInstrumentor::init() {}

void InstRO::Clang::ClangInstrumentor::apply() {
	std::cout << "Preparing to run Clang tool" << std::endl;
	InstRO::Clang::Support::ClangConsumerFactory f(getPassManager(), tool.getReplacements(), fac.get());
	tool.runAndSave(clang::tooling::newFrontendActionFactory<InstRO::Clang::Support::ClangConsumerFactory>(&f).get());
}

void InstRO::Clang::ClangInstrumentor::finalize() {}
