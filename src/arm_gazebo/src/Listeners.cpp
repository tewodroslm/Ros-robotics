#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <iostream>

// include file for the publisher to work
#include "std_msgs/String.h"
#include "std_msgs/Float32MultiArray.h"
#include <sstream>


#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"

namespace gazebo {
 
 class Listener : public ModelPlugin
	{
	

	public:
        Listener(){}
    
    public: 
        virtual void Load(physics::ModelPtr _model, sdf::ElementPtr sdf)
	 	   {

            this->chasis_arm1 = 0;
            this->arm1_arm2 = 0;
            this->arm2_arm3 = 0;
            this->arm3_arm4 = 0;


            // Safety check
            if (_model->GetJointCount() == 0)
            {
              std::cerr << "Invalid joint count, Listener plugin not loaded\n";
              return;
            }

            // Store the model pointer for convenience.
            this->model = _model;
            this->jointController = this->model->GetJointController();

            this->pid = common::PID(20.1, 10.01, 10.03);

                // Create the node
            this->node = transport::NodePtr(new transport::Node());
            
            this->node->Init("talker");
        

            // Create a topic name
            std::string topicName = "/chatter";

            // Subscribe to the topic, and register a callback
            this->sub = this->node->Subscribe(topicName,
               &Listener::OnRosMsg, this);
            
            // Initialize ros, if it has not already bee initialized.
            if (!ros::isInitialized())
            {
              int argc = 0;
              char **argv = NULL;
              ros::init(argc, argv, "gazebo_client",
                  ros::init_options::NoSigintHandler);
            }

            // Create our ROS node. This acts in a similar manner to
            // the Gazebo node
            this->rosNode.reset(new ros::NodeHandle("gazebo_client"));

            // Spin up the queue helper thread.
            this->rosQueueThread =
              std::thread(std::bind(&Listener::QueueThread, this));


            this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&Listener::OnUpdate, this));
		}


        public:
            void OnUpdate()
            {

            printf("ON OnUpdate -=-=-=-=    loaded \n");
            
            
            float angleDegree1 = this->arm1_arm2;
		    float rad1 = M_PI * angleDegree1 / 180;

		    std::string name2 = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();
			this->jointController->SetPositionPID(name2, this->pid);
			this->jointController->SetPositionTarget(name2, rad1);
			this->jointController->Update();

            float angleDegree = this->chasis_arm1;
			float rad = M_PI * angleDegree / 180;

			std::string name1 = this->model->GetJoint("chasis_arm1_joint")->GetScopedName();
			this->jointController->SetPositionPID(name1, this->pid);
			this->jointController->SetPositionTarget(name1, rad);
			this->jointController->Update();
            
            float angleDegree2 = this->arm2_arm3;
			float rad2 = M_PI * angleDegree2 / 180;

		    std::string name3 = this->model->GetJoint("arm2_arm3_joint")->GetScopedName();
		    this->jointController->SetPositionPID(name3, this->pid);
		    this->jointController->SetPositionTarget(name3, rad2);
			this->jointController->Update();
            float angleDegree3 = this->arm3_arm4;
			float rad3 = M_PI * angleDegree3 / 180;

			std::string name4 = this->model->GetJoint("arm3_arm4_joint")->GetScopedName();
			this->jointController->SetPositionPID(name4, this->pid);
			this->jointController->SetPositionTarget(name4, rad3);
			this->jointController->Update();

            }

        public: void OnRosMsg(ConstQuaternionPtr &_msg)
        {
                        
            std::cout << _msg->x() << " " << _msg->y() << " " << _msg->z() << " " << _msg->w() << std::endl;
            

            this->chasis_arm1 = _msg->w();
            this->arm1_arm2 = _msg->x();
            this->arm2_arm3 = _msg->y();
            this->arm3_arm4 = _msg->z();
            // this->updateConnection = event::Events::ConnectWorldUpdateBegin(
			// 	boost::bind(&Listener::OnUpdate, this));

        }

        private: void OnMsg(ConstVector3dPtr &_msg)
        {
        //   this->SetVelocity(_msg->x());
            printf("Listener loaded \n");
            //ROS_INFO("I heard: [%s]", msg->data.c_str());
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
        private: transport::NodePtr node;

        /// \brief A subscriber to a named topic.
        private: transport::SubscriberPtr sub;

        /// \brief A node use for ROS transport
        private: std::unique_ptr<ros::NodeHandle> rosNode;

        /// \brief A ROS subscriber
        private: ros::Subscriber rosSub;

        /// \brief A ROS callbackqueue that helps process messages
        private: ros::CallbackQueue rosQueue;

        /// \brief A thread the keeps running the rosQueue
        private: std::thread rosQueueThread;
        
        private:
            float chasis_arm1;
            float arm1_arm2;
            float arm2_arm3;
            float arm3_arm4;

		
	};
    GZ_REGISTER_MODEL_PLUGIN(Listener)
}
