#!/usr/bin/python3

import rospy
from question_one.msg import Input

def talker():
    pub = rospy.Publisher('chatter', Input, queue_size=10)
    rospy.init_node('talker', anonymous=True)
    rate = rospy.Rate(10)

    msg = Input()
    msg.coor = [4, 5, 6]
    msg.angels = [30, 45, 60]
    msg.d = 5

    while not rospy.is_shutdown():
        rospy.loginfo(msg)
        pub.publish(msg)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass

