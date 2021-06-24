#include "ros/ros.h"
#include "mid_proj/ObstacleMsg.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "Ob_Ultra_sensor");
    ros::NodeHandle nh;

    ros::Publisher Ob_pub =
        nh.advertise<mid_proj::ObstacleMsg>("Obstacle_Location_2",1000);

    ros::Rate loop_rate(10);
    mid_proj::ObstacleMsg msg;

    int count=8000;
    while (ros::ok()){

  msg.stamp = ros::Time::now();
  msg.existence_count = 1;
  msg.distance=count;
  msg.name = 'B';

  ROS_INFO_STREAM("Time: "<<msg.stamp <<", Obstacle_existence_count: "<< msg.existence_count
                 <<",Obstacle_name: "<<msg.name<<",Obstacle_distance: "<<msg.distance);

  Ob_pub.publish(msg);

  ros::spinOnce();
  loop_rate.sleep();
  count--;

}
  return 0;
  }
