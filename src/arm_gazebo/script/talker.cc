#include "ros/ros.h"
#include "std_msgs/String.h"
#include <arm_gazebo/Input.h>
#include <sstream>
// #include <ignition/math/Vector3.hh>
#include <iostream>


int main(int _argc, char **_argv)
{
    
     ros::init(_argc, _argv, "talker");
 
     ros::NodeHandle n;
 
   //   ros::Publisher chatter_pub = n.advertise<arm_gazebo::Input>("/chatter", 1000);
   ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/chatter", 1000);
 
     ros::Rate loop_rate(10);
 
      int count = 0;
    
      while (ros::ok())
      {
      
        std_msgs::String msg;

        std::stringstream ss;
                
         

        ss << _argv[1] << " " << _argv[2] << " " << _argv[3] << " " << _argv[4] << " ";
        msg.data = ss.str();
        ROS_INFO("%s", msg.data.c_str());
        chatter_pub.publish(msg); 
        ros::spinOnce(); 

        loop_rate.sleep(); 
        ++count;
      }


  return 0;
    
}  







