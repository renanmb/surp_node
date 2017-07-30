#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>

class Link{
   public:
     Link(); //error: ISO C++ forbids declaration of ‘Imu’ with no type [-fpermissive]

   private:
     void velLinearCallback(const std_msgs::Float32::ConstPtr& vx);
     void velAngularCallback(const std_msgs::Float32::ConstPtr& wz);
     void encoderCallback(const std_msgs::Int32::ConstPtr& tk);
     ros::NodeHandle nh;
     ros::Publisher pub;
     ros::Subscriber velLinear_x_sub;
     ros::Subscriber velAngular_z_sub;
     ros::Subscriber encoder_sub;
     geometry_msgs::Twist vel;
     std_msgs::Int32 encoder;
};

//This will change when add the TF and pose 
Link::Link(){ //error: ISO C++ forbids declaration of ‘Imu’ with no type [-fpermissive]
   pub = nh.advertise<geometry_msgs::Twist> ("turtle1/cmd_vel", 1 );
   pub = nh.advertise<std_msgs::Int32> ("/encoder", 10);
   velLinear_x_sub = nh.subscribe<std_msgs::Float32> ("/accel_x", 1, &Link::velLinearCallback, this);
   velAngular_z_sub = nh.subscribe<std_msgs::Float32> ("/accel_z", 1, &Link::velAngularCallback, this);
   encoder_sub = nh.subscribe<std_msgs::Int32> ("encoder", 10, &Link::encoderCallback, this);
}

//Encoder receives "encoder" and publish topic "/encoder" in Int32

void Link::velLinearCallback(const std_msgs::Float32::ConstPtr& vx){
   vel.angular.z = vx->data;
   pub.publish(vel);
}

void Link::velAngularCallback(const std_msgs::Float32::ConstPtr& wz){
   vel.linear.x = -1 * wz->data;
   pub.publish(vel);
}

void Link::encoderCallback(const std_msgs::Int32::ConstPtr& tk){
   
   encoder.data = tk->data; //  error: ‘encoder’ was not declared in this scope encoder = tk->data;
   pub.publish(encoder); //need to review how to do this
}

int main(int argc, char** argv){
   ros::init(argc, argv, "commlink");
   Link Link; //object did not understand why
   ros::spin();
}
