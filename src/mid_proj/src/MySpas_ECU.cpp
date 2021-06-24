#include "ros/ros.h"
#include "mid_proj/ObstacleMsg.h"
#include "mid_proj/LocationMsg.h"
#include "mid_proj/OnService.h"
#include "mid_proj/MyState.h"


void OwnerLocationCallback(const mid_proj::LocationMsg::ConstPtr&msg)
{
  ROS_INFO_STREAM("OwnrLocation: "<< msg->location );

}



void locationCallback(const mid_proj::ObstacleMsg::ConstPtr&msg2)
{

  ROS_INFO_STREAM("Time: "<<msg2->stamp <<" , Obstacle_name: "<<msg2->name<<" , Obstacle_distance: "<<msg2->distance );


}

void ObSpCallback(const mid_proj::MyState::ConstPtr&msg4)
{

  ROS_INFO_STREAM("Obstacle_move: "<<msg4->move);


}




int main(int argc, char **argv)
{

  ros::init(argc,argv,"MySpas_ECU");
  ros::NodeHandle nh;

  ros::Subscriber MyV_ECU_sub = nh.subscribe("Owner_Location",1000,OwnerLocationCallback);
  ros::Subscriber Ultra_sub = nh.subscribe("Obstacle_Location",1000,locationCallback);
  ros::Subscriber sub = nh.subscribe("okay",1000,ObSpCallback);

  ros::Publisher ObSp_pub =
         nh.advertise<mid_proj::MyState>("Im_out",1000);



     ros::Rate loop_rate(10);
     mid_proj::MyState msg5;


     while (ros::ok()){


   msg5.move=true;
   msg5.name='A';
   msg5.existence_count=1;

   ROS_INFO_STREAM("I want to go out");
   ROS_INFO_STREAM("move:true , existence_count: "<< msg5.existence_count);

   ObSp_pub.publish(msg5);

   ros::spinOnce();
   loop_rate.sleep();


 }
   return 0;
}
