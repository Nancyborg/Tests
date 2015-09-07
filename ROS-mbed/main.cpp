#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <Odometry.h>

const PinName LEFT_WHEEL_ENCODER_A = p25;
const PinName LEFT_WHEEL_ENCODER_B = p26;
const PinName RIGHT_WHEEL_ENCODER_A = p15;
const PinName RIGHT_WHEEL_ENCODER_B = p16;

ros::NodeHandle nh;
QEI *left_wheel, *right_wheel;
Odometry *odometry;

int pulses_per_revolution[2]; // left and right pulses per revolution
float wheels_radius[2];       // left and right wheels radius
float wheels_distance;        // distance between wheels

void velocityCmd(const geometry_msgs::Twist& twist_msg) {
    nh.loginfo("twist received");
}

int main(void) {
    tf::TransformBroadcaster tf;
    geometry_msgs::TransformStamped odom_trans;
    ros::Subscriber<geometry_msgs::Twist> velSub("cmd_vel", &velocityCmd);

    nh.initNode();
    while (!nh.connected()) { nh.spinOnce(); }

    nh.loginfo("MBED ready.");

    nh.getParam("~wheels_radius",         wheels_radius, 2);
    nh.getParam("~pulses_per_revolution", pulses_per_revolution, 2);
    nh.getParam("~wheels_distance",       &wheels_distance, 1);

    left_wheel = new QEI(LEFT_WHEEL_ENCODER_A, LEFT_WHEEL_ENCODER_B, NC, pulses_per_revolution[0]);
    right_wheel = new QEI(RIGHT_WHEEL_ENCODER_A, RIGHT_WHEEL_ENCODER_B, NC, pulses_per_revolution[1]);
    odometry = new Odometry(left_wheel, right_wheel, wheels_radius[0], wheels_radius[1], wheels_distance);

    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    nh.subscribe(velSub);
    tf.init(nh);

    while (1) {
        odom_trans.transform.translation.x = odometry->getX();
        odom_trans.transform.translation.y = odometry->getY();
        odom_trans.transform.rotation = tf::createQuaternionFromYaw(odometry->getTheta());
        odom_trans.header.stamp = nh.now();
        tf.sendTransform(odom_trans);

        nh.spinOnce();
        wait_ms(1);
    }
}
