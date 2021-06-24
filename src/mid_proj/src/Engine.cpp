#include "ros/ros.h"
#include "mid_proj/OnService.h"

bool Engine(mid_proj::OnService::Request &req,mid_proj::OnService::Response &res){
  res.okay=false;
  if(req.on ==true){
    ROS_INFO("okay. Engine on");
    res.okay=true;
  }

  return res.okay;
}


int main(int argc, char **argv){
  ros::init(argc, argv,"Engine");
  ros::NodeHandle nh;

  ros::ServiceServer service =nh.advertiseService("Engine_on",Engine);
  ROS_INFO("");
  ros::spin();

  return 0;

}
