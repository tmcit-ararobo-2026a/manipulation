//順次他のボタンも実装していきます。
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"

using namespace std::chrono_literals;

class ButtonNode : public rclcpp::Node
{
public:
    ButtonNode() : Node("botton_for_servo")
    {
        button_sbscriver_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&ButtonNode::joy_callback, this, std::placeholders::_1));

        button_publisher_ = this->create_publisher<std_msgs::msg::Int32MultiArray>("button", 10);
        RCLCPP_INFO(this->get_logger(), "Hello user! ButtonNode was started!!");
    }

private:
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        auto send_data = std_msgs::msg::Int32MultiArray();
        send_data.data.push_back(msg->buttons[0]); // cross:
        send_data.data.push_back(msg->buttons[1]); // circle
        send_data.data.push_back(msg->buttons[2]); // triangle
        send_data.data.push_back(msg->buttons[3]); // square
        RCLCPP_INFO(this->get_logger(), "get_controller_button\n cross : %d  circle : %d\n triangle : %d  square : %d ]",
         msg->buttons[0], msg->buttons[1], msg->buttons[2], msg->buttons[3]);
        button_publisher_->publish(send_data);
    }

    rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr button_publisher_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr button_sbscriver_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ButtonNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
