#include "instro/clang/tooling/ClangNamedConstructAccess.h"
#include "instro/clang/core/ClangConstruct.h"
#include "instro/clang/support/ClangHelpers.h"

#include "clang/AST/RecursiveASTVisitor.h"

#include <iostream>

using namespace InstRO::Core;

namespace {
class ConstructCollector : public clang::RecursiveASTVisitor<ConstructCollector> {
 public:
  ConstructCollector(InstRO::Tooling::NamedConstructAccess::Matcher &m, ConstructSet *cs) : matcher(m), csci(cs){};

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
      processIdentifier(std::move(name), fDecl);
    }

    return true;
  }

  bool VisitCallExpr(clang::CallExpr *ce) {
    auto target = ce->getCalleeDecl();
    if (llvm::dyn_cast<clang::NamedDecl>(target)) {
      auto targetND = llvm::dyn_cast<clang::NamedDecl>(target);
      auto identifier = targetND->getQualifiedNameAsString();
      processIdentifier(std::move(identifier), ce);
    }
    return true;
  }

  bool VisitVarDecl(clang::VarDecl *decl) {
    if (decl->hasInit()) {
      auto identifier = decl->getQualifiedNameAsString();
      processIdentifier(std::move(identifier), decl);
    }
    return true;
  }

 private:
  InstRO::Tooling::NamedConstructAccess::Matcher &matcher;
  InstRO::InfrastructureInterface::ConstructSetCompilerInterface csci;

  template <typename ClangNodeT>
  void processIdentifier(std::string &&identifier, ClangNodeT *cn) {
    auto lIdentifier = InstRO::Clang::Support::addTopLevelNameQualification(identifier);
    if (matcher.isMatch(lIdentifier)) {
      csci.put(std::make_shared<InstRO::Clang::Core::ClangConstruct>(cn));
    }
  }
};
}  // namespace

using namespace InstRO::Clang::Tooling::NamedConstructAccess;

ConstructSet ClangNamedConstructAccess::getConstructsByIdentifierName(
    InstRO::Tooling::NamedConstructAccess::Matcher &matcher) {
  ConstructSet cs;
  ConstructCollector cc(matcher, &cs);
  cc.TraverseDecl(context.getTranslationUnitDecl());
  return cs;
}