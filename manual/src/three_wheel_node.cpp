#include <rclcpp/rclcpp.hpp>

#include "geometry_msgs/msg/twist.hpp"

namespace manual {

class ThreeWheelNode : public rclcpp::Node
{
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_cmd_vel_;

public:
    ThreeWheelNode() : Node("three_wheel_node")
    {
        sub_cmd_vel_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            10,
            std::bind(&ThreeWheelNode::cmd_vel_callback, this, std::placeholders::_1)
        );
    }

    void cmd_vel_callback(geometry_msgs::msg::Twist::SharedPtr msg) {}
};

}  // namespace manual

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<manual::ThreeWheelNode>());
    rclcpp::shutdown();
    return 0;
}