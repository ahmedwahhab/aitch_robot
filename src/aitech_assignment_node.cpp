#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
#include <tf/transform_listener.h>
#include "geometry_msgs/Point.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/LaserScan.h"
#include "iomanip"

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */

void Callback(const sensor_msgs::LaserScan::ConstPtr& scan){
         

      ROS_INFO("position=: [%f],[%f],[%f],[%f],[%f],[%f],[%f],[%f]",scan->ranges[562],scan->ranges[561],scan->ranges[560],scan->ranges[559],scan->ranges[157],scan->ranges[158],scan->ranges[159],scan->ranges[160]); 
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "move_aitech_robot");

  const double FORWARD_SPEED_MPS = 0.5;
  
  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/aitech_robot/laser/scan",1000,Callback);

  geometry_msgs::Twist msg;
  //msg.linear.x = FORWARD_SPEED_MPS;

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    
    pub.publish(msg);
 
    ros::spinOnce();

    loop_rate.sleep();
    
  }


  return 0;
}
