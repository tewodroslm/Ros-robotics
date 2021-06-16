#!/usr/bin/python3
import rospy
import numpy as np 
 
def Rx(rad):
  return np.array([[ 1, 0            , 0             , 0],
                   [ 0, np.cos(rad)  ,-np.sin(rad)   , 0],
                   [ 0, np.sin(rad)  , np.cos(rad)   , 0],
                   [ 0,  0           , 0             , 1]])


def Rz(rad):
  return np.array([[ np.cos(rad) , -np.sin(rad),  0, 0],
                   [ np.sin(rad),  np.cos(rad),   0, 0],
                   [           0,            0,   1, 0],
                   [           0,            0,   0, 1]])

def Ry(rad):
  return np.matrix([[ np.cos(rad), 0, np.sin(rad), 0],
                   [ 0           , 1, 0          , 0],
                   [-np.sin(rad) , 0, np.cos(rad), 0],
                   [ 0,         0, 0,           0, 1]])                   


def Tz(d):
    m = np.eye(4)
    m[2, 3] = d
    return m


# m1 = Tz(0.1)
# m2 = Rz(np.radians(60)).dot(Tz(0.05))
# m3 = Rx(np.radians(30)).dot(Tz(2))
# m4 = Rx(np.radians(-45)).dot(Tz(1))
# m5 = Rx(np.radians(-30)).dot(Tz(0.5))

# M = (((m1.dot(m2)).dot(m3)).dot(m4)).dot(m5)
# N = M[:, -1]
# print("____________________________")
# print(N)
# print("____________________________")

from arm_lib.srv import FK, FKResponse
def fk_servier(request):
  m1 = Tz(0.1)
  m2 = Rz(np.radians(request.joint_angles[0])).dot(Tz(0.05))
  m3 = Rx(np.radians(request.joint_angles[1])).dot(Tz(2))
  m4 = Rx(np.radians(request.joint_angles[2])).dot(Tz(1))
  m5 = Rx(np.radians(request.joint_angles[3])).dot(Tz(0.5))
  # m6 = Rx(np.radians(request.joint_angles[4])).dot(Tz(0.15))

  M = (((m1.dot(m2)).dot(m3)).dot(m4)).dot(m5) 
  N = M[:, -1]
  print(N) 
  return FKResponse(N)

rospy.init_node('fk_service_server')
fk_service = rospy.Service('forward_kinematic', FK, fk_servier)
print("listening ...")
rospy.spin()

 



















