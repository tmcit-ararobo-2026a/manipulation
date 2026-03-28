#include <rclcpp/rclcpp.hpp>

#include "sensor_msgs/msg/joy.hpp"
class ThreeWheelNode : public rclcpp::Node
{
private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy;

public:
    ThreeWheelNode() : Node("three_wheel_node")
    {
        sub_joy = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&ThreeWheelNode::sub_joy_three, this, std::placeholders::_1)
        );
    }
    void sub_joy_three(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "get controller : [%f,%d]", msg->axes[0], msg->buttons[1]);
    }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ThreeWheelNode>());
    rclcpp::shutdown();
    return 0;
}