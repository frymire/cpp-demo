cmake_minimum_required(VERSION 3.15)
project(cpp-demo)

set(CMAKE_CXX_STANDARD 23)

# The C++23 <print> header needs the terminal helpers in libstdc++exp on MinGW. Optimized
# builds inline std::vprint_unicode into the object file, so the reference only shows up at
# link time in Release, not Debug.
if (MINGW)
  link_libraries(stdc++exp)
endif()

# Demos that read files under resources/ use this to build an absolute path,
# so they run correctly from any working directory.
add_compile_definitions(PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Every target is declared through the helpers below, which place its build
# products in a build-tree directory that mirrors its source directory,
# e.g. <build>/modules/01-basics/hello/hello.exe.
function(demo_set_output_dir target first_source)
  get_filename_component(dir ${first_source} DIRECTORY)
  set_target_properties(${target} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${dir}
      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${dir}
      ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${dir})
endfunction()

function(add_demo_executable name)
  add_executable(${name} ${ARGN})
  demo_set_output_dir(${name} ${ARGV1})
endfunction()

function(add_demo_library name type)
  add_library(${name} ${type} ${ARGN})
  demo_set_output_dir(${name} ${ARGV2})
endfunction()

# The groups form a phased introduction to C++. Work through them in order.
add_subdirectory(modules/01-basics)
add_subdirectory(modules/02-pointers-and-memory)
add_subdirectory(modules/03-classes)
add_subdirectory(modules/04-functions-and-generics)
add_subdirectory(modules/05-standard-library)
add_subdirectory(modules/06-error-handling)
add_subdirectory(modules/07-concurrency-and-performance)
add_subdirectory(modules/08-build-and-project)

# Sandbox for experiments; not part of the learning path.
add_demo_executable(scratch modules/scratch/scratch.cpp)
