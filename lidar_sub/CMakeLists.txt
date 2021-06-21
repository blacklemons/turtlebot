cmake_minimum_required(VERSION 2.8.3)
project(lidar_sub)


find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  sensor_msgs
  pcl_ros
)

  find_package(PCL REQUIRED COMPONENTS COMMON io)
  

  add_message_files(FILES Lidartest.msg mode_msg.msg)
  
  generate_messages(DEPENDENCIES std_msgs sensor_msgs) 

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES lidar_sub
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs pcl_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
  ${PCL_INCLUDE_DIRS}
)

add_executable(lidar_subscriber src/lidar_subscriber.cpp)

target_link_libraries(lidar_subscriber ${catkin_LIBRARIES} ${PCL_LIBRARYS} )

add_dependencies(lidar_subscriber ${lidar_sub}_EXPORTED_TARGETS ${catkin_EXPORTED_TARGETS})

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(Ob src/Ob.cpp)

target_link_libraries(Ob ${catkin_LIBRARIES} ${PCL_LIBRARYS} )

add_dependencies(Ob ${lidar_sub}_EXPORTED_TARGETS ${catkin_EXPORTED_TARGETS})
