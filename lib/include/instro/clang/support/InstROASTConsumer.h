#ifndef INSTRO_CLANG_SUPPORT_INSTROASTCONSUMER_H
#define INSTRO_CLANG_SUPPORT_INSTROASTCONSUMER_H

#include "clang/AST/ASTConsumer.h"

#include "instro/core/PassManager.h"

namespace InstRO {
namespace Clang {

// forward declaration
class ClangPassFactory;

namespace Support {

/*
 * The class actually used to run InstRO in the Clang world...
 */
class InstROASTConsumer : public clang::ASTConsumer {
 public:
	/* Pass Manager knows when to run which pass */
	InstROASTConsumer(InstRO::PassManagement::PassManager *passManager, InstRO::Clang::ClangPassFactory *fac);

	/* Gets invoked per Translation Unit. Runs all passes, registered in
	 * PassManager on the TranslationUnit */
	void HandleTranslationUnit(clang::ASTContext &context);

 private:
	// This is a raw pointer, since it is a reference to an entity that is owned
	// by the Instrumentor
	InstRO::PassManagement::PassManager *passManager;
	InstRO::Clang::ClangPassFactory *factory;
};
}
}
}

#endif
