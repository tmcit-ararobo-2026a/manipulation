#include <rclcpp/rclcpp.hpp>

#include "geometry_msgs/msg/twist.hpp"
#include "manual/three_wheel_omni.hpp"
#include "std_msgs/msg/float32.hpp"

ThreeWheelOmni omni(0.45, 0.05);

namespace manual {

class ThreeWheelNode : public rclcpp::Node
{
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_cmd_vel_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_wheel_front;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_wheel_back_left;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_wheel_back_right;

public:
    ThreeWheelNode() : Node("three_wheel_node")
    {
        sub_cmd_vel_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            10,
            std::bind(&ThreeWheelNode::cmd_vel_callback, this, std::placeholders::_1)
        );
        pub_wheel_front = this->create_publisher<std_msgs::msg::Float32>("/wheel/front", 10);
        pub_wheel_back_left =
            this->create_publisher<std_msgs::msg::Float32>("/wheel/back_left", 10);
        pub_wheel_back_right =
            this->create_publisher<std_msgs::msg::Float32>("/wheel/back_right", 10);
    }

    void cmd_vel_callback(geometry_msgs::msg::Twist::SharedPtr msg)
    {
        omni.convert(msg->linear.x, msg->linear.y, msg->angular.z, 0.0f);
        std_msgs::msg::Float32 wheel_vel_front, wheel_vel_back_right, wheel_vel_back_left;
        omni.getWheelAngularVelocity(
            &wheel_vel_front.data, &wheel_vel_back_left.data, &wheel_vel_back_right.data
        );
        pub_wheel_front->publish(wheel_vel_front);
        pub_wheel_back_left->publish(wheel_vel_back_left);
        pub_wheel_back_right->publish(wheel_vel_back_right);
    }
};

}  // namespace manual

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<manual::ThreeWheelNode>());
    rclcpp::shutdown();
    return 0;
}