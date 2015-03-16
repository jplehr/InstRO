#include "instro/clang/support/InstROASTConsumer.h"

InstRO::Clang::Support::InstROASTConsumer::InstROASTConsumer(
		::InstRO::Core::PassManagement::PassManager *passManager)
		: passManager(passManager) {}

		InstRO::Clang::Support::InstROASTConsumer::InstROASTConsumer(InstRO::Core::PassManagement::PassManager *passManager, InstRO::Clang::Core::PassManagement::ClangPassExecuter *executer) : passManager(passManager), executer(executer){

		}

		
void InstRO::Clang::Support::InstROASTConsumer::HandleTranslationUnit(
		clang::ASTContext &context) {
	// Is invoked on every TranslationUnit
	// invoke all passes in the correct order per TranslationUnit
	// We delegate to the pass manager. But before we set the executer
	std::cout << "Set Executer object @ " << executer << " from within InstROASTConsumer" << std::endl;
//	passManager->setExecuter(new InstRO::Clang::Core::PassManagement::ClangPassExecuter(&context));
	executer->setASTContext(&context);
	std::cout << "Calling execute in PassManager" << std::endl;
	passManager->execute();
}

