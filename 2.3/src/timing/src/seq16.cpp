#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

#define s 1000000000

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class Seq : public rclcpp::Node
{
  public:
    Seq(): Node("Seq"), elapsed_time(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("ping", 10);
      timer_ = this->create_wall_timer(1ms, std::bind(&Seq::ping, this));
      subscription_ = this->create_subscription<std_msgs::msg::String>("pong", 10, std::bind(&Seq::pong, this, _1));
      clock_gettime(CLOCK_MONOTONIC, &start_time);
    }

  private:
    void ping()
    {
      auto message = std_msgs::msg::String();
      message.data = std::to_string(elapsed_time);
      //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }
    void pong(std_msgs::msg::String _)
    {
      clock_gettime(CLOCK_MONOTONIC, &new_time);
      elapsed_time = (new_time.tv_sec - start_time.tv_sec) * s + (new_time.tv_nsec - start_time.tv_nsec);
      
      start_time = new_time;
    }
    struct timespec new_time, start_time;
    long elapsed_time;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Seq>());
  rclcpp::shutdown();
  return 0;
}