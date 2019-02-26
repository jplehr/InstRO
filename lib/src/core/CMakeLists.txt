

add_library(InstRO_core SHARED ConstructSet
														ConstructTraitType
														PassImplementation
														SimplePassManager
														Singleton)

target_include_directories(InstRO_core PUBLIC ${Boost_INCLUDE_DIRS})
target_add_instro_flags(InstRO_core)
target_add_instro_compile_options(InstRO_core)
