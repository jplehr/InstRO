cmake_minimum_required(VERSION 3.5)

project(InstRO)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Clang REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)
find_package(Boost REQUIRED COMPONENTS system iostreams program_options)

string(REGEX REPLACE "clang-format|clang-import-test|clang-rename|clang-refactor|clang-reorder-fields|modularize|clang-tidy|clangd" "" CLANG_EXPORTED_TARGETS "${CLANG_EXPORTED_TARGETS}")

set(instro_compiler_I_items "${LLVM_INCLUDE_DIRS}")
set(instro_compiler_L_items "${CLANG_EXPORTED_TARGETS}")


# Standard compile options InstRO uses
set(instro_default_options -std=c++14 -Werror=return-type)
set(instro_include_path "${CMAKE_SOURCE_DIR}/lib/include" "${CMAKE_BINARY_DIR}/lib/include")

# We add the compiler-dependent includes to the include path
list(APPEND instro_include_path "${instro_compiler_I_items}")


message(STATUS "Used Includes: " ${instro_include_path})
message(STATUS "Clang: " ${Clang_DIR})
message(STATUS "Boost: " ${Boost_INCLUDE_DIRS})
message(STATUS "Back-end I-items: " ${instro_compiler_I_items})
message(STATUS "Back-end L-items: " ${instro_compiler_L_items})


# To select the Compiler backend InstRO wants to use
# TODO As soon as we port the Rose build to CMake, we need to make this configurable
set(INSTRO_USE_CLANG True)

# Whether we can use exceptions
set(INSTRO_DISABLE_EXCEPTIONS False)

# Generate the needed lib/include/instro/config.h file
configure_file(cconfig.h.in ${CMAKE_BINARY_DIR}/lib/include/instro/config.h)

# Process the subsequent directories
add_subdirectory(lib)
add_subdirectory(support)
add_subdirectory(test)
add_subdirectory(examples)
