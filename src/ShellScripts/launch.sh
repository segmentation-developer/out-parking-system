#!/bin/bash
gnome-terminal -e "roscore" &
sleep 3
gnome-terminal -e "rosrun mid_proj MyVehicle_ECU __ns:=My" &
sleep 3
gnome-terminal -e "rosrun mid_proj MySpas_ECU __ns:=My" &
sleep 3
gnome-terminal -e "rosrun mid_proj Ultra_sensor __ns:=My" &
sleep 3
gnome-terminal -e "rosrun mid_proj Ob_Ultra_sensor __ns:=Other" &
sleep 3
gnome-terminal -e "rosrun mid_proj ObstacleSpas_ECU __ns:=Other" &
sleep 3
gnome-terminal -e "rosrun mid_proj MDPS __ns:=Other" &
gnome-terminal -e "rosrun mid_proj accelerator __ns:=Other" &
sleep 3
gnome-terminal -e "rosrun mid_proj Engine __ns:=Other" &

sleep 4
gnome-terminal -e "rqt_graph"
