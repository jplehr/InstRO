
find_package(Clang REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)

string(REGEX REPLACE "clang-format|clang-import-test|clang-rename|clang-refactor|clang-reorder-fields|modularize|clang-tidy|clangd" "" CLANG_EXPORTED_TARGETS "${CLANG_EXPORTED_TARGETS}")

set(instro_compiler_I_items "${LLVM_INCLUDE_DIRS}")
set(instro_compiler_L_items "${CLANG_EXPORTED_TARGETS}" LLVMSupport)

# To select the Compiler backend InstRO wants to use
set(INSTRO_USE_CLANG True)