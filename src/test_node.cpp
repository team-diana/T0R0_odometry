#include "ros/ros.h"
//#include "geometry_msgs.h"
//#include "actionlib_msgs.h"
//#include "message_generation.h"
#include "nav_msgs/Odometry.h"
//#include "message_runtime.h"

void zedCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  ROS_INFO("Position x: [%f]", msg->pose.pose.position.x);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "zedtest");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/zed/odom", 1000, zedCallback);

  ros::spin();

  return 0;
}

