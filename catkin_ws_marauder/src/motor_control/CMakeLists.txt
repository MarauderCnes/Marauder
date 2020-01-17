cmake_minimum_required(VERSION 2.8.3)
project(motor_control)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_library(wiringPi_LIB wiringPi)
find_library(wiringPi_LIB softPwm)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES motor_control
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)
link_directories(/usr/local/include /usr/include)

add_executable(driver src/driver.cpp src/driver.h src/marauder.cpp src/marauder.h)
target_link_libraries(driver ${catkin_LIBRARIES} ${wiringPi_LIB} -lrt python2.7 pthread wiringPiPca9685)
