#!/bin/sh

#launching turtlebot_world.lauch file to deploy turtlebot in myworld
xterm -e "cd $(pwd)/../..;
souce devel/setup.bash;
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../../src/map/myhome.world" &

sleep 10

#launching amcl_demo.launch to localize turtlebot
xterm -e "cd $(pwd)/../../;
source devel/setup.bash;
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../../src/map/map.yaml" &

sleep 10

#launching view_navigation.launch to observe the map
xterm -e "cd $(pwd)/../..;
cd source devel/setup.bash;
roslaunch turtlebot_rviz_launchers view_navigation.launch " &