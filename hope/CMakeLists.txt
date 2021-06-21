cmake_minimum_required(VERSION 2.8.3)
project(hope)

add_definitions(-std=c++11)






find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
  message_generation
  camera_info_manager
  dynamic_reconfigure
)
add_message_files(FILES moter_msg.msg mode_msg.msg sign_msg.msg)

generate_messages(
	DEPENDENCIES 
	std_msgs 
	sensor_msgs
	)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

#generate_dynamic_reconfigure_options(
#/ cfg/cam.cfg
#)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES hope
  CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs std_msgs camera_info_manager dynamic_reconfigure
  DEPENDS system_lib
)




include_directories(
 include
  ${catkin_INCLUDE_DIRS} 
  ${OpenCV_INCLUDE_DIRS}
)

#add_executable(hope_node src/hope_node.cpp)
#target_link_libraries(hope_node ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES})




add_executable(hope_sub_node src/hope_sub_node.cpp)
target_link_libraries(hope_sub_node ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES})
#add_dependencies(hope_sub_node beginner_tutorials_generate_messages_cpp)
#add_dependencies(hope_sub_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#add_dependencies(hope_sub_node hope_generate_messages_cpp)
#add_dependencies(hope_node can_dynamix_generate_messages_cpp)

add_executable(sub_node src/sub_node.cpp)
target_link_libraries(sub_node ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} -lv4l2 -ludev)
add_dependencies(sub_node ${PROJECT_NAME}_gencfg)
#add_dependencies(hope_node can_dynamix_generate_messages_cpp)

#add_executable(traffic_sign src/traffic_sign.cpp)
#target_link_libraries(traffic_sign ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} -lv4l2 -ludev)

add_dependencies(sub_node ${PROJECT_NAME}_gencfg)
#add_dependencies(hope_node can_dynamix_generate_messages_cpp)
add_library(traffic_sign_lib src/Gradient.cpp)

add_executable(traffic src/traffic.cpp)
target_link_libraries(traffic ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} -lv4l2 -ludev)

add_executable(feature src/feature4.cpp)
target_link_libraries(feature ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} )

add_executable(video src/video_node.cpp)
target_link_libraries(video ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} )

add_executable(redrec src/redrec.cpp)
target_link_libraries(redrec ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} )

add_executable(detect src/detect.cpp)
target_link_libraries(detect ${catkin_LIBRARIES}  ${OpenCV_LIBRARIES} ${Boost_LIBRARIES} )



