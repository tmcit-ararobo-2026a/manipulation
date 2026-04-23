// 順次他のボタンも実装していきます。
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>

using namespace std::chrono_literals;

class ButtonNode : public rclcpp::Node
{
public:
    ButtonNode() : Node("button_for_servo")
    {
        button_subscriber_ = this->create_subscription<sensor_msgs::msg::Joy>(
            "joy", 10, std::bind(&ButtonNode::joy_callback, this, std::placeholders::_1)
        );

        button_publisher_ = this->create_publisher<std_msgs::msg::UInt8MultiArray>("button", 10);
        RCLCPP_INFO(this->get_logger(), "Hello user! ButtonNode was started!!");
    }

private:
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
    {
        uint8_t buttons = 0;
        buttons |= (msg->buttons[0] << 0);  // cross
        buttons |= (msg->buttons[1] << 1);  // circle
        buttons |= (msg->buttons[2] << 2);  // triangle
        buttons |= (msg->buttons[3] << 3);  // square
        auto send_data = std_msgs::msg::UInt8MultiArray();

        send_data.data.push_back(buttons);
        RCLCPP_INFO(
            this->get_logger(),
            "get_controller_button\n cross : %d  circle : %d\n triangle : %d  square : %d ]",
            (buttons) & 1,
            (buttons >> 1) & 1,
            (buttons >> 2) & 1,
            (buttons >> 3) & 1
        );
        button_publisher_->publish(send_data);
    }

    rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr button_publisher_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr button_subscriber_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ButtonNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
