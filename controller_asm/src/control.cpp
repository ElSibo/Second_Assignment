#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Int8.h"


using namespace std;

float dR=0;	//declared a global variable
float dL=0; //because wee need it not only in the main
float a=0.2; //but also in the other function

ros::Publisher pub; //declared the pulisher for the same reason 

	//defined the function the laserscan
void laserscan(const sensor_msgs::LaserScan::ConstPtr& msg){
	
	
	
	
	for(int i=0;i<360;i++){ dR = dR + msg->ranges[i]; }
	//do the average for all right data
	dR= dR/360;
	
	
	
	for(int i=360;i<720;i++){ dL = dL + msg->ranges[i]; }
	//do the average for all left data
	dL= dL/360;
	
	

	
	geometry_msgs::Twist my_vel;
	my_vel.linear.x = a;	//set and publish the speed for the robot
	pub.publish(my_vel);
	
	
	
	if (dR<0.9 & (msg->ranges[0])<(msg->ranges[720]) ){//parameter to turn left
	
		geometry_msgs::Twist my_vel;
		my_vel.linear.x =0.2;
		my_vel.angular.z = 10; //set and pulish the data to turn left
		pub.publish(my_vel);
	
	}
	if (dL<0.9 & (msg->ranges[0])>(msg->ranges[720]) ){//parameter to turn right
		
		geometry_msgs::Twist my_vel;
		my_vel.linear.x =0.2;
		my_vel.angular.z =-10; //set and pulish the data to turn right
		pub.publish(my_vel);
	
	}

	
	
}
	//defined the function the usercont
void usercont(const std_msgs::Int8::ConstPtr& msg){

	int n=msg->data; //reading data
	if(n==1){ a=a+0.2;}// INcrease  the speed 
	if(n==-1){a=a-0.2;}// DEcrease speed
	if(n==0){a=0;}//reset speed
	cout<<"speed = "<<a<<endl;

}

int main(int argc, char **argv){ //main
	
	
	
	ros::init(argc,argv,"controller_n1"); // defined the node /controller_n1
	ros::NodeHandle nh1;	//defined the nodehandler  
	pub = nh1.advertise<geometry_msgs::Twist>("/cmd_vel",1);//defined the pulisher
	
	
	
	while (ros::ok()){//loop no endless
	
	//defined and call  the subscribers 
	ros::Subscriber sub = nh1.subscribe("/base_scan",1,laserscan);
	ros::Subscriber sub2 = nh1.subscribe("/usercont",1,usercont);
	
	ros::spin();	
	}
	
	
	
	
	return 0;

}
