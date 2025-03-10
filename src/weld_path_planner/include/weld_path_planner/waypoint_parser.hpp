#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <geometry_msgs/msg/pose.hpp>

namespace weld_path_planner {

class WaypointParser {
public:
  std::vector<geometry_msgs::msg::Pose> parse_csv(const std::string& file_path) {
    std::vector<geometry_msgs::msg::Pose> waypoints;
    std::ifstream file(file_path);
    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
      std::stringstream ss(line);
      geometry_msgs::msg::Pose pose;
      char comma;

      ss >> pose.position.x >> comma
         >> pose.position.y >> comma
         >> pose.position.z >> comma
         >> pose.orientation.x >> comma
         >> pose.orientation.y >> comma
         >> pose.orientation.z >> comma
         >> pose.orientation.w;

      waypoints.push_back(pose);
    }
    return waypoints;
  }
};
} // namespace weld_path_planner