#include<ros/ros.h>
#include<visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include<complex>

float pickedup = false;
float delivered = false;
float pickuplocation = false;
float deliverylocation = false;
nav_msgs::Odometry odm;
double botpose_x, botpose_y, botpose_z;
double botornt_x, botornt_y, botornt_z, botornt_w;

void Objectproxy( const nav_msgs::Odometry::ConstPtr& msg)
{
  odm = *msg;
  if ( botpose_x == odm.pose.pose.position.x &&
       botpose_y == odm.pose.pose.position.y &&
       botpose_z == odm.pose.pose.position.z &&
       botornt_x == odm.pose.pose.orientation.x &&
       botornt_y == odm.pose.pose.orientation.y && 
       botornt_z == odm.pose.pose.orientation.z &&
       botornt_w == odm.pose.pose.orientation.w )
       {
         pickuplocation = true;
       }  
  if ( botpose_x == odm.pose.pose.position.x &&
       botpose_y == odm.pose.pose.position.y &&
       botpose_z == odm.pose.pose.position.z &&
       botornt_x == odm.pose.pose.orientation.x &&
       botornt_y == odm.pose.pose.orientation.y && 
       botornt_z == odm.pose.pose.orientation.z &&
       botornt_w == odm.pose.pose.orientation.w ) 
       {
         deliverylocation = true;
       }  
  
  return;
}   
  

int main(int argc, char** argv)
   {
     ros::init(argc, argv, "add_markers");
     ros::NodeHandle n;
     ros::Rate r(1);
     ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
     ros::Subscriber odom_sub = n.subscribe("odom", 100, Objectproxy); 
   
      // Set shape of the object to be a cube
     uint32_t shape = visualization_msgs::Marker::CUBE;
  
     while (ros::ok())
     {
       visualization_msgs::Marker marker;
        //Set the frame ID and timestamp
       marker.header.frame_id = "map";
       marker.header.stamp = ros::Time::now();
       
        //Set the namespace and id
       marker.ns = "add_marker";
       marker.id = 0;
       
        //Set the marker type
       marker.type = shape;
       
        //Set the marker action
       marker.action = visualization_msgs::Marker::ADD;
       
        //Set the pose of the marker
      marker.pose.position.x = 4.0;
      marker.pose.position.y = 6.0;
      marker.pose.position.z = 0;
    
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;

       // Set the scale of the marker
      marker.scale.x = 0.8;
      marker.scale.y = 0.8;
      marker.scale.z = 0.8;

       // Set the color 
      marker.color.r = 1.0f;
      marker.color.g = 0.0f;
      marker.color.b = 0.0f;
      marker.color.a = 1.0;

      marker.lifetime = ros::Duration();

       // Publish the marker
      while (marker_pub.getNumSubscribers() < 1)
      {
        if (!ros::ok())
         {
          return 0;
         }
         ROS_WARN_ONCE("Please create a subscriber to the marker");
         sleep(1);
       }
    
       marker_pub.publish(marker);
       
       
       
       if ((pickuplocation = true) && (pickedup = false))
         {
           ROS_INFO("Robot reached pick up location");
           marker.action = visualization_msgs::Marker::DELETE;
           marker_pub.publish(marker);
           pickedup = true;
         }
       
       if ((deliverylocation = true) && (delivered = false))
         {
          ROS_INFO("Robot deliverying the object at the delivery location");
           //Adding the marker 
          marker.action = visualization_msgs::Marker::ADD;
           //Providing the delivery location
          marker.pose.position.x = 8.0;
          marker.pose.position.y = 8.0;
          marker.pose.position.z = 0.0;
          marker.pose.orientation.x = 0.0;
          marker.pose.orientation.y = 0.0;
          marker.pose.orientation.z = 0.0;
          marker.pose.orientation.w = 1.0;
         
           // Set the scale of the marker
          marker.scale.x = 0.8;
          marker.scale.y = 0.8;
          marker.scale.z = 0.8;

           // Set the color 
          marker.color.r = 1.0f;
          marker.color.g = 0.0f;
          marker.color.b = 0.0f;
          marker.color.a = 1.0;

         
           // Publishing the marker
          marker_pub.publish(marker);
          delivered = true;
          ROS_INFO("Robot delivered the object at the delivery location");
          sleep(5.0);
         }
       
         return 0;
     }
   }
         
         