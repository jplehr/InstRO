
add_library(InstRO_clang_tooling SHARED ClangConstructTraitInterface
                                        ClangNamedConstructAccess)


target_compile_options(InstRO_clang_tooling PUBLIC ${instro_default_options})
target_include_directories(InstRO_clang_tooling PUBLIC ${instro_include_path} "${Boost_INCLUDE_DIRS}")
