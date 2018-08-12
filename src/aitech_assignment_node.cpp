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


/**std::vector<float> range2point(float ang_min,float ang_max, float inc,float range, int indx){

std::vector<float>   pt;
pt.push_back(0.1);
pt.push_back(0.3);
return pt;

}*/

void Callback(const sensor_msgs::LaserScan::ConstPtr& scan){
         

  geometry_msgs::Twist msg;
  

  int n, i;
  float sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, average1, average2, average3;
  const double FORWARD_SPEED_MPS = 0.5;
  msg.linear.x = FORWARD_SPEED_MPS;

  for(i = 0; i < 719; ++i)
    {
        
        if(scan->ranges[i]>30){
          scan->ranges[i]=0.0;
        }
    }


  //right leg avrege pointcloud
  for(i = 156; i < 162; ++i)
    {
        
        sum1 += scan->ranges[i];
    }

    average1 = sum1 / n;
    printf("%.6f", average1);


  //left leg averge pointcloud
  for(i = 557; i < 563; ++i)
    {
        
        sum2 += scan->ranges[i];
    }

    average2 = sum2 / n;
    printf("%.6f", average2);

  //not seeing other legs average 
  for(i = 181; i < 539; ++i)
    {
        
        sum3 += scan->ranges[i];
    }

    average3 = sum3 / n;
    printf("%.6f", average3);

  

  if((1.73<average1<1.77)&&(1.73<average2<1.77)&&(average3<0.5)){

    msg.linear.x = 0;
    
  }
  
      //ROS_INFO("position=: [%f],[%f],[%f],[%f],[%f],[%f],[%f],[%f]",scan->ranges[562],scan->ranges[561],scan->ranges[560],scan->ranges[559],scan->ranges[157],scan->ranges[158],scan->ranges[159],scan->ranges[160]); 
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "move_aitech_robot");

  
  
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::Subscriber sub = nh.subscribe<sensor_msgs::LaserScan>("/aitech_robot/laser/scan",1000,Callback);

  geometry_msgs::Twist msg;

  ros::Rate loop_rate(10);

  while (ros::ok())
  {

    //std::cout<<range2point(0.1,0.1,0.1,0.2,1).back()<<std::endl;
    
    pub.publish(msg);
 
    ros::spinOnce();

    loop_rate.sleep();
    
  }


  return 0;
}
