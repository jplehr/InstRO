
# Build the supporting infrastructure library for the tests
add_library(InstRO_clang_test lib/TestAdapter.cpp)

target_include_directories(InstRO_clang_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${instro_include_path})
target_compile_options(InstRO_clang_test PUBLIC ${instro_default_options})


function(add_instro_flags target)
  target_include_directories(${target} PUBLIC ${instro_include_path} ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
  target_compile_options(${target} PUBLIC ${instro_default_options})

  target_link_libraries(${target} InstRO_clang_test InstRO ${instro_compiler_L_items} LLVMSupport ${Boost_LIBRARIES})
endfunction()

# Build the test case binary
add_executable(ConstructHierarchySelectionTest ConstructHierarchySelectionTestMain)
add_executable(BooleanCompoundSelectorTest BooleanCompoundSelectorTest)
add_executable(CallpathSelectorTest CallpathSelectorTest)
add_executable(ConstructElevatorSelectorTest ConstructElevatorSelectorTest)
#add_executable(DefaultInstrumentationAdapterTest DefaultInstrumentationAdapterTest)
add_executable(IdentifierSelectorTest IdentifierSelectorTest)

add_instro_flags(ConstructHierarchySelectionTest)
add_instro_flags(BooleanCompoundSelectorTest)
add_instro_flags(CallpathSelectorTest)
add_instro_flags(ConstructElevatorSelectorTest)
#add_instro_flags(DefaultInstrumentationAdapterTest)
add_instro_flags(IdentifierSelectorTest)