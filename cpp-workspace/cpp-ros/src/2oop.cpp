#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class TurtleController
{
public:
    TurtleController(ros::NodeHandle &nh) {
        publisher_cmd_vel_ = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
        ROS_INFO("TurtleController initialized.");
    }
 
    void UpdateCmdVel(double linear_x, double angular_z) {
        cmd_vel_.linear.x = linear_x;
        cmd_vel_.angular.z = angular_z;
    }
 
    void Publish() {
        publisher_cmd_vel_.publish(cmd_vel_);
    }

    void Spin() {
        ros::Rate loop_rate(60);
        while (ros::ok()) {
            UpdateCmdVel(2.0, 1.0);
            Publish();
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::Publisher publisher_cmd_vel_;
    geometry_msgs::Twist cmd_vel_;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_circle_node");
    ros::NodeHandle n;
 
    TurtleController turtle_controller(n);
    turtle_controller.Spin();
 
    return 0;
}
