#include "ros/ros.h"
#include "mid_proj/ObstacleMsg.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "Ultra_sensor");
    ros::NodeHandle nh;

    ros::Publisher pub =
        nh.advertise<mid_proj::ObstacleMsg>("Obstacle_Location",1000);

    ros::Rate loop_rate(10);
    mid_proj::ObstacleMsg msg2;

    int count=10000;
    while (ros::ok()){

  msg2.stamp = ros::Time::now();
  msg2.existence_count = 1;
  msg2.distance=count;
  msg2.name = 'A';


  ROS_INFO_STREAM("Time: "<<msg2.stamp <<", Obstacle_existence_count: "<< msg2.existence_count
                 <<",Obstacle_name: "<<msg2.name<<",Obstacle_distance: "<<msg2.distance);

  pub.publish(msg2);

  ros::spinOnce();
  loop_rate.sleep();
  count--;

}
  return 0;
  }
