
#include "instro/clang/support/ClangHelpers.h"

clang::tooling::Replacements InstRO::Clang::Support::mergeToolReplacements(clang::tooling::RefactoringTool &tool) {
  clang::tooling::Replacements repls;
  for (const auto &rPairs : tool.getReplacements()) {
    repls = repls.merge(rPairs.second);
  }

  return repls;
}

std::string InstRO::Clang::Support::addTopLevelNameQualification(const std::string &identifier) {
  std::string newIdentifier = "::" + identifier;
  return newIdentifier;
}