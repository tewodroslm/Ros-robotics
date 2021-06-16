#!/bin/bash
sleep 2 
python3 ik.py
rostopic pub  /care arm_gazebo/  catch
rostopic pub  /chatter arm_gazebo/   {20, 30,44, 75}
rostopic pub  /care arm_gazebo/   release 

