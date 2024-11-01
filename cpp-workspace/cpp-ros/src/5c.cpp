#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <unistd.h>
#include <iostream>

void move_straight(ros::Publisher &publisher, double speed, double duration) {
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = speed;
    cmd_vel.angular.z = 0;
    ros::Time start_time = ros::Time::now();

    while (ros::Time::now() - start_time < ros::Duration(duration)) {
        publisher.publish(cmd_vel);
        ros::spinOnce();
        usleep(100000);
    }
}

void turn(ros::Publisher &publisher, double angular_speed, double angle) {
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 0;
    cmd_vel.angular.z = angular_speed;
    double duration = angle / angular_speed;
    ros::Time start_time = ros::Time::now();

    while (ros::Time::now() - start_time < ros::Duration(duration)) {
        publisher.publish(cmd_vel);
        ros::spinOnce();
        usleep(100000);
    }
}

void circle_motion(ros::Publisher &publisher) {
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 2.0;
    cmd_vel.angular.z = 1.0;
    ros::Rate loop_rate(60);

    while (ros::ok()) {
        publisher.publish(cmd_vel);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void square_motion(ros::Publisher &publisher) {
    for (int i = 0; i < 4; ++i) {
        move_straight(publisher, 2.0, 2.0);
        turn(publisher, 1.57, 1.57);
    }
}

void star_motion(ros::Publisher &publisher) {
    for (int i = 0; i < 5; ++i) {
        move_straight(publisher, 2.0, 2.0);
        turn(publisher, 3.14, 2.094);
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_motion_node");
    ros::NodeHandle n;
    ros::Publisher publisher = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    int choice;
    
    std::cout << "Enter 1 for Circle, 2 for Square, 3 for Star: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            circle_motion(publisher);
            break;

        case 2:
            square_motion(publisher);
            break;

        case 3:
            star_motion(publisher);
            break;

        default:
            std::cout << "Invalid choice!" << std::endl;
    }

    return 0;
}
