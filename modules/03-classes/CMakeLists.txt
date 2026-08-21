# Phase 3: Classes and object-oriented design

add_demo_executable(instantiation instantiation/instantiation.cpp)
add_demo_executable(class-visibility class-visibility/class_visibility.cpp)
add_demo_executable(member_initialization member-initialization/member_initialization.cpp)
add_demo_executable(delegating_constructor delegating-constructor/delegating_constructor.cpp)

add_demo_executable(static
    static/external_variables.cpp
    static/header_with_static.h
    static/static.cpp)

add_demo_executable(operator_overload operator-overload/operator_overload.cpp)
add_demo_executable(virtual_functions virtual-functions/virtual-functions.cpp)
add_demo_executable(virtual-member-variables virtual-member-variables/virtual_member_variables.cpp)
add_demo_executable(singleton singleton/singleton.cpp)
add_demo_executable(namespace_collision namespace-collision/namespace_collision.cpp)
