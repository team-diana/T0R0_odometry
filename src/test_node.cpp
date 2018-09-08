#include "ros/ros.h"
//#include "geometry_msgs.h"
//#include "actionlib_msgs.h"
//#include "message_generation.h"
#include "nav_msgs/Odometry.h"
//#include "message_runtime.h"

/*
double roll = 0;
double pitch = 0;
double yaw = 0;

static void toEulerAngle(float* q, double* roll, double* pitch, double* yaw)
{
  // roll (x-axis rotation)
  double sinr = +2.0 * (q[0] * q[1] + q[2] * q[3]);
  double cosr = +1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]);
  *roll = atan2(sinr, cosr);
  // pitch (y-axis rotation)
  double sinp = +2.0 * (q[0] * q[2] - q[3] * q[1]);
  if (fabs(sinp) >= 1)
  {
    *pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
  }
  else
  {
    *pitch = asin(sinp);
  }
  // yaw (z-axis rotation)
  double siny = +2.0 * (q[0] * q[3] + q[1] * q[2]);
  double cosy = +1.0 - 2.0 * (q[2] * q[2] + q[3] * q[3]);
  *yaw = atan2(siny, cosy);
}
/**/

void zedCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
/*
  int i = 0;  // quaternion index
  float q[4]; // quaternion
  for(i = 0; i < 4; i++)
  {
    if(i = 0)
    {
      q[0] = msg->pose.pose.orientation.w;
    }
    else if(i = 1)
    {
      q[1] = msg->pose.pose.orientation.x;
    }
    else if(i = 2)
    {
      q[2] = msg->pose.pose.orientation.y;
    }
    else if(i = 3)
    {
      q[3] = msg->pose.pose.orientation.z;
    }
  }
/**/
  ROS_INFO("Position x: [%f]\n Position y: [%f]\n Position z: [%f]\n Quaternion w: [%lf]\n Quaternion x: [%lf]\n Quaternion y: [%lf]\n Quaternion z: [%lf]\n", msg->pose.pose.position.x,
                                                             msg->pose.pose.position.y,
                                                             msg->pose.pose.position.z,
                                                             msg->pose.pose.orientation.w,
							     msg->pose.pose.orientation.x,
							     msg->pose.pose.orientation.y,
						     	     msg->pose.pose.orientation.z);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "zedtest");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/zed/odom", 1000, zedCallback);

  ros::spin();

  return 0;
}

