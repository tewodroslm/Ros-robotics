#!/usr/bin/python3

import rospy
from std_msgs.msg import String

# def my_callback(event):
#     print("Hey ! 10 seconds have passed!")
#     rospy.signal_shutdown("Just stopping the robot")

def talker():
    rospy.init_node('talker', anonymous=True)
    pub = rospy.Publisher('/chatter', Float64, queue_size=10)
    rate = rospy.Rate(10)
    #rospy.Timer(rospy.Duration(10), my_callback)

    while not rospy.is_shutdown():
        
        #hello_str = "hello world %s" % rospy.get_time()

        position = math.pi/2
        rospy.loginfo(position)

        pub.publish(position)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException: pass

