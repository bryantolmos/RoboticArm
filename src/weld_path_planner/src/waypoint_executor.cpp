#include "weld_path_planner/waypoint_parser.hpp"
#include <moveit/move_group_interface/move_group_interface.h>
#include <rclcpp/rclcpp.hpp>

class WaypointExecutor : public rclcpp::Node {
public:
  WaypointExecutor() : Node("waypoint_executor") {
    // Use timer to delay initialization
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      [this]() { this->initialize(); });
  }

private:
  void initialize() {
    // SAFE initialization after node is fully constructed
    move_group_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(
      shared_from_this(), "ur_manipulator");
    
    // Load waypoints
    weld_path_planner::WaypointParser parser;
    auto waypoints = parser.parse_csv("install/weld_path_planner/share/config/waypoints.csv");
    
    execute_trajectory(waypoints);
    timer_->cancel();  // Stop the timer after initialization
  }

  void execute_trajectory(const std::vector<geometry_msgs::msg::Pose>& waypoints) {
    for (const auto& pose : waypoints) {
      move_group_->setPoseTarget(pose);
      move_group_->move();  // Blocking call
    }
  }
  
  rclcpp::TimerBase::SharedPtr timer_;
  std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_;
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<WaypointExecutor>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}