#include <rclcpp/rclcpp.hpp>

#include "sensor_msgs/msg/joy.hpp"
class ThreeWheelNode : public rclcpp::Node
{
private:
public:
    ThreeWheelNode() : Node("three_wheel_node") {}
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ThreeWheelNode>());
    rclcpp::shutdown();
    return 0;
}