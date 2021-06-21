#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <stdio.h>
#include <moter_pkg/moter_msg.h>  
  
int speed=0;
float angle=0;
char stats, keep =0;
int cnt = 0;

void msgCallback(const moter_pkg::moter_msg::ConstPtr& msg1)
{
  //ROS_INFO("receive msg speed = %d",msg1->speed);
  speed = (msg1->speed);
  //ROS_INFO("receive msg angular = %f",msg1->angle);
  if(((msg1->angle) > -2.84 )&&((msg1->angle) < 2.84))
    angle = (msg1->angle);
  cnt = 1;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "motor_main");
  ros::NodeHandle nh1;
  ros::NodeHandle nh2;
  ros::Publisher cmd_pub = nh1.advertise<geometry_msgs::Twist>("/cmd_vel",5);
  ros::Subscriber sign = nh2.subscribe("/cmd_sign",10, msgCallback);
  ros::Rate loop_rate(10);
  geometry_msgs::Twist msg;

  int ch;

  while(ros::ok())
  {
    ros::spinOnce();

    if(cnt==1)
    {
      
    msg.angular.z = -angle;

    switch(speed)
    {
      case 4:
	msg.linear.x = 0.17;
        break;
      
      case 2:
	msg.linear.x = 0.01;
        break;
      case 1:
	msg.linear.x = 0.17;
        break;
      case 0:
	msg.linear.x = 0;
        break;
      case -1:
	msg.linear.x = -0.05;
        break;
        
    }

        // linear.x = (-0.22 ~ 0.22), angular.z = (-2.84 ~ 2.84)
    cmd_pub.publish(msg);
    //printf("linear.x = %.2f, angular.z = %f \n\n", msg.linear.x, msg.angular.z);
    }
    cnt = 0;
    loop_rate.sleep();
  }
  return 0;

}
