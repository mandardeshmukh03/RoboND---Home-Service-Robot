#!/bin/sh

#launching turtlebot_world.lauch file to deploy turtlebot in myworld
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../../src/map/myhome.world" &

sleep 10

# launching gmapping_demo.launch to perfrom SLAM
xterm -e "cd $(pwd)/../..;
source devel setup.bash;
roslaunch turtlebot_gazebo gmapping_demo.launch" &

sleep 10

# launching view_navigation 
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 10

#launching teleop_keyboard 
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_teleop keyboard_teleop.launch" &


