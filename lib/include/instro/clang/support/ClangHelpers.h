#ifndef INSTRO_CLANG_SUPPORT_CLANGHELPERS_H
#define INSTRO_CLANG_SUPPORT_CLANGHELPERS_H
#include "clang/Tooling/Refactoring.h"

#include <string>

namespace InstRO {

namespace Clang {
namespace Support {
clang::tooling::Replacements mergeToolReplacements(clang::tooling::RefactoringTool &);

std::string addTopLevelNameQualification(const std::string &identifier);
}  // namespace Support
}  // namespace Clang
}  // namespace InstRO
#endif
