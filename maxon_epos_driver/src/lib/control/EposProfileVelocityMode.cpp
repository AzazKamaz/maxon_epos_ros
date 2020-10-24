/**
 * @file   EposProfileVelocityMode
 * @brief  
 * @author arwtyxouymz
 * @date   2019-06-04 22:42:41
 */

#include "maxon_epos_driver/control/EposProfileVelocityMode.hpp"

EposProfileVelocityMode::~EposProfileVelocityMode()
{}

void EposProfileVelocityMode::init(ros::NodeHandle &motor_nh, NodeHandle &node_handle)
{
    ControlModeBase::init(motor_nh, node_handle);
}

void EposProfileVelocityMode::activate()
{
    VCS_NODE_COMMAND_NO_ARGS(ActivateProfileVelocityMode, m_epos_handle);
}

void EposProfileVelocityMode::read()
{}

void EposProfileVelocityMode::write(const double position, const double velocity, const double current)
{
    int raw_velocity;
    ROS_DEBUG_STREAM("Target Velocity: " << velocity);
    if (m_use_ros_unit) {
        raw_velocity = static_cast<int>(velocity * 30. / M_PI);
    } else {
        raw_velocity = static_cast<int>(velocity);
    }
    ROS_DEBUG_STREAM("Send Raw Velocity: " << raw_velocity);
    VCS_NODE_COMMAND(MoveWithVelocity, m_epos_handle, raw_velocity);
}
