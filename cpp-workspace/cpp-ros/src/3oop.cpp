#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class BasicClassPublish {
public:
    BasicClassPublish(ros::NodeHandle &n)
    : publisher_cmd_vel_(n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10)),
     start_time_(ros::Time::now()) {
    ROS_INFO("Basic_class_publish_node Open");
 }
    ~BasicClassPublish() {
    ROS_INFO("Basic_class_publish_node Close");
 }
    void UpdateCmdVel() {
        cmd_vel_.linear.x = 10;
        cmd_vel_.angular.z = 10;
    }

    void Publisher() {
        publisher_cmd_vel_.publish(cmd_vel_);
    }

    void Stop() {
        if ((ros::Time::now() - start_time_).toSec() >= 10) {
            cmd_vel_.linear.x = 0;
            cmd_vel_.angular.z = 0;
        }
    }

    void Spin() {
        UpdateCmdVel();
        Stop();
        Publisher();
    }
private:
    geometry_msgs::Twist cmd_vel_;
    ros::Publisher publisher_cmd_vel_;
    ros::Time start_time_;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_stop_node");
    ros::NodeHandle n;
    ros::Rate loop_rate(60);
    BasicClassPublish basic_class_publish(n);

    while (ros::ok()) {
        basic_class_publish.Spin();
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

