/*
#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
/**/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <cstring>
#include "mqtt/client.h"

//#define ADDRESS "192.168.1.209"	// Broker IP
#define ADDRESS "127.0.0.1"
#define CLIENTID "ODOM ID"
#define TOPIC "odom"
#define QOS 2
#define PAYLOAD "CIAO!"

double roll = 0;
double pitch = 0;
double yaw = 0;

/* func
void zedCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
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

 ROS_INFO("\nPosition x: [%f]\n Position y: [%f]\n Position z: [%f]\n Roll: [%lf]\n Pitch: [%lf]\n Yaw: [%lf]\n", msg->pose.pose.position.x,
                                                            msg->pose.pose.position.y,
                                                             msg->pose.pose.position.z,
                                                             roll, pitch, yaw);
}
/* func */

int main(int argc, char **argv)
{
  sample_mem_persistence persist;
  mqtt::client client(ADDRESS, CLIENTID, &persist);
  mqtt::connect_options connOpts;
  
  try 
  {
		  std::cout << "\nConnecting..." << std::endl;
		  client.connect(connOpts);
		  std::cout << "...OK" << std::endl;

		  // First use a message pointer.

		  std::cout << "\nSending message..." << std::endl;
		  auto posx = mqtt::make_message(TOPIC, PAYLOAD1);
		  posx->set_qos(QOS);
		  client.publish(posx);
		  std::cout << "...OK" << std::endl;		  
  }
 
	 catch (const mqtt::persistence_exception& exc) 
  {
		  std::cerr << "Persistence Error: " << exc.what() << " ["
		    << exc.get_reason_code() << "]" << std::endl;
		  return 1;
	 }
 
	 catch (const mqtt::exception& exc) 
  {
		  std::cerr << exc.what() << std::endl;
		  return 1;
	 }

/*
  ros::init(argc, argv, "zedmqtt");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/zed/odom", 1000, zedCallback);
  
  ros::spin();
/**/
 
  return 0;
}
