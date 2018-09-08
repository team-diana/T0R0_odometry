/*
*
* TO DO:
* Not sure if roll, pitch and yaw shall be converted into string to be used as MQTT message payload
*
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ros/ros.h"
#include "math.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Float64.h"
#include "nav_msgs/Odometry.h"
// #include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include "include/MQTTClient.h"

#define ADDRESS   "10.0.0.83"
#define CLIENTID  "ZED_ODOM"
#define QOS       2

#define DIAG_PAYLOAD "Successful operation"

double roll = 0;
double pitch = 0;
double yaw = 0;

MQTTClient zedodom;
MQTTClient_create(&zedodom, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

MQTTClient_message zedodom_msg = MQTTClient_message_initializer;

nav_msgs::Odometry odom;

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

int missionCallback(nav_msgs::Odometry::ConstPtr& odom)
{
  int i = 0;  // quaternion index
  float q[4];  // quaternion
  for(i = 0; i < 4; i++)
  {
    if(i = 0)
    {
      q[0] = odom->pose.pose.orientation.w;
    }
    else if(i = 1)
    {
      q[1] = odom->pose.pose.orientation.x;
    }
    else if(i = 2)
    {
      q[2] = odom->pose.pose.orientation.y;
    }
    else if(i = 3)
    {
      q[3] = odom->pose.pose.orientation.z;
    }
  }
  
  zedodom_msg.qos = QOS;
  zedodom_msg.retained = 0;

  zedodom_msg.payload = &(odom->pose.pose.position.x);
  MQTTClient_publishMessage(zedodom, "odometry/position/x", &zedodom_msg, NULL);
  zedodom_msg.payload = &(odom->pose.pose.position.y);
  MQTTClient_publishMessage(zedodom, "odometry/position/y", &zedodom_msg, NULL);
  zedodom_msg.payload = &(odom->pose.pose.position.z);
  MQTTClient_publishMessage(zedodom, "odometry/position/z", &zedodom_msg, NULL);
  
  toEulerAngle(q, &roll, &pitch, &yaw);
  
  zedodom_msg.payload = &roll;
  MQTTClient_publishMessage(zedodom, "odometry/orientation/roll", &zedodom_msg, NULL);
  zedodom_msg.payload = &pitch;
  MQTTClient_publishMessage(zedodom, "odometry/orientation/pitch", &zedodom_msg, NULL);
  zedodom_msg.payload = &yaw;
  MQTTClient_publishMessage(zedodom, "odometry/orientation/yaw", &zedodom_msg, NULL);
  
  return 0;
}

int main(int argc, char **argv)
{
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  conn_opts.cleansession = 0;

  ros::init(argc, argv, "odom_node");
  ros::NodeHandle n;
  ros::Subscriber subOdom = n.subscribe("/odom", 1000, missionCallback);
  //if(missionCallback(odom))
  //{
  //  MQTTClient_message diag_msg = MQTTClient_message_initializer;
  //  MQTTClient_publishMessage(zedodom, "diagnostics", &diag_msg, NULL);
  //}
  ros::spin();

  return 0;
}
