#include "ros/ros.h"
#include <stdio.h>  
#include "geometry_msgs/PoseStamped.h"
#include <termios.h>  
#include <unistd.h>
  

void poseCallback(const geometry_msgs::Pose::ConstPtr& msg)
{
	float x,y,z;
      x = msg->position.x;
	printf("x = %f\n",x);
      y = msg->position.y;
	printf("y = %f\n",y);
      z = msg->position.z;
	printf("z = %f\n",z);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "motor_publisher2");
  ros::NodeHandle nh1;
  ros::Subscriber pose_sub = nh1.subscribe("robot_pose", 10,poseCallback);
  ros::Rate loop_rate(10);

  int ch,tunnel;

  while(ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }

}
