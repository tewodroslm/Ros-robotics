#!/usr/bin/python3

import rospy

from question_one.msg import Input

import numpy as np
import math as m
 
def Rx(theta):
  return np.matrix([[ 1, 0           , 0           ],
                   [ 0, m.cos(theta),-m.sin(theta)],
                   [ 0, m.sin(theta), m.cos(theta)]])
 
def Ry(theta):
  return np.matrix([[ m.cos(theta), 0, m.sin(theta)],
                   [ 0           , 1, 0           ],
                   [-m.sin(theta), 0, m.cos(theta)]])
 
def Rz(theta):
  return np.matrix([[ m.cos(theta), -m.sin(theta), 0 ],
                   [ m.sin(theta), m.cos(theta) , 0 ],
                   [ 0           , 0            , 1 ]])

def callback(data):
    alpha = data.angels[0]
    beta = data.angels[1]
    gam = data.angels[2]
    print("alpha =", alpha)
    print("beta  =", beta)
    print("gam =", gam)
    

    R = Rz(alpha) * Ry(beta) * Rx(gam)
    print(np.round(R, decimals=2))
    
    # rotate
    rval = np.dot(R, data.coor)
    print(rval)
    print(list(rval))
    print(rval.item((0, 0)))
    print(rval.item((0, 1)))
    print(rval.item((0, 2)))
    
    # translate by b

    final_val = translate(rval.item((0, 0)), rval.item((0, 1)), rval.item((0,2)), data.d)

    print('______________________')
    rospy.loginfo('After rotation and translation the value is: ') 
    print(final_val)
    print('______________________')
    #rospy.loginfo('\n'.join('{}: {}'.format(*k) for k in enumerate(data.coor)))

def translate(x, y, z, t):
  return (x + t, y + t, z + t)

def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber('chatter', Input, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()


