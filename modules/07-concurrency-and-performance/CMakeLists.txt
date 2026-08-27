# Phase 7: Concurrency and performance

add_demo_executable(threads threads/threads.cpp)
add_demo_executable(async async/async.cpp)
add_demo_executable(volatile volatile/volatile.c)
add_demo_executable(timing timing/timing.cpp)
add_demo_executable(synchronization synchronization/synchronization.cpp)

# This compiles, but doesn't do anything anymore. Google Chrome also warns you that it's not supported.
add_demo_executable(visual_benchmarking
    visual-benchmarking/instrumentor.h
    visual-benchmarking/visual_benchmarking.cpp)
