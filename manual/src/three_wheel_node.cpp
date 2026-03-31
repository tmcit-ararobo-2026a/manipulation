#include <rclcpp/rclcpp.hpp>

#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/joy.hpp"
class ThreeWheelNode : public rclcpp::Node
{
private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist;
    geometry_msgs::msg::Twist send_data;

public:
    ThreeWheelNode() : Node("three_wheel_node")
    {
        sub_joy = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&ThreeWheelNode::sub_joy_three, this, std::placeholders::_1)
        );
        twist = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }
    void sub_joy_three(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "get controller : [%f,%d]", msg->axes[0], msg->buttons[1]);
        send_data.linear.x  = msg->axes[1];  // 左側スティック（上下方向
        send_data.linear.y  = msg->axes[0];  // 左側スティック（左右方向）
        send_data.angular.z = msg->axes[3];  // 右側スティック（左右方向）
        twist->publish(send_data);
    }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ThreeWheelNode>());
    rclcpp::shutdown();
    return 0;
}