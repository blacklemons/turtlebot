cmake_minimum_required(VERSION 2.8.3)
project(mode_second)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  message_generation
  geometry_msgs
  std_msgs
)

add_message_files(FILES mode_msg.msg)

generate_messages(DEPENDENCIES std_msgs geometry_msgs)

catkin_package(
  #INCLUDE_DIRS include
  LIBRARIES mode_second
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs message_runtime
  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(mode_main2 src/mode_main2.cpp)
target_link_libraries(mode_main2 ${catkin_LIBRARIES})
add_dependencies(mode_main2 ${mode_second}_EXPORTED_TARGETS ${catkin_EXPORTED_TARGETS})



