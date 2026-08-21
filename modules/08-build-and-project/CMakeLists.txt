# Phase 8: Build system and project structure

add_demo_executable(project_configuration project-configuration/project_configuration.cpp)

add_demo_executable(macros macros/macros.h macros/macros.cpp)
target_compile_definitions(macros PUBLIC MY_VALUE=3)

add_demo_executable(call_location call-location/call_location.cpp)

# precompiled-headers
add_demo_executable(precompiled-headers precompiled-headers/precompiled-headers.cpp)
target_precompile_headers(precompiled-headers PRIVATE precompiled-headers/pch.h)

# static-library
add_demo_library(static_library STATIC static-library/static_library.cpp static-library/static_library.h)
target_include_directories(static_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/static-library)
add_demo_executable(static_library_app static-library-app/static-library-app.cpp)
target_link_libraries(static_library_app PRIVATE static_library)

# shared library (Linux) / dynamic link library (Windows)
add_demo_library(shared_library SHARED shared-library/shared_library.cpp shared-library/shared_library.h)
target_include_directories(shared_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/shared-library)
add_demo_executable(shared_library_app shared-library-app/shared_library_app.cpp)
target_link_libraries(shared_library_app PRIVATE shared_library)

# On Windows the app needs the DLL next to its exe, so copy it there after each build.
add_custom_command(TARGET shared_library_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:shared_library> $<TARGET_FILE_DIR:shared_library_app>)
