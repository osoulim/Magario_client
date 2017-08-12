cmake_minimum_required(VERSION 3.6)
project(Agar_client)

set(CMAKE_CXX_STANDARD 11)

#project directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH /home/mamzi/Qt5.8.0/5.8/gcc_64/)

#find the library
find_package(Qt5Widgets)
find_package(Qt5Network)
find_package(Qt5Multimedia)

set(SOURCE_FILES main.cpp Client.cpp Client.h LGwin.cpp LGwin.h Gamewin.cpp Gamewin.h)
add_executable(Agar_client ${SOURCE_FILES})

target_link_libraries(Agar_client Qt5::Widgets Qt5::Network Qt5::Multimedia)