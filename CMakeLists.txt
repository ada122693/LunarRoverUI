cmake_minimum_required(VERSION 3.5)

project(LunarRoverUI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(OpenCV REQUIRED COMPONENTS core imgproc videoio)
find_package(gazebo QUIET)
find_package(rclcpp QUIET)
find_package(std_msgs QUIET)
find_package(nav_msgs QUIET)
find_package(sensor_msgs QUIET)
find_package(geometry_msgs QUIET)

if(gazebo_FOUND AND rclcpp_FOUND)
  add_definitions(-DGAZEBO_SUPPORT)
  message(STATUS "Gazebo simulation support enabled")
else()
  message(STATUS "Gazebo libraries not found - simulation support disabled")
endif()

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/gui_manager.cpp
    src/gui_manager.h
    src/splash_screen.cpp
    src/splash_screen.h
    src/simulation_bridge.h
    src/simulation_bridge.cpp
    src/gui_sections/status_section.h
    src/gui_sections/status_section.cpp
    src/gui_sections/camera_section.h
    src/gui_sections/camera_section.cpp
    src/gui_sections/objectives_section.h
    src/gui_sections/objectives_section.cpp
    src/gui_sections/location_section.h
    src/gui_sections/location_section.cpp
    src/gui_sections/overrides_section.h
    src/gui_sections/overrides_section.cpp
    resources.qrc
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets ${OpenCV_LIBS})

if(gazebo_FOUND AND rclcpp_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GAZEBO_LIBRARIES}
    rclcpp::rclcpp
    std_msgs::std_msgs
    nav_msgs::nav_msgs
    sensor_msgs::sensor_msgs
    geometry_msgs::geometry_msgs
  )
endif()
