cmake_minimum_required(VERSION 2.8.3)
project(marauder_2dnav)

## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  motor_control
  tuto_tf
  sick_tim
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES marauder_2dnav
#  CATKIN_DEPENDS motor_control tuto_tf sick_tim
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

