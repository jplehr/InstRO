
add_library(InstRO_clang_adapter SHARED ClangCygProfileAdapter
																	ClangMangledNameOutputAdapter)


target_add_instro_compile_options(InstRO_clang_adapter)
target_include_directories(InstRO_clang_adapter PUBLIC ${Boost_INCLUDE_DIRS})

target_add_instro_flags(InstRO_clang_adapter)