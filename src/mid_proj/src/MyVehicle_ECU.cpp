#include "ros/ros.h"
#include "mid_proj/LocationMsg.h"
#include "mid_proj/ObstacleMsg.h"
#include "mid_proj/OnService.h"


int main(int argc, char **argv){
    ros::init(argc, argv, "MyVehicle_ECU");
    ros::NodeHandle n;


    ros::Publisher pub =
        n.advertise<mid_proj::LocationMsg>("Owner_Location",1000);



    ros::Rate loop_rate(10);
    mid_proj::LocationMsg msg;

    int count=123;
    while (ros::ok()){

  msg.stamp = ros::Time::now();
  msg.location = count;
  msg.move =true ;

  ROS_INFO_STREAM("Time: "<<msg.stamp <<", OwnerLocation: "<< msg.location);

  pub.publish(msg);

  ros::spinOnce();
  loop_rate.sleep();
  //count++;


}
  return 0;
  }
