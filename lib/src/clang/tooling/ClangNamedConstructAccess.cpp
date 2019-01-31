#include "instro/clang/tooling/ClangNamedConstructAccess.h"
#include "instro/clang/core/ClangConstruct.h"
#include "instro/clang/support/ClangHelpers.h"

#include "clang/AST/RecursiveASTVisitor.h"

#include <iostream>

using namespace InstRO::Core;

namespace {
class ConstructCollector : public clang::RecursiveASTVisitor<ConstructCollector> {
 public:
  ConstructCollector(InstRO::Tooling::NamedConstructAccess::Matcher &m, ConstructSet *cs, clang::ASTContext &context)
      : matcher(m), csci(cs), ctx(context){};

  bool shouldVisitTemplateInstantiations() { return true; }

  /*
  Which parts have identifiers we want to match?
  - Functions (definitions, call expr, ?)
  - Variables (definitions?, usages?)
  - Class names (Maybe not?)
  - ?
  */
  bool VisitFunctionDecl(clang::FunctionDecl *fDecl) {
    if (fDecl->isThisDeclarationADefinition()) {
      auto name = fDecl->getQualifiedNameAsString();
      auto lIdentifier = InstRO::Clang::Support::addTopLevelNameQualification(name);
      processIdentifier(lIdentifier, fDecl);
    }

    return true;
  }

  bool VisitCallExpr(clang::CallExpr *ce) {
    auto target = ce->getCalleeDecl();
    if (llvm::dyn_cast<clang::NamedDecl>(target)) {
      auto targetND = llvm::dyn_cast<clang::NamedDecl>(target);
      auto identifier = targetND->getQualifiedNameAsString();
      auto lIdentifier = InstRO::Clang::Support::addTopLevelNameQualification(identifier);
      processIdentifier(lIdentifier, ce);
    }
    return true;
  }

  bool VisitVarDecl(clang::VarDecl *decl) {
    if (decl->hasInit()) {
      auto identifier = decl->getQualifiedNameAsString();
      processIdentifier(identifier, decl);
      if (!decl->getInit()->isEvaluatable(ctx)) {
        processIdentifier(identifier, decl->getInit());
      }
    }
    return true;
  }

  // FIXME: Not working.
  bool VisitDeclRefExpr(clang::DeclRefExpr *expr) {
    auto decl = expr->getDecl();
    auto identifier = decl->getNameAsString();
    std::cout << "Identifier: " << identifier << std::endl;
    processIdentifier(identifier, expr);
    return true;
  }

 private:
  InstRO::Tooling::NamedConstructAccess::Matcher &matcher;
  InstRO::InfrastructureInterface::ConstructSetCompilerInterface csci;
  clang::ASTContext &ctx;

  template <typename ClangNodeT>
  void processIdentifier(std::string &identifier, ClangNodeT *cn) {
    if (matcher.isMatch(identifier)) {
      csci.put(std::make_shared<InstRO::Clang::Core::ClangConstruct>(cn));
    }
  }
};
}  // namespace

using namespace InstRO::Clang::Tooling::NamedConstructAccess;

ConstructSet ClangNamedConstructAccess::getConstructsByIdentifierName(
    InstRO::Tooling::NamedConstructAccess::Matcher &matcher) {
  ConstructSet cs;
  ConstructCollector cc(matcher, &cs, context);
  cc.TraverseDecl(context.getTranslationUnitDecl());
  return cs;
}