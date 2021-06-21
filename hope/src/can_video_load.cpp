#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <stdio.h>
#include <sstream> // for converting the command line parameter to integer

int main(int argc, char** argv)
{
  // Check if video source has been passed as a parameter
///  if(argv[1] == NULL) return 1;

  ros::init(argc, argv, "video_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/video", 1);

  // Convert the passed as command line parameter index for the video device to an integer
///  std::istringstream video_sourceCmd("2.mp4");
///  std::istringstream video_sourceCmd(argv[1]);
  int video_source;
  // Check if it is indeed a number
///  if(!(video_sourceCmd >> video_source)) return 1;
///      ROS_INFO("2 ");
///  cv::VideoCapture cap(video_source);
  cv::VideoCapture cap(0);

  // Check if video device can be opened with the given index
  if(!cap.isOpened()) { 
      ROS_ERROR("unable open video file ");
	return 1; 
  }


  cv::Mat frame;
  sensor_msgs::ImagePtr msg;

/* /---

double fps = 5;
int fourcc = CV_FOURCC('X','V','I','D'); // codec (opencv3.0이하)
bool isColor = true;

cv::VideoWriter *video = new VideoWriter;
if(!video->open("result.avi", fourcc, fps, cv::Size(frame.rows, frame.cols), isColor)){
//cv::delete video;
//return;
}

*/


  ros::Rate loop_rate(5);
  while (nh.ok()) {
    cap >> frame;
    // Check if grabbed frame is actually full with some content
    if(!frame.empty()) {
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
      pub.publish(msg);
//      ROS_INFO("video out ");
 //     cv::waitKey(1);
     
    }
//    ROS_INFO("--- ");
    ros::spinOnce();
    loop_rate.sleep();
  }
}
