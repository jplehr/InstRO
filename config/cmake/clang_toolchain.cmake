
find_package(Clang REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)

string(REGEX REPLACE "clang-format|clang-import-test|clang-rename|clang-refactor|clang-reorder-fields|modularize|clang-tidy|clangd" "" CLANG_EXPORTED_TARGETS "${CLANG_EXPORTED_TARGETS}")

set(instro_compiler_I_items "${LLVM_INCLUDE_DIRS}")
set(instro_compiler_L_items "${CLANG_EXPORTED_TARGETS}")

# To select the Compiler backend InstRO wants to use
# TODO As soon as we port the Rose build to CMake, we need to make this configurable
set(INSTRO_USE_CLANG True)