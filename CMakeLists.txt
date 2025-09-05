cmake_minimum_required(VERSION 3.15)
project(cpp-demo)

set(CMAKE_CXX_STANDARD 23)

# Put all build products under the chosen build dir
# e.g. cmake-build-debug/bin, cmake-build-debug/lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(any modules/any/any.cpp)
add_executable(arrays modules/arrays/arrays.cpp)
add_executable(async modules/async/async.cpp)
add_executable(binary_operators modules/binary-operators/binary_operators.cpp)
add_executable(call_location modules/call-location/call_location.cpp)
add_executable(casting modules/casting/casting.cpp)
add_executable(class-visibility modules/class-visibility/class_visibility.cpp)
add_executable(const modules/const/const.cpp)
add_executable(copy modules/copy/copy.cpp)
add_executable(delegating_constructor modules/delegating-constructor/delegating_constructor.cpp)

add_executable(doubly_linked_list
    modules/doubly-linked-list/doubly_linked_list.h
    modules/doubly-linked-list/doubly_linked_list.cpp
    modules/doubly-linked-list/main.cpp)

# shared library (Linux) / dynamic link library (Windows)
add_library(shared_library SHARED modules/shared-library/shared_library.cpp modules/shared-library/shared_library.h)
target_include_directories(shared_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/shared-library)
add_executable(shared_library_app modules/shared-library-app/shared_library_app.cpp)
target_link_libraries(shared_library_app PRIVATE shared_library)

add_executable(enum modules/enum/enum.cpp)
add_executable(evaluation_order modules/evaluation-order/evaluation_order.cpp)
add_executable(exceptions modules/exceptions/exceptions.cpp)
add_executable(expected modules/expected/expected.cpp)
add_executable(files modules/files/files.cpp)
add_executable(format modules/format/format.cpp)
add_executable(function_pointers modules/function-pointers/function_pointers.cpp)

add_executable(hash_table
    modules/hash-table/hash_table.h
    modules/hash-table/hash_table.cpp
    modules/hash-table/main.cpp)

add_executable(hello modules/hello/hello.cpp)
add_executable(instantiation modules/instantiation/instantiation.cpp)
add_executable(iterators modules/iterators/iterators.cpp)
add_executable(lambda modules/lambda/lambda.cpp)
add_executable(lvalue-rvalue modules/lvalue-rvalue/lvalue-rvalue.cpp)

add_executable(macros modules/macros/macros.h modules/macros/macros.cpp)
target_compile_definitions(macros PUBLIC MY_VALUE=3)

add_executable(malloc modules/malloc/malloc_demo.cpp)
add_executable(maps modules/maps/maps.cpp)
add_executable(member_initialization modules/member-initialization/member_initialization.cpp)
add_executable(memory_tracker modules/memory-tracker/memory_tracker.cpp)
add_executable(move modules/move/move.cpp)
add_executable(multidimensional_arrays modules/multidimensional-arrays/multidimensional_arrays.cpp)
add_executable(namespace_collision modules/namespace-collision/namespace_collision.cpp)
add_executable(operator_overload modules/operator-overload/operator_overload.cpp)
add_executable(optional modules/optional/optional.cpp)
add_executable(pointers modules/pointers/pointers.cpp)
add_executable(popcount modules/popcount/popcount.cpp)

# precompiled-headers
add_executable(precompiled-headers modules/precompiled-headers/precompiled-headers.cpp)
target_precompile_headers(precompiled-headers PRIVATE modules/precompiled-headers/pch.h)

add_executable(project_configuration modules/project-configuration/project_configuration.cpp)
add_executable(references modules/references/references.cpp)
add_executable(scope modules/scope/scope.cpp)
add_executable(scratch modules/scratch/scratch.cpp)
add_executable(singleton modules/singleton/singleton.cpp)
add_executable(sorting modules/sorting/sorting.cpp)

add_executable(static
    modules/static/external_variables.cpp
    modules/static/header_with_static.h
    modules/static/static.cpp)

# static-library
add_library(static_library STATIC modules/static-library/static_library.cpp modules/static-library/static_library.h)
target_include_directories(static_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/static-library)
add_executable(static_library_app modules/static-library-app/static-library-app.cpp)
target_link_libraries(static_library_app PRIVATE static_library)

add_executable(string_demo modules/string-demo/string_demo.cpp)
add_executable(templates modules/templates/templates.cpp)
add_executable(threads modules/threads/threads.cpp)
add_executable(timing modules/timing/timing.cpp)
add_executable(tuples modules/tuples/tuples.cpp)
add_executable(type_parameter_extension modules/type-parameter-extension/type_parameter_extension.cpp)
add_executable(unions modules/unions/unions.cpp)
add_executable(variant modules/variant/variant.cpp)
add_executable(virtual_functions modules/virtual-functions/virtual-functions.cpp)
add_executable(virtual-member-variables modules/virtual-member-variables/virtual_member_variables.cpp)

# This compiles, but doesn't do anything anymore. Google Chrome also warns you that it's not supported.
add_executable(visual_benchmarking
    modules/visual-benchmarking/instrumentor.h
    modules/visual-benchmarking/visual_benchmarking.cpp)

add_executable(volatile modules/volatile/volatile.c)
