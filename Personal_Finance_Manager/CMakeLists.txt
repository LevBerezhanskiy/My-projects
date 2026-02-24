cmake_minimum_required(VERSION 3.16)

project(QtKursovaya VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(QtKursovaya
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui


    transactions.c
    transactions.h
    server.h
)

target_include_directories(QtKursovaya PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(QtKursovaya PRIVATE Qt::Widgets)

if(WIN32)
    target_link_libraries(QtKursovaya PRIVATE ws2_32)
endif()

set_target_properties(QtKursovaya PROPERTIES
    WIN32_EXECUTABLE TRUE
)

add_executable(server_exe_target
    server_main.c
    server.c
    transactions.c
)

target_include_directories(server_exe_target PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    target_link_libraries(server_exe_target PRIVATE ws2_32)
endif()

set_target_properties(server_exe_target PROPERTIES OUTPUT_NAME "server")
