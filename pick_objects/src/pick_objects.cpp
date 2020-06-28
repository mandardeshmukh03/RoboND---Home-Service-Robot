#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


int main(int argc, char** argv){
  
  // Initializing the pick_objects node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  
  
  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;		

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
   ROS_INFO("Sending pick-up goal location");
   goal.target_pose.pose.position.x = 4.0;
   goal.target_pose.pose.position.y = 6.0;
   goal.target_pose.pose.position.z = 0.0;

   goal.target_pose.pose.orientation.x = 0.0;
   goal.target_pose.pose.orientation.y = 0.0;
   goal.target_pose.pose.orientation.z = 0.0;
   goal.target_pose.pose.orientation.w = 1.0;

  // Sending the goal pos and orientation 
  ac.sendGoal(goal);
  ROS_INFO("Pickup location sent to robot");

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its drop goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
   
   // Define pos and orientation for drop off location
   ROS_INFO("Sending drop-off goal location");
   goal.target_pose.pose.position.x = 8.0;
   goal.target_pose.pose.position.y = 8.0;
   goal.target_pose.pose.position.z = 0.0;

   goal.target_pose.pose.orientation.x = 0.0;
   goal.target_pose.pose.orientation.y = 0.0;
   goal.target_pose.pose.orientation.z = 0.0;
   goal.target_pose.pose.orientation.w = 1.0;

   // Sending drop off location to the robot
   ac.sendGoal(goal);
   ROS_INFO("Robot has reached drop off location");
   sleep(5);
   ROS_INFO("Robot has dropped the package");
  }
  else {
    ROS_INFO("The robot failed to reach drop-off location");
  }

  // wait a bit before next message
  ros::Duration(5.0).sleep();

  return 0;
}