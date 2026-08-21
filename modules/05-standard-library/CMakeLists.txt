# Phase 5: The standard library

add_demo_executable(maps maps/maps.cpp)

add_demo_executable(hash_table
    hash-table/hash_table.h
    hash-table/hash_table.cpp
    hash-table/main.cpp)

add_demo_executable(doubly_linked_list
    doubly-linked-list/doubly_linked_list.h
    doubly-linked-list/doubly_linked_list.cpp
    doubly-linked-list/main.cpp)

add_demo_executable(tuples tuples/tuples.cpp)
add_demo_executable(sorting sorting/sorting.cpp)
add_demo_executable(popcount popcount/popcount.cpp)
add_demo_executable(format format/format.cpp)
