#ifndef INSTRO_CLANG_TOOLING_CLANG_ANALYSIS_INTERFACE_H
#define INSTRO_CLANG_TOOLING_CLANG_ANALYSIS_INTERFACE_H

#include "instro/tooling/AnalysisInterface.h"

#include "instro/clang/tooling/ClangConstructTraitInterface.h"
#include "instro/clang/tooling/ClangNamedConstructAccess.h"

namespace InstRO {
namespace Clang {
namespace Tooling {

class ClangAnalysisManager : public InstRO::Tooling::AnalysisManager {
 public:
  ClangAnalysisManager(clang::ASTContext &context)
      : cti(new ConstructTraitInterface::ClangConstructTraitInterface(context)),
        nca(new NamedConstructAccess::ClangNamedConstructAccess(context)) {}
  ClangAnalysisManager() = delete;
  virtual ~ClangAnalysisManager() {}

  virtual InstRO::Tooling::ExtendedCallGraph::ExtendedCallGraph *getECG() override { return nullptr; }
  virtual InstRO::Tooling::ControlFlowGraph::ControlFlowGraph *getCFG() override { return nullptr; }
  virtual InstRO::Tooling::ConstructElevator::ConstructElevator *getCSElevator() override { return nullptr; }
  virtual InstRO::Tooling::ConstructTraitInterface::ConstructTraitInterface *getConstructTraitInterface() override {
    return cti.get();
  }
  virtual InstRO::Tooling::NamedConstructAccess::NamedConstructAccess *getNamedConstructAccessFacility() override {
    return nca.get();
  }

 protected:
  std::unique_ptr<ConstructTraitInterface::ClangConstructTraitInterface> cti;
  std::unique_ptr<NamedConstructAccess::ClangNamedConstructAccess> nca;
};
}  // namespace Tooling
}  // namespace Clang
}  // namespace InstRO

#endif  // INSTRO_CLANG_TOOLING_CLANG_ANALYSIS_INTERFACE_H
