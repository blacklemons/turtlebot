#include "ros/ros.h"
//#include "geometry_msgs/Twist.h"
#include <stdio.h>
#include <mode_second/mode_msg.h>
#include "geometry_msgs/PoseStamped.h"
#include <termios.h>  
#include <unistd.h>  

int mode=1,cnt=0;

int getch(void)  
{  
  int ch = '\n';  
  struct termios buf;  
  struct termios save;  
  
   tcgetattr(0, &save);  
   buf = save;  
   buf.c_lflag &= ~(ICANON|ECHO);  
   buf.c_cc[VMIN] = 1;  
   buf.c_cc[VTIME] = 0;  
   tcsetattr(0, TCSAFLUSH, &buf);  
   ch = getchar();  
   tcsetattr(0, TCSAFLUSH, &save);  
   return ch;  


}  

void msgCallback(const mode_second::mode_msg::ConstPtr& msg1)
{
  mode = (msg1->mode);
  cnt = (msg1->cnt);
  printf("receive msg mode = %d\n",msg1->mode);
  printf("receive msg cnt = %d\n",msg1->cnt);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "mode_main2");
  ros::NodeHandle nh1;
  ros::NodeHandle nh2;
  ros::NodeHandle nh3;
  ros::Publisher send_msg = nh1.advertise<mode_second::mode_msg>("/mode",10);
  ros::Subscriber recive_msg = nh2.subscribe("/mode",10, msgCallback);
  ros::Publisher tunnel_pub = nh3.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal",10);
  ros::Rate loop_rate(10);
  geometry_msgs::PoseStamped goal;
  mode_second::mode_msg msg;

  msg.mode = 1;
  msg.cnt = 0;
  
  int ch;

  while(ros::ok())
  {
    ros::spinOnce();
    
    for(; !(ch=='\n');){  
  
        ch = getch();  
        printf("%d \n", ch);
        break;  
    }
    switch(ch)
      {
        case 97:
          msg.mode = 1;
          break;
        case 100:
          msg.mode = 0;
          break;
        case 115:
          msg.mode = 5;
          break;
        case 113:
          msg.cnt = 0; 
          break;
        case 119:
          msg.cnt = 1;
          break;
        case 107:
          goal.pose.position.x = -1.75;
          goal.pose.position.y = -1.75;
          goal.pose.orientation.w = 1.56;

          goal.header.stamp = ros::Time::now();
          goal.header.frame_id = "map";
          tunnel_pub.publish(goal);
          
          for(int i=0; i<15; i++)
            loop_rate.sleep();
            
          goal.pose.position.x = 0.15;
          goal.pose.position.y = -1.7;
          goal.pose.orientation.w = 3.24;

          goal.header.stamp = ros::Time::now();
          goal.header.frame_id = "map";
          tunnel_pub.publish(goal);
          break;
       }

    send_msg.publish(msg);
    printf("msg.mode = %d\n", msg.mode);
    printf("msg.cnt = %d\n", msg.cnt);
    }
    loop_rate.sleep();
  

}
