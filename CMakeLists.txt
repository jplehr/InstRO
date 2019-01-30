cmake_minimum_required(VERSION 3.5)

project(InstRO)

option(use_clang_backend "whether to use the clang backend" ON)
option(use_rose_backend "whether to use the ROSE backend" OFF)


list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/config/cmake)

if(${use_clang_backend})
  include(clang_toolchain)
elseif(${use_rose_backend})
  include(rose_toolchain)
else()
  message(FATAL_ERROR " Need to use one compiler: Either use Clang or use ROSE.")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Boost is required for all builds [maybe we should consider getting rid of it?]
find_package(Boost REQUIRED COMPONENTS system iostreams program_options)

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


# Whether we can use exceptions
set(INSTRO_DISABLE_EXCEPTIONS False)

# Generate the needed lib/include/instro/config.h file
configure_file(cconfig.h.in ${CMAKE_BINARY_DIR}/lib/include/instro/config.h)

# Process the subsequent directories
add_subdirectory(lib)
add_subdirectory(support)
add_subdirectory(test)
add_subdirectory(examples)
