#include "instro/clang/ClangInstrumentor.h"
#include "instro/clang/core/ClangConsumerFactory.h"
#include "instro/clang/support/ClangHelpers.h"
#include "instro/utility/MemoryManagement.h"

#include "instro/core/Singleton.h"
#include "instro/utility/exception.h"

InstRO::Clang::ClangInstrumentor::ClangInstrumentor(int argc, const char **argv, llvm::cl::OptionCategory &llvmThing)
    : argc(argc),
      argv(argv),
      cop(argc, argv, llvmThing, llvm::cl::NumOccurrencesFlag::Optional),
      tool(cop.getCompilations(), cop.getSourcePathList()) {
  InstRO::setInstrumentorInstance(this);
}

InstRO::Clang::ClangPassFactory *InstRO::Clang::ClangInstrumentor::getFactory(CompilationPhase phase) {
  if (clangPassFactory == nullptr) {
    auto repls = InstRO::Clang::Support::mergeToolReplacements(tool);
    // Move to C++14
    clangPassFactory = std::make_unique<ClangPassFactory>(passManager, repls);
  }
  return clangPassFactory.get();
}

clang::tooling::RefactoringTool &InstRO::Clang::ClangInstrumentor::getTool() { return tool; }

void InstRO::Clang::ClangInstrumentor::apply() {
  std::cout << "Preparing to run Clang tool" << std::endl;

  auto repls = InstRO::Clang::Support::mergeToolReplacements(tool);
  InstRO::Clang::Support::ClangConsumerFactory f(passManager, repls, getFactory());

  if(modify) {
    tool.runAndSave(clang::tooling::newFrontendActionFactory<InstRO::Clang::Support::ClangConsumerFactory>(&f).get());
  } else {
    std::cout << "Running in non-modifying context." << std::endl;
    tool.run(clang::tooling::newFrontendActionFactory<InstRO::Clang::Support::ClangConsumerFactory>(&f).get());
  }
}

void InstRO::Clang::ClangInstrumentor::initializeAnalysisManager(clang::ASTContext &context) {
  clangAnalysisManager = std::make_unique<InstRO::Clang::Tooling::ClangAnalysisManager>(context);
}

InstRO::Tooling::AnalysisManager *InstRO::Clang::ClangInstrumentor::getAnalysisManager() {
  if (!clangAnalysisManager) {
    InstRO::raise_exception("AnalysisManager has not yet been initialized");
  }

  return clangAnalysisManager.get();
}
