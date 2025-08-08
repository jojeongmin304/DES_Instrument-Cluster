cmake_minimum_required(VERSION 3.16)

project(AnalogInstrumentCluster VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(AnalogInstrumentCluster
    main.cpp
    mainwindow.cpp
    mainwindow.h
    speedometer.cpp
    speedometer.h
    rpmgauge.cpp
    rpmgauge.h
)

target_link_libraries(AnalogInstrumentCluster Qt6::Widgets)
