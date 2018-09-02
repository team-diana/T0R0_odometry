#include "ros/ros.h"
#include "nav_msgs/Odometry.h"

double roll = 0;
double pitch = 0;
double yaw = 0;

void zedCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
/**/
 // roll (x-axis rotation)
  double sinr = +2.0 * (msg->pose.pose.orientation.w * msg->pose.pose.orientation.x + msg->pose.pose.orientation.y * msg->pose.pose.orientation.z);
  double cosr = +1.0 - 2.0 * (msg->pose.pose.orientation.x * msg->pose.pose.orientation.x + msg->pose.pose.orientation.y * msg->pose.pose.orientation.y);
  roll = atan2(sinr, cosr);

  // pitch (y-axis rotation)
  double sinp = +2.0 * (msg->pose.pose.orientation.w * msg->pose.pose.orientation.y - msg->pose.pose.orientation.z * msg->pose.pose.orientation.x);
  if (fabs(sinp) >= 1)
  {
    pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
  }
  else
  {
    pitch = asin(sinp);
  }

  // yaw (z-axis rotation)
  double siny = +2.0 * (msg->pose.pose.orientation.w * msg->pose.pose.orientation.z + msg->pose.pose.orientation.x * msg->pose.pose.orientation.y);
  double cosy = +1.0 - 2.0 * (msg->pose.pose.orientation.y * msg->pose.pose.orientation.y + msg->pose.pose.orientation.z * msg->pose.pose.orientation.z);
  yaw = atan2(siny, cosy);
/**/

/**/
 ROS_INFO("\nPosition x: [%f]\n Position y: [%f]\n Position z: [%f]\n Roll: [%lf]\n Pitch: [%lf]\n Yaw: [%lf]\n", msg->pose.pose.position.x,
                                                             msg->pose.pose.position.y,
                                                             msg->pose.pose.position.z,
                                                             roll, pitch, yaw);
/**/
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "zedtest");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/zed/odom", 1000, zedCallback);

  ros::spin();

  return 0;
}

