#!/bin/bash

end()
{
    echo -e "... finishing ...\n"
    pkill -9 ros_rpc_server
    pkill -9 gzclient
    pkill -9 gzserver
    pkill -9 robot_state_publisher
    pkill -9 spawn_model
    pkill -9 mobile_base
    pkill -9 cmd_vel_mux
    pkill -9 bumper2point
    pkill -9 laserscan
    pkill -9 depthimage
    pkill -9 nodelet
    pkill -9 gazebo
    pkill -9 roslaunch
    pkill -9 rosout
    pkill -9 rosmaster
    exit
}

trap "end" 2 3
#roslaunch turtlebot_gazebo turtlebot_world.launch &
#sleep 10
#rosrun nodo_comunicacion ros_rpc_server &
#sleep 5
if [ $# -gt 0 ]; then
    bin/pddl_executor $1
else
    bin/pddl_executor config/pddlconfig
fi

read -p "Press any key to finish" -n1 -s
end
