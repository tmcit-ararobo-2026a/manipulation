#include <rclcpp/rclcpp.hpp>

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "sensor_msgs/msg/joy.hpp"
namespace manual {
class JoyToTwistNode : public rclcpp::Node
{
private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_;

public:
    JoyToTwistNode(const rclcpp::NodeOptions& options) : Node("joy_to_twist_node", options)
    {
        sub_joy_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&JoyToTwistNode::sub_joy_three, this, std::placeholders::_1)
        );
        twist_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }
    void sub_joy_three(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        auto send_data = geometry_msgs::msg::Twist();
        RCLCPP_INFO(this->get_logger(), "get controller : [%f,%d]", msg->axes[0], msg->buttons[1]);
        send_data.linear.x  = msg->axes[1];  // 左側スティック（上下方向
        send_data.linear.y  = msg->axes[0];  // 左側スティック（左右方向）
        send_data.angular.z = msg->axes[3];  // 右側スティック（左右方向）
        twist_->publish(send_data);
    }
};
}  // namespace manual

RCLCPP_COMPONENTS_REGISTER_NODE(manual::JoyToTwistNode)