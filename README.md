# Second_Assignment
--------------------

INTRODUCTION, MATERIAL AND METODS:
------------------------------------

This is the second assignment of Research Track I,
the goal this assignment is to learn to use ROS and in this assignment,
it was given to as a circuit where there is a point who represent the robot.
The robot is equipped with a laser scanner 
who detect al obstacle to a maximum distance of 30 and an angle that ranging from -π/2 to π/2 radians, the increment of angle it is approximately of 0.04 radians and all date is stoked in an array named ranges[] so this array have 720 data (π/0.04), where the first 360 data is the data from the right side and the last 360 data from the left side.
 
In this assignment we are put in practice what we learned in class, we are create 2 node /controller_n1 and /controller_n,
the first one communicate with the node of simulator /stageros,
where publishing in it the linear velocity in topic /cmd_vel and subscribe in in topic /base_scan 
who take information about laser scanner,
whit this information the robot decide to turn left or right for dodge the obstacle,
this  node use another topic /usercontrol (from the second node ) where receive the message to reset,
increase or decrease the speed;
the second node take the input from user and 
if this input is “e”/”d” send a msg at the first controller to increase/decrease  speed,
and if the input is “r” the node call the service /reset_positions for reset the position of robot and reset the speed to 0 and,
if the input is “s” the node break the execution.
In the and we are make a lunch file that use to launch the node that form the  simulator.

What is ROS?
------------

ROS (Robot Operating System) provides libraries and tools to help software developers create robot applications.
It provides hardware abstraction, device drivers, libraries, visualizers, message-passing, package management and more. 
Substantially, ROS is a set of node that communicate between them and are coordinate by roscore (node master);
the node are script (in py or cpp) that can communicate between them in two way,
whit topic(publisher/subscriber) or service(request/reply). 

PSEUDOCOD:
------------
____________

In the script usercont.cpp that represent the node controller_n:
---
_______________________________________

Declared global variable a who represent speed;                                         
Declared publisher pub;                                         
Defined the function setspeed(char w) that the input from user,                                         
and if this input is “e”/”d”/”r” send an inter to the other node to increase/decrease/reset speed and give ta user,                     
information about speed; 

______________
In the main():
______________

Defined the node;                                                                                  
Defined the node handler;                                                                                  
Defined the publisher;                                                                                  
Defined the client;                                                                                  
Defined and set the Serviceclient;                                                                                  
Starting while  a loop no endless;                                                                                  
Declared the variable s who take the data from user;                                                                                  
Put the data into the function setspeed();                                                                                  
If user enter “r”, call the serviceclient /reset_positions to set the position of the robot;                                                                            
If user enter “s”, stop the execution of node;                                                                                    
  
In the script control.cpp that represent the node controller_n1:
---
_____________________________________________

Declared the global variable dR, dL, a                                         
that represent the data from laser scanner for right side (dR), left side(dL) and the data for speed.                                         
Declared the publisher pub;                                         
Defined he function the function laserscan(),                                         
that take the information from the topic /base_scan to analyze the left and right side and,
publishing velocity in the topic /cmd_vel,                                         
if dR <0.9 and the rightmost data < the leftmost data the robot turn left;                                         
if idL <0.9 and the rightmost data > the leftmost data the robot turn right;                                         
Defined the function usercont(),                                         
that take information data from /usercont topic and                                         
if data is 1 increase sped of +0.2,                                         
if data is -1 decrease speed of -0.2,                                         
if data is 0 reset speed to 0, in the end print speed.                                         

____________________
In the main():
____________________

defined the node controller_n1;                                                                                  
Defined the node handler nh1;                                                                                  
Defined the publisher pub;(the publisher send data to the node /stageros)                                                                                   
Starting while a loop no endless; (ros::ok() it mean stop when we send signal to stop ctrl-c)                                         
Defined the subscriber that use the function to menage the data.                                                                                  

INSTALLING AND RUNNING:
---
_________


After the installation of ROS,(I use a linux(Ubuntu 20.04) operator sistem), you shoud be create your work space;

```bash
$ mkdir –p/my_ros_ws/src
 $ cd –p/my_ros_ws/src
```
Dowload the folder where there are the node, Cmakelist, pakage and the launch file;

```bash

```
You must be go inside the folder(the same folder where is present the lunch file),
if you want to launch the simulato whit launch file and not manualy.
In the end enter this:

```bash
$ roslaunch launch.launch
```
