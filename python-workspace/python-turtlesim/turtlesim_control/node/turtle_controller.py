#!/usr/bin/env python


import rospy
import argparse
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from P import PController
from I import IController
from PI import PIController
from PID import PIDController

import math


class turtle_PID():

    def __init__(self, controller=0):

        self.pub = rospy.Publisher('turtle1/cmd_vel', Twist, queue_size=10)
        rospy.Subscriber("turtle1/pose", Pose, self.pose_callback)

        rospy.init_node('turtle_controller', anonymous=True)
        self.rate = rospy.Rate(100)  # 10hz

        self.angle_PID = None
        self.distance_PID = None

        if controller == 1:
            self.init_P()
        elif controller == 2:
            self.init_I()
        elif controller == 3:
            self.init_PI()
        else:
            self.init_PID()

        self.msg = Twist()
        self.move_turtle()

    def init_P(self):
        self.angle_PID = PController()
        self.distance_PID = PController()

        self.angle_PID.setKp(1.4)
        self.distance_PID.setKp(1.4)

    def init_I(self):
        self.angle_PID = IController()
        self.distance_PID = IController()

        self.angle_PID.setKi(0.1)
        self.distance_PID.setKi(0.1)

    def init_PI(self):
        self.angle_PID = PIController()
        self.distance_PID = PIController()

        self.angle_PID.setKp(1.4)
        self.angle_PID.setKi(0.01)

        self.distance_PID.setKp(1.4)
        self.distance_PID.setKi(0.01)

    def init_PID(self):
        self.angle_PID = PIDController()
        self.distance_PID = PIDController()

        self.angle_PID.setKp(1.4)
        self.angle_PID.setKi(0.01)
        self.angle_PID.setKd(0.5)

        self.distance_PID.setKp(1.4)
        self.distance_PID.setKi(0.01)
        self.distance_PID.setKd(0.5)

    def angular_controller(self):

        self.R = math.sqrt(
            math.pow(self.current_pose_x - self.goal_x, 2) + math.pow(self.current_pose_y - self.goal_y, 2))

        self.xr = self.R * math.cos(self.current_angle)
        self.yr = self.R * math.sin(self.current_angle)

        self.xim = self.current_pose_x + self.xr
        self.yim = self.current_pose_y + self.yr

        self.C = math.sqrt(math.pow(self.xim - self.goal_x, 2) + math.pow(self.yim - self.goal_y, 2))

        if self.xim > self.goal_x:

            self.alpha = math.acos((2 * math.pow(self.R, 2) - math.pow(self.C, 2)) / (2 * math.pow(self.R, 2)))
        else:
            self.alpha = 2 * 3.14 * math.acos(
                (2 * math.pow(self.R, 2) - math.pow(self.C, 2)) / (2 * math.pow(self.R, 2)))

        print(self.alpha)
        while self.alpha > 0.005:
            self.R = math.sqrt(
                math.pow(self.current_pose_x - self.goal_x, 2) + math.pow(self.current_pose_y - self.goal_y, 2))
            self.xr = self.R * math.cos(self.current_angle)
            self.yr = self.R * math.sin(self.current_angle)

            self.xim = self.current_pose_x + self.xr
            self.yim = self.current_pose_y + self.yr

            self.C = math.sqrt(math.pow(self.xim - self.goal_x, 2) + math.pow(self.yim - self.goal_y, 2))

            if self.xim > self.goal_x:

                self.alpha = math.acos((2 * math.pow(self.R, 2) - math.pow(self.C, 2)) / (2 * math.pow(self.R, 2)))

            else:

                self.alpha = 2 * 3.14 * math.acos(
                    (2 * math.pow(self.R, 2) - math.pow(self.C, 2)) / (2 * math.pow(self.R, 2)))

            self.alpha = math.acos((2 * math.pow(self.R, 2) - math.pow(self.C, 2)) / (2 * math.pow(self.R, 2)))

            self.PID_angle = self.angle_PID.update(self.alpha)

            self.msg.angular.z = self.PID_angle

            self.pub.publish(self.msg)

    def distance_controller(self):

        self.distance = math.sqrt(
            math.pow(self.goal_x - self.current_pose_x, 2) + math.pow(self.goal_y - self.current_pose_y, 2))
        print("distance: " + str(self.distance))
        while self.distance > 0.15:
            self.distance = math.sqrt(
                math.pow(self.goal_x - self.current_pose_x, 2) + math.pow(self.goal_y - self.current_pose_y, 2))

            self.PID_distance = self.distance_PID.update(self.distance)

            self.msg.linear.x = self.PID_distance

            self.pub.publish(self.msg)

    def get_user_input(self):

        self.goal_x = input("X position:")
        self.goal_y = input("Y position:")

    def move_turtle(self):

        self.get_user_input()

        self.angular_controller()

        self.distance_controller()

    def pose_callback(self, data):

        self.current_pose_x = data.x
        self.current_pose_y = data.y
        self.current_angle = data.theta


if __name__ == '__main__':

    try:
        parser = argparse.ArgumentParser()
        parser.add_argument("-c", "--controller", dest="controller", action="store")
        args = parser.parse_args()
        turtle_PID(args.controller)

    except rospy.ROSInterruptException:

        pass
