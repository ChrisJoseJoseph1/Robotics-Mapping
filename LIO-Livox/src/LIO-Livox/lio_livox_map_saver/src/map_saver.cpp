#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl_conversions/pcl_conversions.h>

#include <mutex>
#include <string>

using PointType = pcl::PointXYZI;

pcl::PointCloud<PointType>::Ptr accumulated_map(new pcl::PointCloud<PointType>());
std::mutex map_mutex;

std::string output_pcd;
double voxel_leaf_size;
int frame_count = 0;

void cloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
    pcl::PointCloud<PointType>::Ptr current_cloud(new pcl::PointCloud<PointType>());

    try
    {
        pcl::fromROSMsg(*msg, *current_cloud);
    }
    catch (const std::exception& e)
    {
        ROS_WARN("Failed to convert cloud: %s", e.what());
        return;
    }

    if (current_cloud->empty())
    {
        ROS_WARN("Received empty cloud. Skipping.");
        return;
    }

    {
        std::lock_guard<std::mutex> lock(map_mutex);
        *accumulated_map += *current_cloud;
        frame_count++;
    }

    if (frame_count % 50 == 0)
    {
        ROS_INFO("Accumulated %d frames, current total points: %lu",
                 frame_count,
                 accumulated_map->points.size());
    }
}

void saveMap()
{
    std::lock_guard<std::mutex> lock(map_mutex);

    if (accumulated_map->empty())
    {
        ROS_WARN("Accumulated map is empty. Nothing to save.");
        return;
    }

    pcl::PointCloud<PointType>::Ptr map_to_save(new pcl::PointCloud<PointType>());

    if (voxel_leaf_size > 0.0)
    {
        ROS_INFO("Downsampling accumulated map with voxel leaf size: %.3f m", voxel_leaf_size);

        pcl::VoxelGrid<PointType> voxel_filter;
        voxel_filter.setInputCloud(accumulated_map);
        voxel_filter.setLeafSize(voxel_leaf_size, voxel_leaf_size, voxel_leaf_size);
        voxel_filter.filter(*map_to_save);
    }
    else
    {
        *map_to_save = *accumulated_map;
    }

    map_to_save->width = map_to_save->points.size();
    map_to_save->height = 1;
    map_to_save->is_dense = false;

    ROS_INFO("Saving map to: %s", output_pcd.c_str());
    ROS_INFO("Frames accumulated: %d", frame_count);
    ROS_INFO("Raw accumulated points: %lu", accumulated_map->points.size());
    ROS_INFO("Saved points: %lu", map_to_save->points.size());

    int result = pcl::io::savePCDFileBinary(output_pcd, *map_to_save);

    if (result == 0)
    {
        ROS_INFO("PCD map saved successfully.");
    }
    else
    {
        ROS_ERROR("Failed to save PCD file.");
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "lio_livox_map_saver");
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    std::string input_topic;

    private_nh.param<std::string>("input_topic", input_topic, "/livox_full_cloud_mapped");
    private_nh.param<std::string>("output_pcd", output_pcd, "/root/rosbags/lio_livox_accumulated_map.pcd");
    private_nh.param<double>("voxel_leaf_size", voxel_leaf_size, 0.05);

    ROS_INFO("LIO-Livox map saver started.");
    ROS_INFO("Subscribing to: %s", input_topic.c_str());
    ROS_INFO("Output PCD: %s", output_pcd.c_str());
    ROS_INFO("Voxel leaf size: %.3f m", voxel_leaf_size);

    ros::Subscriber sub = nh.subscribe(input_topic, 10, cloudCallback);

    ros::spin();

    saveMap();

    return 0;
}
