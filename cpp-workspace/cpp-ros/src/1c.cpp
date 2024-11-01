#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

int main(int argc, char** argv) {
    ros::init(argc, argv, "robot_speed_publisher");
    ros::NodeHandle nh;

    ros::Publisher speed_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);

    geometry_msgs::Twist speed_msg;

    double linear, angular;
    std::cout << "Enter linear velocity: ";
    std::cin >> linear;
    std::cout << "Enter angular velocity: ";
    std::cin >> angular;

    speed_msg.linear.x = linear;
    speed_msg.angular.z = angular;

    ros::Rate loop_rate(10);
    
    while (ros::ok()) {
        speed_pub.publish(speed_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
