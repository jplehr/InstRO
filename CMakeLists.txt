cmake_minimum_required(VERSION 3.5)

project(InstRO LANGUAGES CXX)

# We want to include the helper cmake files we create
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/config/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/config/cmake/modules)
include(common)

# The options to select which compiler should be used when building InstRO
option(USE_CLANG_BACKEND "whether to use the clang backend" OFF)
option(USE_ROSE_BACKEND "whether to use the ROSE backend" OFF)


if(${USE_CLANG_BACKEND})
  include(clang_toolchain)
  message(STATUS "Running clang build")
elseif(${USE_ROSE_BACKEND})
  include(rose_toolchain)
  message("Running ROSE Build")
else()
  message(FATAL_ERROR " Need to use one compiler: Either use Clang or use ROSE.")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Boost is required for all builds [maybe we should consider getting rid of it?]
find_package(Boost REQUIRED COMPONENTS system iostreams program_options)

# Standard compile options InstRO uses
set(CMAKE_CXX_STANDARD 17)

set(instro_include_path "${CMAKE_SOURCE_DIR}/lib/include" "${CMAKE_BINARY_DIR}/lib/include")

# We add the compiler-dependent includes to the include path
list(APPEND instro_include_path "${instro_compiler_I_items}")


message(STATUS "Used Includes: " ${instro_include_path})
message(STATUS "Clang: " ${Clang_DIR})
message(STATUS "ROSE: " ${ROSE_DIR})
message(STATUS "Boost: " ${Boost_INCLUDE_DIRS})
message(STATUS "Back-end I-items: " ${instro_compiler_I_items})
message(STATUS "Back-end L-items: " ${instro_compiler_L_items})


# Whether we can use exceptions
set(INSTRO_DISABLE_EXCEPTIONS False)

# Generate the needed lib/include/instro/config.h file
configure_file(cconfig.h.in ${CMAKE_BINARY_DIR}/lib/include/instro/config.h @ONLY)

# Process the subsequent directories
add_subdirectory(lib)
add_subdirectory(support)
add_subdirectory(test)
add_subdirectory(examples)
