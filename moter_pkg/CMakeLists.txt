cmake_minimum_required(VERSION 2.8.3)
project(moter_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  message_generation
  geometry_msgs
  std_msgs
)

add_message_files(FILES moter_msg.msg)

generate_messages(DEPENDENCIES std_msgs geometry_msgs)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES moter_pkg
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs message_runtime
  #DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_executable(moter_main src/moter_main.cpp)
target_link_libraries(moter_main ${catkin_LIBRARIES})
add_dependencies(moter_main ${moter_pkg}_EXPORTED_TARGETS ${catkin_EXPORTED_TARGETS})



