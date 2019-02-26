

add_library(InstRO_util SHARED BWLFileReader
														CommandlineHandling
														#ConfigurationLoader # This needs rapidJSON
														Environment
														Logger)

target_include_directories(InstRO_util PUBLIC ${Boost_INCLUDE_DIRS})

target_add_instro_flags(InstRO_util)

target_add_instro_compile_options(InstRO_util)
target_link_libraries(InstRO_util PUBLIC ${Boost_LIBRARIES})

