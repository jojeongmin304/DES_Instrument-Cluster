# Minimum version of CMake required
cmake_minimum_required(VERSION 3.16)

# Project name and language
project(IC_Project VERSION 0.1 LANGUAGES CXX)

# Use the C++17 standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Automatically run Qt's MOC, RCC, and UIC tools when needed
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the necessary Qt6 components.
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml Network)

qt_standard_project_setup(REQUIRES 6.8)

# Define the executable target.
# We will now add the .qrc files directly here.
qt_add_executable(appIC_Project
    src/main.cpp
    src/speedprovider.cpp
    src/cangatewayclient.cpp
    
    # ADDED: Directly add resource files to the executable.
    # This is the most reliable way to ensure they are compiled in.
    qml.qrc
    image.qrc
)

# Define the QML module for your application.
# The RESOURCES section has been removed from here.
qt_add_qml_module(appIC_Project
    URI IC_Project
    VERSION 1.0
    QML_FILES
        Main.qml
        InstrumentCluster.qml
        Gear.qml
        LeftCluster.qml
        RightCluster.qml
    SOURCES
        src/speedprovider.h src/speedprovider.cpp
        src/cangatewayclient.h src/cangatewayclient.cpp
)

# Tell CMake where to find our own header files and the json.hpp header.
target_include_directories(appIC_Project PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link the required Qt libraries to your application.
target_link_libraries(appIC_Project
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::Qml
        Qt6::Network
)

# --- This section is for macOS and Windows packaging ---
set_target_properties(appIC_Project PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# --- This section is for creating an installer ---
include(GNUInstallDirs)
install(TARGETS appIC_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# # Minimum version of CMake required
# cmake_minimum_required(VERSION 3.16)

# # Project name and language
# project(IC_Project VERSION 0.1 LANGUAGES CXX)

# # Statically link libstdc++ to make the binary more portable
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")

# # Use the C++17 standard
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD 17)

# # Automatically run Qt's MOC, RCC, and UIC tools when needed
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)

# # Find the necessary Qt6 components.
# # We've added Core, Gui, and Network to the existing 'Quick'.
# find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml Network)

# qt_standard_project_setup(REQUIRES 6.8)

# # Define the executable target.
# # All C++ source files should be listed here.
# qt_add_executable(appIC_Project
#     src/main.cpp
#     src/speedprovider.cpp
#     src/cangatewayclient.cpp
# )

# # Define the QML module for your application.
# # The SOURCES list now includes the gateway client.
# qt_add_qml_module(appIC_Project
#     URI IC_Project
#     VERSION 1.0
#     QML_FILES
#         Main.qml
#         InstrumentCluster.qml
#         Gear.qml
#         LeftCluster.qml
#         RightCluster.qml
#     RESOURCES
#         image.qrc
#         qml.qrc
#     SOURCES
#         src/speedprovider.h src/speedprovider.cpp
#         src/cangatewayclient.h src/cangatewayclient.cpp
# )

# # Tell CMake where to find our own header files and the json.hpp header.
# target_include_directories(appIC_Project PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

# # Link the required Qt libraries to your application.
# # We've added Core, Gui, and Network.
# target_link_libraries(appIC_Project
#     PRIVATE
#         Qt6::Core
#         Qt6::Gui
#         Qt6::Quick
#         Qt6::Qml
#         Qt6::Network
# )

# # --- This section is for macOS and Windows packaging and can be left as is ---
# set_target_properties(appIC_Project PROPERTIES
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# # --- This section is for creating an installer and can be left as is ---
# include(GNUInstallDirs)
# install(TARGETS appIC_Project
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
# ---------------------------------------------
# cmake_minimum_required(VERSION 3.16)

# project(IC_Project VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# #add .qrc files as sources to executable or library

# set(CMAKE_AUTORCC ON)


# find_package(Qt6 REQUIRED COMPONENTS Quick)

# qt_standard_project_setup(REQUIRES 6.8)

# qt_add_executable(appIC_Project
#     image.qrc
#     qml.qrc
#     main.cpp
# )

# qt_add_qml_module(appIC_Project
#     URI IC_Project
#     VERSION 1.0
#     QML_FILES
#         Main.qml
#         InstrumentCluster.qml
#         Gear.qml
#         LeftCluster.qml
#         RightCluster.qml
#     RESOURCES
#         image.qrc
#         qml.qrc
#         SOURCES speedprovider.h speedprovider.cpp
# )

# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# set_target_properties(appIC_Project PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appIC_Project
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# target_link_libraries(appIC_Project
#     PRIVATE Qt6::Quick
# )

# include(GNUInstallDirs)
# install(TARGETS appIC_Project
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
