#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

#include "std_msgs/String.h"
#include <sstream>
#include <ros/ros.h>
// Gazebo's API has changed between major releases. These changes are
// accounted for with #if..#endif blocks in this file.

#include <gazebo/gazebo_client.hh>

int main(int _argc, char **_argv)
{
      // Load gazebo as a client
    gazebo::client::setup(_argc, _argv);


    // Create our node for communication
    gazebo::transport::NodePtr node(new gazebo::transport::Node());
    node->Init();

    // Publish to the  velodyne topic
    gazebo::transport::PublisherPtr pub =
      node->Advertise<gazebo::msgs::Quaternion>("/chatter");

      // Wait for a subscriber to connect to this publisher
    pub->WaitForConnection();

      // Create a a vector3 message
    gazebo::msgs::Quaternion msg;
    
    //   // Set the velocity in the x-component
    gazebo::msgs::Set(&msg, 
        ignition::math::Quaternion(std::atof(_argv[1]), std::atof(_argv[2]), std::atof(_argv[3]), std::atof(_argv[4])));
   
    // ROS_INFO(&msg);
    
    // Send the message
    pub->Publish(msg);

    // Make sure to shut everything down.   
    gazebo::client::shutdown();
    
}  







