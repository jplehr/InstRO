

add_library(InstRO_pass SHARED adapter/ConstructPrinterAdapter
												adapter/DefaultInstrumentationAdapter
												selector/BooleanCompoundSelector
												selector/CallPathSelector
												selector/ConstructTraitSelector
												selector/ElevatorSelector
												selector/IdentifierMatcherSelector
												selector/ProgramEntrySelector)

target_add_instro_compile_options(InstRO_pass)
target_include_directories(InstRO_pass PUBLIC ${Boost_INCLUDE_DIRS})

target_add_instro_flags(InstRO_pass)
