#include "instro/clang/support/InstROASTConsumer.h"

#include "instro/clang/ClangInstrumentor.h"
#include "instro/clang/ClangPassFactory.h"
#include "instro/clang/core/ClangConstruct.h"
#include "instro/core/Singleton.h"
#define INSTRO_LOG_LEVEL DEBUG
#include "instro/utility/Logger.h"

InstRO::Clang::Support::InstROASTConsumer::InstROASTConsumer(InstRO::PassManagement::PassManager *passManager,
                                                             InstRO::Clang::ClangPassFactory *fac)
    : passManager(passManager), factory(fac) {}

void InstRO::Clang::Support::InstROASTConsumer::HandleTranslationUnit(clang::ASTContext &context) {
  // Is invoked on every TranslationUnit
  // invoke all passes in the correct order per TranslationUnit
  // We delegate to the pass manager. But before we set the executer
  InstRO::Clang::Core::ClangConstruct::setASTContext(context);
  auto CI = static_cast<InstRO::Clang::ClangInstrumentor *>(InstRO::getInstrumentorInstance());
  assert(CI != nullptr && "The InstRO instance is null");
  CI->initializeAnalysisManager(context);
  assert(factory != nullptr && "The InstRO factory is null.");
  factory->finishConstruction(&context);

  logIt(DEBUG) << "Calling execute in PassManager" << std::endl;
  passManager->execute();
}
