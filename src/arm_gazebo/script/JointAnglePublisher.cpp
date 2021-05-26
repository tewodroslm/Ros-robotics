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


//////                This file contain the solution for the 3rd question...  it wo'nt execute since i only copy the file in to this folder.. 
/////                 This to show the solution only


namespace gazebo
{
	class ModelPush : public ModelPlugin
	{
	public:
		void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
		{
			// Store the pointer to the model
			this->model = _parent;

			// // intiantiate the joint controller
			this->jointController = this->model->GetJointController();

			// // set your PID values
			this->pid = common::PID(20.1, 10.01, 10.03);

			auto joint_name = "arm1_arm2_joint";

			std::string name = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();

			this->jointController->SetPositionPID(name, pid);

			// Listen to the update event. This event is broadcast every
			// simulation iteration.
			this->updateConnection = event::Events::ConnectWorldUpdateBegin(
				std::bind(&ModelPush::OnUpdate, this));

			// HANDLES THE PUBLISHER ...

			if(!ros::isInitialized()){
				int argc = 0;
				char **argv = NULL;

				ros::init(argc, argv, "talker", ros::init_options::NoSigintHandler);
			}

			this->chatter_pub = this->n.advertise<std_msgs::String>("chatter", 1000);

			
		}

		// Called by the world update start event
	public:
		void OnUpdate()
		{


			float angleDegree = 20;
			float rad = M_PI * angleDegree / 180;

			std::string name = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();
			std::string name1 = this->model->GetJoint("chasis_arm1_joint")->GetScopedName();
            std::string name3 = this->model->GetJoint("arm2_arm3_joint")->GetScopedName();
            std::string name4 = this->model->GetJoint("arm3_arm4_joint")->GetScopedName();
			
			this->jointController->SetPositionPID(name, pid);
			this->jointController->SetPositionPID(name1, pid);
			this->jointController->SetPositionPID(name3, pid);
			this->jointController->SetPositionPID(name4, pid);


			this->jointController->SetPositionTarget(name, rad);
			this->jointController->Update();

			// Get joint position by index. 
			// 0 returns rotation accross X axis
			// 1 returns rotation accross Y axis
			// 2 returns rotation accross Z axis
			// If the Joint has only Z axis for rotation, 0 returns that value and 1 and 2 return nan
			double a1 = physics::JointState(this->model->GetJoint("arm1_arm2_joint")).Position(0);
			double a2 = physics::JointState(this->model->GetJoint("chasis_arm1_joint")).Position(0);
			double a3 = physics::JointState(this->model->GetJoint("arm2_arm3_joint")).Position(0);
			double a4 = physics::JointState(this->model->GetJoint("arm3_arm4_joint")).Position(0);

			double finalCoord = a1 * 180.0 / M_PI ;
			double finalCoord2 = a2 * 180.0 / M_PI ;
			double finalCoord3 = a3 * 180.0 / M_PI ;
			double finalCoord4 = a4 * 180.0 / M_PI ;

			std::cout << "Current arm1_arm2_joint values: " << finalCoord << " , " << finalCoord2 <<" , "<< finalCoord3<<" , "<< finalCoord4 << std::endl;

			// Apply a small linear velocity to the model.
      		//this->model->SetLinearVel(ignition::math::Vector3d(.3, 0, 0));

			// Publish the Joint angle ...

			std_msgs::Float32MultiArray array;
			
			array.data.clear();
			array.data.push_back(finalCoord);
			array.data.push_back(finalCoord2);
			array.data.push_back(finalCoord3);
			array.data.push_back(finalCoord4);
			
			
			ROS_INFO("publishing hello wooooooorld arrayyy");

			// PUBLISH THE MSSG
			this->chatter_pub.publish(array);

			
		}

		// a pointer that points to a model object
	private:
		physics::ModelPtr model;

		// 	// A joint controller object
		// 	// Takes PID value and apply angular velocity
		// 	//  or sets position of the angles
	private:
		physics::JointControllerPtr jointController;

	private:
		event::ConnectionPtr updateConnection;

		// // 	// PID object
	private:
		common::PID pid;

		// PUBLISHER
	private:
		ros:: NodeHandle n;
	private: 
		ros::Publisher chatter_pub;

	};


	// Register this plugin with the simulator
	GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}