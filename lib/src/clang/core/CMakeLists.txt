
add_library(InstRO_clang_core SHARED ClangConstruct
																		 ClangPassFactory)
																		
target_add_instro_compile_options(InstRO_clang_core)
target_include_directories(InstRO_clang_core PUBLIC ${Boost_INCLUDE_DIRS})
target_add_instro_flags(InstRO_clang_core)