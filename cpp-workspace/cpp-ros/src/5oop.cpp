#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <unistd.h>
#include <iostream>

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

    void circleMotion() {
        geometry_msgs::Twist cmd_vel;
        cmd_vel.linear.x = 2.0;
        cmd_vel.angular.z = 1.0;
        ros::Rate loop_rate(60);

        while (ros::ok()) {
            publisher_cmd_vel_.publish(cmd_vel);
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

    void squareMotion() {
        for (int i = 0; i < 4; ++i) {
            moveStraight(2.0, 2.0);
            turn(1.57, 1.57);
        }
    }

    void starMotion() {
        for (int i = 0; i < 5; ++i) {
            moveStraight(2.0, 2.0);
            turn(1.25, 2.094);
        }
    }

    void run(int choice) {
        switch (choice) {
            case 1:
                circleMotion();
                break;

            case 2:
                squareMotion();
                break;

            case 3:
                starMotion();
                break;

            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }

private:
    ros::Publisher publisher_cmd_vel_;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_motion_node");
    ros::NodeHandle n;
    TurtleController turtle(n);
    int choice;

    std::cout << "Enter 1 for Circle, 2 for Square, 3 for Star: ";
    std::cin >> choice;
    turtle.run(choice);
    
    return 0;
}
