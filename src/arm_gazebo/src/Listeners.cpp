#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <iostream>

// include file for the publisher to work
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float32MultiArray.h"
#include <sstream>


#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>


namespace gazebo {
 
 class Listener : public ModelPlugin
	{
	

	public:
        Listener(){}
    
    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr /*_sdf*/)
		{
            
            // Safety check
            if (_model->GetJointCount() == 0)
            {
              std::cerr << "Invalid joint count, Listener plugin not loaded\n";
              return;
            }

            // Store the model pointer for convenience.
            this->model = _model;

            // Get the first joint. We are making an assumption about the model
            // having one joint that is the rotational joint.
            this->joint = _model->GetJoints()[0];

            // Setup a P-controller, with a gain of 0.1.
            this->pid = common::PID(0.1, 0, 0);

            // Apply the P-controller to the joint.
            this->model->GetJointController()->SetPositionTarget(
                this->joint->GetScopedName(), this->pid);

            // Set the joint's target velocity. This target velocity is just
            // for demonstration purposes.
            this->model->GetJointController()->SetPositionTarget(
                this->joint->GetScopedName(), 10.0);

                // Create the node
            this->node = transport::NodePtr(new transport::Node());
            
            this->node->Init(this->model->GetWorld()->Name());
        

            // Create a topic name
            std::string topicName = "~/" + this->model->GetName() + "/list_cmd";

            // Subscribe to the topic, and register a callback
            this->sub = this->node->Subscribe(topicName,
               &Listener::OnMsg, this);

		}

        private: void OnMsg(ConstVector3dPtr &_msg)
        {
        //   this->SetVelocity(_msg->x());
            ROS_INFO("I heard: [%s]", msg->data.c_str());
        }

        private: physics::ModelPtr model;

        /// \brief Pointer to the joint.
        private: physics::JointPtr joint;

        /// \brief A PID controller for the joint.
        private: common::PID pid;
	    private:
	    	ros:: NodeHandle n; 
            ///  \brief A node used for transport
        private: transport::NodePtr node;

        /// \brief A subscriber to a named topic.
        private: transport::SubscriberPtr sub;
		
	};
    GZ_REGISTER_MODEL_PLUGIN(Listener)
}
