#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <unistd.h>

class TurtleController {
public:
    TurtleController(ros::NodeHandle &nh) {
        publisher_cmd_vel_ = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
    }

    void moveStraight(double speed, double duration) {
        geometry_msgs::Twist cmd_vel;
        cmd_vel.linear.x = speed;
        cmd_vel.angular.z = 0;
        ros::Time start_time = ros::Time::now();
        
        while (ros::Time::now() - start_time < ros::Duration(duration)) {
            publisher_cmd_vel_.publish(cmd_vel);
            ros::spinOnce();
            usleep(100000);
        }
    }

    void turn(double angular_speed, double angle) {
        geometry_msgs::Twist cmd_vel;
        cmd_vel.linear.x = 0;
        cmd_vel.angular.z = angular_speed;
        double duration = angle / angular_speed;
        ros::Time start_time = ros::Time::now();
        
        while (ros::Time::now() - start_time < ros::Duration(duration)) {
            publisher_cmd_vel_.publish(cmd_vel);
            ros::spinOnce();
            usleep(100000);
        }
    }
    
    void runSquarePath() {
        for (int i = 0; i < 4; ++i) {
            moveStraight(2.0, 2.0);
            turn(1.57, 1.57);
        }
    }
private:
    ros::Publisher publisher_cmd_vel_;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_square_node");
    ros::NodeHandle n;
    TurtleController turtle(n);
    turtle.runSquarePath();

    return 0;
}
