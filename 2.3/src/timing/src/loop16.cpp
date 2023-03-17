#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class Loop16 : public rclcpp::Node
{
public:
  Loop16() : Node("Loop16")
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "ping", 1, std::bind(&Loop16::subscription_callback, this, _1)
    );

    publisher_ = this->create_publisher<std_msgs::msg::String>(
      "pong", 1);

    RCLCPP_INFO(this->get_logger(), "elapsed_time, jitter_roundtrip, jitter_wall_timer");
  }

private:

  void subscription_callback(const std_msgs::msg::String &msg)
  {
    publisher_->publish(msg);
    
    RCLCPP_INFO(this->get_logger(), "%s", msg.data.c_str());
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Loop16>());
  rclcpp::shutdown();
  return 0;
}