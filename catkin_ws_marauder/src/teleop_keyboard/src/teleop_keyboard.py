#!/usr/bin/env python

from __future__ import print_function

import roslib; roslib.load_manifest('teleop_keyboard')
import rospy

from geometry_msgs.msg import Twist

import sys, select, termios, tty

msg = """
k to kill
---------------------------
Moving around:
   a         e
        z

   q    s    d

        x
   w         c
---------------------------
t/g : increase/decrease max speeds
y/h : increase/decrease angular speed
---------------------------
CTRL-C to quit
"""

moveBindings = {
        'z':(1,0),
        'e':(1,-1),
        'a':(1,1),
        'x':(-1,0),
        'c':(-1,-1),
        'w':(-1,1),
        's':(0,0),
        'q':(0,1),
        'd':(0,-1),
        'k':(100,100),
    }

speedBindings={
        't':(10),
        'g':(-10),
    }

rotationBindings={
        'y':(5),
        'h':(-5),
    }

def getKey():
    tty.setraw(sys.stdin.fileno())
    select.select([sys.stdin], [], [], 0)
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def vels(speed,turn):
    return "currently:\tspeed %s\tturn %s " % (speed,turn)

if __name__=="__main__":
    settings = termios.tcgetattr(sys.stdin)

    pub = rospy.Publisher('cmd_vel', Twist, queue_size = 1)
    rospy.init_node('teleop_keyboard')

    speed = rospy.get_param("~speed", 70)
    turn = rospy.get_param("~turn", 45)

    x = 0
    th = 0
    status = 0

    twist = Twist()
    twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
    twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0

    try:
        print(msg)
        print(vels(speed,turn))
        while(1):
            key = getKey()
            if key in moveBindings.keys():
                x = moveBindings[key][0]
                th = moveBindings[key][1]

                twist.linear.x = x*speed
                twist.angular.z = th*turn

                pub.publish(twist)
            elif key in speedBindings.keys():
                if (speedBindings[key] > 0 and speed < 100) or (speedBindings[key] < 0 and speed > 10):
                    speed += speedBindings[key]
                    print(vels(speed,turn))
            elif key in rotationBindings.keys():
                if (rotationBindings[key] > 0 and turn < 60) or (rotationBindings[key] < 0 and turn > 10):
                    turn += rotationBindings[key]
                    print(vels(speed,turn))
            else:
                if (key == '\x03'):
                    twist.linear.x = 200
                    
                    pub.publish(twist)

    except Exception as e:
        print(e)

    finally:
        twist = Twist()
        twist.linear.x = 0; twist.linear.y = 0; twist.linear.z = 0
        twist.angular.x = 0; twist.angular.y = 0; twist.angular.z = 0
        pub.publish(twist)

        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)