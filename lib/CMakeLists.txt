# Process part-libraries
if(INSTRO_USE_CLANG)
    add_subdirectory(src/clang)
elseif(INSTRO_USE_ROSE)
	add_subdirectory(src/rose)
endif()
add_subdirectory(src/core)
add_subdirectory(src/pass)
add_subdirectory(src/tooling)
add_subdirectory(src/utility)

# The InstRO library
add_library(InstRO SHARED src/Instrumentor 
											src/Pass 
											src/PassFactory)

target_add_instro_flags(InstRO)
target_include_directories(InstRO PUBLIC ${Boost_INCLUDE_DIRS})
target_add_instro_compile_options(InstRO)


target_link_libraries(InstRO PUBLIC InstRO_core
																		InstRO_pass 
																		InstRO_util 
																		InstRO_tooling
																		${Boost_LIBRARIES})
if(INSTRO_USE_CLANG)
  target_link_libraries(InstRO PUBLIC InstRO_clang )
endif()
