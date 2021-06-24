#include "ros/ros.h"
#include "mid_proj/OnService.h"
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"
#include "mid_proj/OnActionAction.h"
#include "mid_proj/ObstacleMsg.h"
#include "mid_proj/MyState.h"



typedef actionlib::SimpleActionClient<mid_proj::OnActionAction> Client;


void locationCallback(const mid_proj::ObstacleMsg::ConstPtr&msg)
{

  ros::NodeHandle nh;

  ROS_INFO_STREAM("Time: "<<msg->stamp <<" , Obstacle_name: "<<msg->name<<" , Obstacle_distance: "<<msg->distance);

  if(msg->distance >7850){

    Client action_client ("desired_angle",true);
    action_client.waitForServer();


    Client action_client2 ("desired_velocity",true);
    action_client2.waitForServer();


    ROS_INFO("Action server started,sending goal.");
    ROS_INFO("desired_angle:50, desired_velocity:30");

    mid_proj::OnActionGoal goal,goal2;
    goal.order = 50;
    goal2.order = 30;

    action_client.sendGoal(goal);
    action_client.waitForResult(ros::Duration(60.0));

    action_client2.sendGoal(goal2);
    action_client2.waitForResult(ros::Duration(60.0));

    if(action_client.getState()==actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Current angle State: %s \n",action_client.getState().toString().c_str());
}
    if(action_client2.getState()==actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Current velocity State: %s \n",action_client2.getState().toString().c_str());
}


}

  if(msg->distance ==7800){
    ros::ServiceClient client =nh.serviceClient<mid_proj::OnService>("Engine_on");
    mid_proj::OnService srv;
    srv.request.on =true;

    if(client.call(srv)){
      ROS_INFO("Engine_on");
    }else {
      ROS_ERROR("failed");
    }
  }

}

void MySpCallback(const mid_proj::MyState::ConstPtr&msg5)
{
  ROS_INFO(" I got it. ");

  if(msg5->move==true){
    ros::NodeHandle nh;

    ros::Publisher MySp_pub = nh.advertise<mid_proj::MyState>("okay",1000);

    ros::Rate loop_rate(10);
    mid_proj::MyState msg4;


    while (ros::ok()){

      msg4.move = true;
      msg4.existence_count = 1;

      ROS_INFO_STREAM("move: "<<msg4.move <<", existence_count: "<< msg4.existence_count);

      MySp_pub.publish(msg4);

      ros::spinOnce();
      loop_rate.sleep();

}
    }else{
      ROS_INFO("failed ");
          }

  }


int main(int argc, char **argv) {
  ros::init(argc,argv,"ObstacleSpas_ECU");
  ros::NodeHandle nh;



  ros::Subscriber MySp_sub = nh.subscribe("Im_out",1000,MySpCallback);
ros::Subscriber Ob_Ultra_sub = nh.subscribe("Obstacle_Location_2",1000,locationCallback);


  ros::spin();

  return 0;
}
