#ifndef INSTRO_CLANG_TOOLING_CLANG_NAMED_CONSTRUCT_ACCESS_H
#define INSTRO_CLANG_TOOLING_CLANG_NAMED_CONSTRUCT_ACCESS_H

#include "instro/core/ConstructSet.h"
#include "instro/tooling/NamedConstructAccess.h"

#include "clang/AST/ASTContext.h"

namespace InstRO {
namespace Clang {
namespace Tooling {
namespace NamedConstructAccess {
class ClangNamedConstructAccess : public InstRO::Tooling::NamedConstructAccess::NamedConstructAccess {
 protected:
  clang::ASTContext &context;

 public:
  ClangNamedConstructAccess(clang::ASTContext &ctx) : context(ctx){};
  ~ClangNamedConstructAccess(){};

  virtual InstRO::Core::ConstructSet getConstructsByIdentifierName(
      InstRO::Tooling::NamedConstructAccess::Matcher &matcher) override;
};
}  // namespace NamedConstructAccess
}  // namespace Tooling
}  // namespace Clang
}  // namespace InstRO
#endif