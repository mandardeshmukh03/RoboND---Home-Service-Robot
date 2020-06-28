#!/bin/sh

#launching turtlebot_world.launch
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../../src/map/myhome.world" &

sleep 10

#launching amcl_demo.launch
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../../src/map/map.yaml" &

#launching view_navigation for rviz
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 10

#launch add_markers node
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
rosrun add_markers add_markers" &