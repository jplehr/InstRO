

add_library(InstRO_tooling  SHARED ConstructElevator
														ControlFlowGraph
														ExtendedCallGraph
														IdentifierProvider
														NamedConstructAccess)

target_add_instro_compile_options(InstRO_tooling)

target_include_directories(InstRO_tooling PUBLIC ${Boost_INCLUDE_DIRS})

target_add_instro_flags(InstRO_tooling)
