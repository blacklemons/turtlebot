#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <stdio.h>  
#include "geometry_msgs/PoseStamped.h"
#include <termios.h>  
#include <unistd.h>
#include <moter_pub/mode_msg.h>    
  
float x,y;

void poseCallback(const geometry_msgs::Pose::ConstPtr& msg)
{
      x = msg->position.x;
	printf("x = %f\n",x);
      y = msg->position.y;
	printf("y = %f\n",y);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "motor_publisher");
  ros::NodeHandle nh1;
  ros::NodeHandle nh2;
  ros::Subscriber pose_sub = nh1.subscribe("robot_pose", 10,poseCallback);
  ros::Publisher mode_pub = nh2.advertise<moter_pub::mode_msg>("/mode",10);
  ros::Rate loop_rate(10);
  moter_pub::mode_msg msg;
  

  int k=0;
  while(ros::ok())
  {
    ros::spinOnce();

 if(x<-0.11 && x>-1.13 && y <-1.74 && y>-1.76)
    {
       msg.mode = 1;
       msg.cnt = 0;
       mode_pub.publish(msg);
    }
    loop_rate.sleep();

  }

}
