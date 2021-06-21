#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <iostream>
#include <sensor_msgs/PointCloud2.h>
//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <std_msgs/UInt16.h>
#include "std_msgs/String.h"
#include "stdio.h"
#include <lidar_sub/Lidartest.h>


using namespace std;
int turn;

//int row_step, height;

void lidarJudgCallback(const sensor_msgs::LaserScan::ConstPtr& scanVal) 
{
   
  int angle_L, count=0;
  float length, angle_rad, x, y, z, sum=0, average=0;
  
  
  
   for ( angle_L = 350; angle_L < 360; angle_L++) {   // 전방 우측면 30도각 탐지
    length = 100*(float)((scanVal->ranges[angle_L]));  //m -> cm로 단위 변환
    printf("ranges[%d] = %f\n",angle_L,length); 
    if((length >2.f)&&(length < 50.f)){
      sum += length;
      count++;
      } 
 }
  average = sum/count;
  //printf("%f",average);
  /*if(average<25){
    turn = 1;
   }

   else 
    turn = 0; */ 


  printf("\n");

}



int main(int argc, char **argv)
{
  ros::init(argc,argv,"lidar_subscriber");
  ros::NodeHandle nh;
  
  ros::NodeHandle nh3;
  
  ros::Publisher scan_pub = nh3.advertise<sensor_msgs::LaserScan>("/scan_front",10); 
  ros::Subscriber ros_sub = nh.subscribe("scan", 10, lidarJudgCallback);
  

  lidar_sub::Lidartest msg;
  msg.speed=1;

  
  while (ros::ok())
  {
  ros::spinOnce();

    
  }

  return 0;
}


