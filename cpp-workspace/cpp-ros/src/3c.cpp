#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "basic_class_publish_node");
    ros::NodeHandle n;
    geometry_msgs::Twist cmd_vel_;
    ros::Publisher publisher_cmd_vel_ = n.advertise<geometry_msgs::Twist> ("turtle1/cmd_vel", 10);

    ros::Rate loop_rate(60);
    
    ros::Time start_time_ = ros::Time::now();
    while (ros::ok()) {
        cmd_vel_.linear.x = 10;
        cmd_vel_.angular.z = 10;
        if ((ros::Time::now() - start_time_).toSec() >= 10) {
            cmd_vel_.linear.x = 0;
            cmd_vel_.angular.z = 0;
        }
        publisher_cmd_vel_.publish(cmd_vel_);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
