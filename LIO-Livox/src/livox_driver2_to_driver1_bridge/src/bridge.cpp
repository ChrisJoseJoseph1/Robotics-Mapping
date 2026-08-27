#include <ros/ros.h>

#include <livox_ros_driver/CustomMsg.h>
#include <livox_ros_driver/CustomPoint.h>

#include <livox_ros_driver2/CustomMsg.h>
#include <livox_ros_driver2/CustomPoint.h>

ros::Publisher pub;

void callback(const livox_ros_driver2::CustomMsgConstPtr& in)
{
    livox_ros_driver::CustomMsg out;

    out.header = in->header;
    out.timebase = in->timebase;
    out.point_num = in->point_num;
    out.lidar_id = in->lidar_id;
    out.rsvd = in->rsvd;

    out.points.resize(in->points.size());

    for (size_t i = 0; i < in->points.size(); ++i)
    {
        out.points[i].offset_time = in->points[i].offset_time;
        out.points[i].x = in->points[i].x;
        out.points[i].y = in->points[i].y;
        out.points[i].z = in->points[i].z;
        out.points[i].reflectivity = in->points[i].reflectivity;
        out.points[i].tag = in->points[i].tag;
        out.points[i].line = in->points[i].line;
    }

    pub.publish(out);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "livox_driver2_to_driver1_bridge");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/livox/lidar_raw_driver2", 100, callback);
    pub = nh.advertise<livox_ros_driver::CustomMsg>("/livox/lidar", 100);

    ROS_INFO("Livox driver2 to driver1 bridge started.");
    ROS_INFO("Subscribing: /livox/lidar_raw_driver2 [livox_ros_driver2/CustomMsg]");
    ROS_INFO("Publishing:  /livox/lidar [livox_ros_driver/CustomMsg]");

    ros::spin();
    return 0;
}
