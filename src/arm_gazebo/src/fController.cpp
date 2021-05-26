#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Vector3.hh>
#include <iostream>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

namespace gazebo
{
    class ModelPush : public ModelPlugin
    {

        //mmmmmmmmmmmmmmmmmmmmmmmmmmmmm

    public:
          ros::NodeHandle n;
          ros::Publisher pub;
        //mmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

    public:
        void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
        {// Store the pointer to the model
            this->model = _parent;

            // // intiantiate the joint controller
            this->jointController = this->model->GetJointController();

            // // set your PID values
            this->pid = common::PID(30.1, 10.01, 10.03);

            auto joint_name = "arm1_arm2_joint";

            std::string name = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();

            this->jointController->SetPositionPID(name, pid);

            // Listen to the update event. This event is broadcast every
            // simulation iteration.
            this->updateConnection = event::Events::ConnectWorldUpdateBegin(

std::bind(&ModelPush::OnUpdate, this));    }


        // Called by the world update start event
    public:
        void OnUpdate()
        {

    pub = n.advertise<std_msgs::String>("CurrentAnglePublisher",1000);

            float angleDegree = 30;
            float rad = M_PI * angleDegree / 180;
std::string name = this->model->GetJoint("arm1_arm2_joint")->GetScopedName();
            this->jointController->SetPositionPID(name, pid);
            this->jointController->SetPositionTarget(name, rad);
            this->jointController->Update();
    // Get joint position by index.
            // 0 returns rotation accross X axis
            // 1 returns rotation accross Y axis
            // 2 returns rotation accross Z axis
            // If the Joint has only Z axis for rotation, 0 returns that value and 1 and 2 return nan
       double a0 = physics::JointState(this->model->GetJoint("chasis_arm1_joint")).Position(0);
       double a1 = physics::JointState(this->model->GetJoint("arm1_arm2_joint")).Position(0);
    double a2 = physics::JointState(this->model->GetJoint("arm2_arm3_joint")).Position(0);

    double a3 = physics::JointState(this->model->GetJoint("arm3_arm4_joint")).Position(0);

             //double a4 = this->model->GetJoint("chasis_arm1_joint").Position(0);
             //double a5 = physics::JointState(this->model->GetJoint("chasis_arm1_joint")).Position(2);


std::cout << ".......................: " << std::endl;

std::cout << "Current chasis_arm1_joint values: " << a0 * 180.0 / M_PI << std::endl;
std::cout << "Current arm1_arm2_joint values: " << a1 * 180.0 / M_PI << std::endl;
std::cout << "Current arm2_arm3_joint values: " << a2 * 180.0 / M_PI << std::endl;
std::cout << "Current arm3_arm4_joint values: " << a3 * 180.0 / M_PI << std::endl;

std::cout << ".......................: " << std::endl;
//..............   publisher code
    std_msgs::String pub_str;

    std::stringstream ss;

    ss <<"CurrentAngle of chasis_arm1: " <<a0<< std::endl;
    ss <<"CurrentAngle of arm1_arm2  : " <<a1<< std::endl;
    ss <<"CurrentAngle of arm2_arm3  : " <<a2<< std::endl;
    ss <<"CurrentAngle of arm3_arm4  : " <<a3<< std::endl;

    pub_str.data=ss.str();

    std::cout << pub_str.data.c_str() << std::endl;

    pub.publish(pub_str);
        }

        // a pointer that points to a model object
    private:
        physics::ModelPtr model;

        //     // A joint controller object
        //     // Takes PID value and apply angular velocity
        //     //  or sets position of the angles
    private:
        physics::JointControllerPtr jointController;

    private:
        event::ConnectionPtr updateConnection;

        // //     // PID object
    private:
        common::PID pid;

    };
    // Register this plugin with the simulator
    GZ_REGISTER_MODEL_PLUGIN(gazebo::ModelPush)
}
