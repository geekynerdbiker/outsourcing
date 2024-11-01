#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <unistd.h>

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

int main(int argc, char **argv) {
    ros::init(argc, argv, "square_path_turtle");
    ros::NodeHandle n;
    ros::Publisher publisher = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);

    for (int i = 0; i < 4; ++i) {
        move_straight(publisher, 2.0, 2.0);
        turn(publisher, 1.57, 1.57);
    }
    
    return 0;
}
