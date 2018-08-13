#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
#include <vector>
#include <tf/transform_listener.h>
#include "geometry_msgs/Point.h"
#include "std_msgs/Header.h"
#include "sensor_msgs/LaserScan.h"
#include "iomanip"


class ParkingRobot
{
public:
  

  static void Callback(const sensor_msgs::LaserScan::ConstPtr& scan){
         

  double* new_readings = new double [720];

  int n, i;
  float sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;
  
  for(i = 0; i < 719; ++i)
    {
        new_readings[i] = scan->ranges[i];
        
        if(new_readings[i]>30){
          new_readings[i]=0.0;
        }

    }


  //right leg avrege pointcloud
  for(i = 156; i < 162; ++i)
    {
        
        sum1 += new_readings[i];
    }

    avg1 = sum1 / 6;
    


  //left leg averge pointcloud
  for(i = 557; i < 563; ++i)
    {
        
        sum2 += new_readings[i];
    }

    avg2 = sum2 / 6;
    

  //not seeing other legs average 
  for(i = 181; i < 539; ++i)
    {
        
        sum3 += new_readings[i];
    }

    avg3 = sum3 / n;
 

}
  
 
 
  static double avg1, avg2, avg3;

};

double ParkingRobot::avg1 = 0;
double ParkingRobot::avg2 = 0;
double ParkingRobot::avg3 = 0;

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "move_aitech_robot");

  ParkingRobot R;

  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Subscriber sub = nh.subscribe<sensor_msgs::LaserScan>("/aitech_robot/laser/scan",1000,ParkingRobot::Callback);


  ros::Rate loop_rate(10);

  while (ros::ok())
  { 

    geometry_msgs::Twist msg;
    const double FORWARD_SPEED_MPS = 0.5;

    msg.linear.x = FORWARD_SPEED_MPS;

    
    if(ParkingRobot::avg1 > 0 && ParkingRobot::avg3 == 0 ){
      
        msg.linear.x = 0;
      }

    pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  
  }
  


  return 0;
}
