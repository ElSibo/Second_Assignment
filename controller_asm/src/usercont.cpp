#include "ros/ros.h"
#include "std_msgs/Int8.h"	
#include"std_srvs/Empty.h"

using namespace std;
float a=0.2; // declarred the global variable who rapresent speed 
ros::Publisher pub; //declared publisher pub 

void setspeed(char w){ // we are defined function to set speed

	int f=0;
	if(w=='E' | w=='e'){f=1;a=a+0.2;cout<<"\nINcrease speed\n";}//increase speed
	if(w=='D' | w=='d'){f=-1;a=a-0.2;cout<<"\nDEcrease speed\n";}//decrease speed
	if(w=='r' | w=='R'){f=0;a=0;cout<<"\nRESET speed\n";}//reset speed
	std_msgs::Int8 vel_usr;
	vel_usr.data=f;	 //setting the data to send at the other node
	pub.publish(vel_usr);	//publishing it
	if(a>=3.6){cout<<"		WARNING: you are exceeded speed limit \n 	you can crash or somthing unxpected can happend\n";}
	if(-0.001<a & a<0.001){cout<<"\nrobot is STOPPED !!!\n";}
	if(a<-0.001){cout<<"\nyou put the REVERS GEAR!!\n";}
		
	cout<<"\nspeed = "<<a<<endl;
}

int main(int argc, char **argv){

 	ros::init(argc,argv,"controller_n");//defined the node controller_n
 	ros::NodeHandle nh; //define the nodehandeler
 	pub=nh.advertise<std_msgs::Int8>("/usercont",1);//defined the publisher
 	ros::ServiceClient client=nh.serviceClient<std_srvs::Empty>("/reset_positions");//defined the Serviceclient
 	
 	std_srvs::Empty my_reset;	//set the claint if there is a call
 	client.waitForExistence();
 	
	while(ros::ok()){ //loop no endless 
	char s;//defined the variable who take the input 
	
	cout<<"SPEED :: E:to Increase D:to Decrease\nSTOP  :: S:to Stop\nRESET :: R:to Reset\n";
	cin>>s; //take input from user
	
	setspeed(s);
	
	if(s=='R' | s=='r'){
	
		cout<<"YOU are RESET the ROBOT to iniztial position\n";
		client.call(my_reset); //call the service to reset position(/reset_positions)
	}
	
	
	if( s=='s' | s=='S'){ break; }//data to stop the signal
	
	}
	return 0;
	
	}
	
