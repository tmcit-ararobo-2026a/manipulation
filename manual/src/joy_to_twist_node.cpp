#include <rclcpp/rclcpp.hpp>

#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/joy.hpp"
namespace manual {
class JoyToTwistNode : public rclcpp::Node
{
private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_joy_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_;

public:
    JoyToTwistNode() : Node("joy_to_twist_node")
    {
        sub_joy_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&JoyToTwistNode::sub_joy_three, this, std::placeholders::_1)
        );
        twist_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
    }
    void sub_joy_three(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        double x = msg->axes[0];  // 左側スティック（上下方向
        double y = msg->axes[1];  // 左側スティック（左右方向）
        double z = msg->axes[2];  // 右側スティック（左右方向）
        if (std::abs(x) < 0.3) x = 0.0;
        if (std::abs(y) < 0.3) y = 0.0;
        if (std::abs(z) < 0.3) z = 0.0;
        auto send_data = geometry_msgs::msg::Twist();
        RCLCPP_INFO(this->get_logger(), "get controller : [%f,%d]", msg->axes[0], msg->buttons[1]);
        send_data.linear.x  = x * 1.0f;
        send_data.linear.y  = y * 1.0f;
        send_data.angular.z = z * 1.0f;
        twist_->publish(send_data);
    }
};

}  // namespace manual
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<manual::JoyToTwistNode>());
    rclcpp::shutdown();
    return 0;
}