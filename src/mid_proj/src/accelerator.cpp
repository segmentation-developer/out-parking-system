#include "ros/ros.h"
#include "mid_proj/OnService.h"
#include "actionlib/server/simple_action_server.h"
#include "mid_proj/OnActionAction.h"
#include "mid_proj/ObstacleMsg.h"


typedef actionlib::SimpleActionServer<mid_proj::OnActionAction> Server;

void execute(const mid_proj::OnActionGoalConstPtr& goal2 ,Server* as) {

  ros::Rate r(1);
  bool success=true;

  mid_proj::OnActionFeedback feedback;
  mid_proj::OnActionResult result;


  for(int count=0 ; count>=goal2->order ; count++){

/*
    if(as->isPreemptRequested() || !ros::ok()){
      ROS_INFO("preempted");
      as->setPreempted();
      success=false;
      break;
    }
    */


    feedback.sequence = count;
    as->publishFeedback(feedback);

    r.sleep();

}

  if(success){
    result.sequence = feedback.sequence;
    ROS_INFO("velocity control complete.");
    as->setSucceeded(result);
  }
}



int main(int argc, char** argv) {

  ros::init(argc,argv,"accelerator");
  ros::NodeHandle nh;
  Server server(nh,"desired_velocity",boost::bind(&execute,_1,&server),false);
  server.start();
  ros::spin();
  return 0;

}
