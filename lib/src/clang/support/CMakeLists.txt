
add_library(InstRO_clang_support SHARED ClangConsumerFactory
                                                                                                                                        InstROASTConsumer
                                                                                                                                        ClangHelpers)


target_add_instro_compile_options(InstRO_clang_support)
target_include_directories(InstRO_clang_support PUBLIC ${Boost_INCLUDE_DIRS})
target_add_instro_flags(InstRO_clang_support)