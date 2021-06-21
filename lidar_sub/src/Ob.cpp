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
#include <lidar_sub/mode_msg.h>

using namespace std;
int Ob_start = 0, Ob_ing = 0, mode = 1,Obstacle = 0, cnt = 0;

void modeJudgCallback(const lidar_sub::mode_msg::ConstPtr& msg1)
{
  mode = msg1->mode;
  cnt = msg1->cnt;
}



void lidarJudgCallback(const sensor_msgs::LaserScan::ConstPtr& scanVal) 
{
   
  int angle_F, count=0;
  float length, angle_rad, x, y, z, sum=0, average=0;
  
   for (angle_F = 350; angle_F < 360; angle_F++) {   // 앞의 장애물 발견
    length = 100*(float)((scanVal->ranges[angle_F]));  //m -> cm로 단위 변환
    //printf("ranges[%d] = %f\n",angle_L,length); 
    if((length >2.f)&&(length < 40.f)){
      sum += length;
      count++;
      } 
 }
  average = sum/count;
  //printf("%f",average);
  if(mode==1&&cnt==4&&average<35){
    Ob_start = 1 ;
   }
}


int main(int argc, char **argv)
{
   ros::init(argc,argv,"Ob");
   ros::NodeHandle nh1;
   ros::NodeHandle nh2;
   ros::NodeHandle nh3;
   ros::NodeHandle nh4;
   
   ros::Rate loop_rate(10);

   ros::Publisher cmd_pub = nh3.advertise<lidar_sub::Lidartest>("/cmd_sign",10);
   ros::Publisher mode_pub = nh4.advertise<lidar_sub::mode_msg>("/mode",10); 
   ros::Subscriber ros_sub = nh1.subscribe("scan", 10, lidarJudgCallback);
   ros::Subscriber mode_sub = nh2.subscribe("/mode", 10, modeJudgCallback);  
  
   
   lidar_sub::Lidartest msg;
   lidar_sub::mode_msg msg1;
   
   int sleep = 0;
   
   while (ros::ok())
   {
     ros::spinOnce();
	     if(Ob_start == 1 && Ob_ing == 0)
	      {
		 Obstacle = 1, Ob_ing = 1;
	      }
	      if(Obstacle == 6) //직진 
	      {
		      cnt = 0;
		      mode = 1;
		      mode_pub.publish(msg1);
	      }
	      if(Obstacle == 5) //직진 
	      {
		msg.speed = 4;
		Obstacle = 6;
		msg.angle = 0;
		sleep = 28;
	      }
	      
	      if(Obstacle == 4) //오른쪽으로 회전
	      {
		msg.speed = 0;
		msg.angle = 0.5;
		sleep = 28;
		Obstacle = 5;
	      }
	      
	      if(Obstacle == 3) //직진 
	      {
		msg.speed = 4;
		msg.angle = 0;
		sleep = 30;
		Obstacle = 4;
	      }
	      
	      if(Obstacle == 2) //왼쪽으로 회전
	      {
		msg.speed = 0;
		msg.angle = -0.4;
		sleep = 17;
		Obstacle = 3;
	      }
	      
	      if(Obstacle == 1) //멈춤 
	      {
		msg.speed = 0;
		msg.angle = 0;
		sleep = 0;
		Obstacle =2;
	      }
	     
	      
	     if(Ob_ing == 1)
		cmd_pub.publish(msg);
	      
	     for(int i=0; i<sleep; i++)
	     {
	       loop_rate.sleep();  //1초간 멈춤
	     }
	     sleep = 0;
     }
   return 0;
   
}
