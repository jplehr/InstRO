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
    // std::cout << "ConstructCollector::VisitFunctionDecl" << std::endl;
    if (fDecl->isThisDeclarationADefinition()) {
      auto name = fDecl->getQualifiedNameAsString();
      auto lIdentifier = InstRO::Clang::Support::addTopLevelNameQualification(name);
      processIdentifier(lIdentifier, fDecl);
      // std::cout << "ConstructCollector::VisitFunctionDecl END" << std::endl;
    }

    return true;
  }

  bool VisitCallExpr(clang::CallExpr *ce) {
    auto target = ce->getCalleeDecl();
    // std::cout << "ConstructCollector::VisitCallExpr" << std::endl;
    if (target && llvm::dyn_cast<clang::NamedDecl>(target)) {
      auto targetND = llvm::dyn_cast<clang::NamedDecl>(target);
      auto identifier = targetND->getQualifiedNameAsString();
      auto lIdentifier = InstRO::Clang::Support::addTopLevelNameQualification(identifier);
      processIdentifier(lIdentifier, ce);
    }
    return true;
  }

  bool VisitVarDecl(clang::VarDecl *decl) {
    // std::cout << "ConstructCollector::VisitVarDecl" << std::endl;
    if (decl->hasInit()) {
      auto identifier = decl->getQualifiedNameAsString();
      processIdentifier(identifier, decl);

      auto init = decl->getInit();
      // Account for foldable expressions, the isEvaluatable bails our with some assertion. I'm not sure how to fix.
      // XXX FOR NOW: We consider an expression without side effects not interesting
      if (!init->HasSideEffects(ctx)) {
        // FIXME how to call *init->isEvaluatable* without triggering various asserts?
        // if (init->isRValue() || init->getType()->hasPointerRepresentation() || init->isEvaluatable(ctx)) {
        return true;
      }

      processIdentifier(identifier, init);
    }
    return true;
  }

  // FIXME: Not working.
  bool VisitDeclRefExpr(clang::DeclRefExpr *expr) {
    // std::cout << "ConstructCollector::VisitDeclRefExpr Enter" << std::endl;
    auto decl = expr->getDecl();
    auto identifier = decl->getNameAsString();
    // std::cout << "ConstructCollector::VisitDeclRefExpr -> Identifier: " << identifier << std::endl;
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