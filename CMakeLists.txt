cmake_minimum_required(VERSION 3.10)
project(dungeon_editor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основное приложение
add_executable(dungeon_editor
    src/main.cpp
    src/npc.cpp
    src/npc_factory.cpp
    src/visitor.cpp
    src/observer.cpp
    src/battle.cpp
)

target_include_directories(dungeon_editor PRIVATE include)

# Тесты (опционально)
if(BUILD_TESTS)
    find_package(GTest REQUIRED)
    
    add_executable(tests
        tests/test_npc.cpp
        tests/test_battle.cpp
    )
    
    target_include_directories(tests PRIVATE include)
    target_link_libraries(tests GTest::gtest GTest::gtest_main dungeon_editor)
    
    enable_testing()
    add_test(NAME NPCTests COMMAND tests)
endif()