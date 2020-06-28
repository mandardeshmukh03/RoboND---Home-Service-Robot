#!/bin/sh

#launching turtlebot
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/../../src/map/myhome.world" &

sleep 5;

#lainching amcl_demo.launch
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/../../src/map/map.yaml" &

sleep 2;

#launching rviz
xterm -e " cd $(pwd)/../..;
source devel/setup.bash;
roslaunch turtlebot_rviz_launchers view_navigation.launch"  &

sleep 10

#launch add_markers node
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
rosrun add_markers add_markers" &

sleep 10

# launch pick_objects node
xterm -e "cd $(pwd)/../..;
source devel/setup.bash;
rosrun pick_objects pick_objects" &
