#include <boost/bind.hpp>
#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <iostream>

// include file for the publisher to work
#include "std_msgs/String.h"
#include "std_msgs/Float32.h"
#include <sstream>
#include <cstdlib>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"
#include <arm_gazebo/Input.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>



namespace gazebo {
 
 class Listener : public ModelPlugin
	{
	

	public:
        Listener(){}
    
    public: 
        virtual void Load(physics::ModelPtr _model, sdf::ElementPtr sdf)
	 	   {

            
            // Store the model pointer for convenience.
            this->model = _model;
            this->jointController = this->model->GetJointController();

            if (!ros::isInitialized())
            {
                int argc = 0;
                char **argv = NULL;
                ros::init(argc, argv, "gazebo_client", ros::init_options::NoSigintHandler);
                ROS_FATAL_STREAM("Ros is not initialized."
                       << "Load the .. in gazebo_ros");
            }
            else
            {
                ROS_INFO("Starting plugin");
            }

            this->pid = common::PID(20.1, 10.01, 10.03);

                
            std::string topicName = "/chatter";


            // Create our ROS node. This acts in a similar manner to
            // the Gazebo node
            this->rosNode.reset(new ros::NodeHandle("gazebo_client"));
            ros::SubscribeOptions so =
                ros::SubscribeOptions::create<std_msgs::String>(
                     "/chatter",
                    1,
                    boost::bind(&Listener::OnRosMsg, this, _1),
                    ros::VoidPtr(), &this->rosQueue);
            
            this->rosSub = this->rosNode->subscribe(so);

            //   this->rosSub = this->rosNode->subscribe(topicName, 1000,
            //    &Listener::OnRosMsg);

            // Spin up the queue helper thread.
            this->rosQueueThread =
              std::thread(std::bind(&Listener::QueueThread, this));

            name1 = this->model->GetJoint("chasis_arm1_joint")->GetScopedName();
            name2 = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();
            name3 = this->model->GetJoint("arm2_arm3_joint")->GetScopedName();
            name4 = this->model->GetJoint("arm3_arm4_joint")->GetScopedName();

            this->jointController->SetPositionPID(this->name1, this->pid);
            this->jointController->SetPositionPID(this->name2, this->pid);
            this->jointController->SetPositionPID(this->name3, this->pid);
            this->jointController->SetPositionPID(this->name4, this->pid);

            this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&Listener::OnUpdate, this));
		}


        public:
            void OnUpdate()
            {
            // std::cout << this->angles[0]  << " " <<  this->angles[1]  << " " <<  this->angles[2] << std::endl;
            float angleDegree1 = this->angles[1];
		    float rad1 = M_PI * angleDegree1 / 180;

		    //std::string name2 = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();
			//this->jointController->SetPositionPID(this->name2, this->pid);
			this->jointController->SetPositionTarget(this->name2, rad1);

            float angleDegree = this->angles[0];
			float rad = M_PI * angleDegree / 180;

			//std::string name1 = this->model->GetJoint("chasis_arm1_joint")->GetScopedName();
			//this->jointController->SetPositionPID(this->name1, this->pid);
			this->jointController->SetPositionTarget(this->name1, rad);
			// this->jointController->Update();
            
            float angleDegree2 = this->angles[2];
			float rad2 = M_PI * angleDegree2 / 180;

		    //std::string name3 = this->model->GetJoint("arm2_arm3_joint")->GetScopedName();
		    //this->jointController->SetPositionPID(this->name3, this->pid);
		    this->jointController->SetPositionTarget(this->name3, rad2);
			// this->jointController->Update();
            float angleDegree3 = this->angles[3];
			float rad3 = M_PI * angleDegree3 / 180;

			//std::string name4 = this->model->GetJoint("arm3_arm4_joint")->GetScopedName();
			//this->jointController->SetPositionPID(this->nstd::cout << _msg->x <<ame4, this->pid);
			this->jointController->SetPositionTarget(this->name4, rad3);
			
            
            this->jointController->Update();

            }

        public: void OnRosMsg(const std_msgs::String::ConstPtr& msg)
        {
            
            // std::cout << msg->data.c_str() <<  std::endl;                

            std::stringstream ss(msg->data.c_str());

            std::string angle;
            int i = 0;
            while (ss >> angle) {
                this->angles[i++] = std::stof(angle);                
            }

        }

        /// \brief ROS helper function that processes messages
        private: void QueueThread()
        {
          static const double timeout = 0.01;
          while (this->rosNode->ok())
          {
            this->rosQueue.callAvailable(ros::WallDuration(timeout));
          }          

        }


        private:
		    event::ConnectionPtr updateConnection;

        private: physics::ModelPtr model;
        
        private:
		    physics::JointControllerPtr jointController;

        /// \brief Pointer to the joint.
        private: physics::JointPtr joint;

        /// \brief A PID controller for the joint.
        private: common::PID pid;
	    private:
	    	ros:: NodeHandle n; 
            ///  \brief A node used for transport
            
        /// \brief A node use for ROS transport
        private: std::unique_ptr<ros::NodeHandle> rosNode;

        /// \brief A ROS subscriber
        private: ros::Subscriber rosSub;

        /// \brief A ROS callbackqueue that helps process messages
        private: ros::CallbackQueue rosQueue;

        /// \brief A thread the keeps running the rosQueue
        private: std::thread rosQueueThread;
        
        private:
            double angles[4];
            std::string name1;
            std::string name2;
            std::string name3;
            std::string name4;

		
	};
    GZ_REGISTER_MODEL_PLUGIN(Listener)
}
