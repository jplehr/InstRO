
add_library(InstRO_clang_tooling SHARED ClangConstructTraitInterface
                                        ClangNamedConstructAccess)


target_add_instro_compile_options(InstRO_clang_tooling)
target_include_directories(InstRO_clang_tooling PUBLIC ${Boost_INCLUDE_DIRS})
target_add_instro_flags(InstRO_clang_tooling)