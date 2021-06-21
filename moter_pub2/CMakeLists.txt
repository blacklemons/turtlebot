cmake_minimum_required(VERSION 2.8.3)
project(moter_pub2)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  message_generation
  geometry_msgs
  std_msgs
)


generate_messages(DEPENDENCIES std_msgs geometry_msgs)

catkin_package(
  #INCLUDE_DIRS include
  LIBRARIES moter_pub2
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs message_runtime
  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(moter_publisher2 src/moter_publisher2.cpp)
target_link_libraries(moter_publisher2 ${catkin_LIBRARIES})
add_dependencies(moter_publisher2 ${moter_pub2}_EXPORTED_TARGETS ${catkin_EXPORTED_TARGETS})



