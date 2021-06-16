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

#include <arm_lib/FK.h>
#include <arm_lib/Ik.h>

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
 
            this->pid = common::PID(200.1, 64.01, 44.03); 

            // Create our ROS node. This acts in a similar manner to
            // the Gazebo node
            this->rosNode.reset(new ros::NodeHandle("gazebo_client"));
            ros::SubscribeOptions so =
                ros::SubscribeOptions::create<std_msgs::String>(
                     "/chatter",
                    1,
                    boost::bind(&Listener::OnRosMsg, this, _1),
                    ros::VoidPtr(), &this->rosQueue);
            
            // subscribe using rosNode1
            this->rosNode1.reset(new ros::NodeHandle("gazebo_client1"));
            ros::SubscribeOptions so_1 =
                ros::SubscribeOptions::create<std_msgs::String>(
                     "/care",
                        1,
                    boost::bind(&Listener::OnRosMsg1, this, _1),
                    ros::VoidPtr(), &this->rosQueue1);

            this->rosSub = this->rosNode->subscribe(so);
            this->rosSub1 = this->rosNode->subscribe(so_1);

            // Spin up the queue helper thread.
            this->rosQueueThread =
              std::thread(std::bind(&Listener::QueueThread, this));
            
            this->rosQueueThread1 =
              std::thread(std::bind(&Listener::QueueThread1, this));

            chasis_arm1_joint = this->model->GetJoint("chasis_arm1_joint")->GetScopedName();
            arm1_arm2_joint = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();
            arm2_arm3_joint = this->model->GetJoint("arm2_arm3_joint")->GetScopedName();
            arm3_arm4_joint = this->model->GetJoint("arm3_arm4_joint")->GetScopedName();

            left_finger = this->model->GetJoint("palm_left_finger")->GetScopedName();
            right_finger = this->model->GetJoint("palm_right_finger")->GetScopedName();
            
            //Velocity of joint trial
            //  this->model->GetJoint("chasis_arm1_joint")->SetVelocity(0, .10);

            this->jointController->SetPositionPID(this->chasis_arm1_joint, this->pid);
            this->jointController->SetPositionPID(this->arm1_arm2_joint, this->pid);
            this->jointController->SetPositionPID(this->arm2_arm3_joint, this->pid);
            this->jointController->SetPositionPID(this->arm3_arm4_joint, this->pid);
            

            this->jointController->SetPositionPID(this->left_finger, this->pid);
            this->jointController->SetPositionPID(this->right_finger, this->pid);

            // Handling the service

            std::vector<float> a;
            a.push_back(2.3); 
            a.push_back(0); 
            a.push_back(0.5); 
            inVerseKinematic(a);
            
            this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&Listener::OnUpdate, this));
		}


        public:
            void OnUpdate()
            {
                          
            //forwardKinematic();

            
            jointAngleController(this->anew, this->bnew, this->cnew, this->dnew, this->enew);
            this->jointController->Update();  
            
            }

        public: void inVerseKinematic(std::vector<float> a){
                        
            std::vector<float> link_length;
            link_length.push_back(0.05);
            link_length.push_back(2.0);
            link_length.push_back(1.0);
            link_length.push_back(0.5);
            link_length.push_back(0.15);

            ros::NodeHandle n;
            ros::ServiceClient client = n.serviceClient<arm_lib::Ik>("inverse_kinematic",100);
            arm_lib::Ik::Request srv;
            arm_lib::Ik::Response resp;
            srv.target_pose = a; 
            srv.link_length = link_length; 
            if (client.call(srv, resp)) { 
                std::cout <<  resp.new_angles[0] << " " <<  resp.new_angles[1] << " " <<  resp.new_angles[2]<< " " <<  resp.new_angles[3]<< " " << std::endl;  
                this->anew = resp.new_angles[0];
                this->bnew = resp.new_angles[1];
                this->cnew = resp.new_angles[2];
                this->dnew = resp.new_angles[3];
                this->enew = resp.new_angles[4];
                // jointAngleController(resp.new_angles[0], resp.new_angles[1], resp.new_angles[2], resp.new_angles[3],  resp.new_angles[4]);
            } else {
                ROS_ERROR("Failed to call service to get *Inverse kinematic* work"); 
            }

            
        }  

        public: void forwardKinematic(){
            std::vector<float> a;
            for(int i = 0; i < sizeof(this->angles)/sizeof(this->angles[0]); i++){ 
                a.push_back(this->angles[i]); 
            }
            
            std::vector<float> link_length;
            link_length.push_back(0.05);
            link_length.push_back(2.0);
            link_length.push_back(1.0);
            link_length.push_back(0.5);
            link_length.push_back(0.15);

            ros::NodeHandle n;
            ros::ServiceClient client = n.serviceClient<arm_lib::FK>("forward_kinematic");
            arm_lib::FK::Request srv;
            arm_lib::FK::Response resp;
            srv.joint_angles = a; 
            srv.link_length = link_length;
            // std::cout <<  a[0] << std::endl;
            if (client.call(srv, resp)) {                  
                 std::cout <<  resp.actuator_pose[0] << " " << resp.actuator_pose[2]<< std::endl;
            } else {
                ROS_ERROR("Failed to call service to get *actuator_pose*"); 
            }
        }

        public: void jointAngleController(float a,float b,float c,float d, float e){ 

		    float rad1 = M_PI * b / 180;

		    this->jointController->SetPositionTarget(this->arm1_arm2_joint, rad1);
 
			float rad = M_PI * a / 180;
        
			this->jointController->SetPositionTarget(this->chasis_arm1_joint, rad);
			   
			float rad2 = M_PI * c / 180;

		    this->jointController->SetPositionTarget(this->arm2_arm3_joint, rad2);
			 
			float rad3 = M_PI * d / 180;

			this->jointController->SetPositionTarget(this->arm3_arm4_joint, rad3);
 
        }    

       
        public: void OnRosMsg(const std_msgs::String::ConstPtr& msg)
        {
            
        
            std::stringstream ss(msg->data.c_str());

            std::string angle;
            int i = 0;
            while (ss >> angle) {
                this->angles[i++] = std::stof(angle);                
            }

        }

        public: void OnRosMsg1(const std_msgs::String::ConstPtr& msg)
        {
            
        
            std::stringstream ss(msg->data.c_str());
            
            std::string s = ss.str(); 
            std::cout <<  s << std::endl;
            
            if(s.find("catch") != std::string::npos){
               ROS_INFO("valueee Equals catch"); 
               this->jointController->SetPositionTarget(this->left_finger, -0.52360);
               this->jointController->SetPositionTarget(this->right_finger, 0.52360);
            }else{
                if(s.find("release") != std::string::npos){
                  this->jointController->SetPositionTarget(this->left_finger, 0.6);
                  this->jointController->SetPositionTarget(this->right_finger, -0.6);
                }
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

        private: void QueueThread1()
        {
          static const double timeout = 0.01;
          while (this->rosNode1->ok())
          {
            this->rosQueue1.callAvailable(ros::WallDuration(timeout));
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
        private: common::PID pid1;
	    private:
	    	ros:: NodeHandle n; 
            ///  \brief A node used for transport
            
        /// \brief A node use for ROS transport
        private: std::unique_ptr<ros::NodeHandle> rosNode;
        private: std::unique_ptr<ros::NodeHandle> rosNode1;

        /// \brief A ROS subscriber
        private: ros::Subscriber rosSub;
        private: ros::Subscriber rosSub1;

        /// \brief A ROS callbackqueue that helps process messages
        private: ros::CallbackQueue rosQueue;
        private: ros::CallbackQueue rosQueue1;

        /// \brief A thread the keeps running the rosQueue
        private: std::thread rosQueueThread;
        private: std::thread rosQueueThread1;
        
        private:
            double angles[4];
            std::string chasis_arm1_joint;
            std::string arm1_arm2_joint;
            std::string arm2_arm3_joint;
            std::string arm3_arm4_joint;
            std::string right_finger;
            std::string left_finger;
            std::string control_fing;
            float anew;float bnew;float cnew;float dnew;float enew;
		
	};
    GZ_REGISTER_MODEL_PLUGIN(Listener)
}
