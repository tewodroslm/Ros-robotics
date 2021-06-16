#!/usr/bin/python3
import rospy

import numpy as np

import tinyik as ik
from arm_lib.srv import Ik, IkResponse

def ik_servier(request):
  arm = ik.Actuator([
    "z", [0, 0, 0.5],
    "x", [0, 0, 2.0],
    "x", [0, 0, 1.0],
    "x", [0, 0, 0.5],
    "z", [0, 0, 0.15],
    "x", [0, 0, 0.15]
  ])  
  arm.ee = request.target_pose
  print(request.target_pose) 
  print(np.rad2deg(arm.angles/2)) 
  return IkResponse(np.rad2deg(arm.angles/2))

rospy.init_node('service_server')
service = rospy.Service('inverse_kinematic', Ik, ik_servier)
print("listening on inverse kinematic...")
rospy.spin()
  