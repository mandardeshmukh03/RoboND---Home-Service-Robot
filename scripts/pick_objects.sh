#!/bin/sh

# launch turtlebot_world.launch to deploy turtlebot environment
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_gazebo turtlebot_world.launch  world_file:=$(pwd)/../../src/map/myhome.world " & 

sleep 10

# launch amcl_demo.launch for localization
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../../src/map/map.yaml " &

sleep 10

# launch view_navigation for rviz
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 10

# launch pick_objects node
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
rosrun pick_objects pick_objects " &