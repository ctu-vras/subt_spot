#include <ros/ros.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

#include <bosdyn_spot/LogicalContact.h>
#include <champ_msgs/ContactsStamped.h>
#include <mutex>

namespace subt_spot
{

class ChampContactSensor : public nodelet::Nodelet
{
  virtual void onInit()
  {
    this->champPub = this->getNodeHandle().advertise<champ_msgs::ContactsStamped>(
      "foot_contacts", 10);
    this->rosSub = this->getNodeHandle().subscribe<bosdyn_spot::LogicalContact>(
      "leg_contacts", 10, &ChampContactSensor::OnMsg, this);
  }

  protected: void OnMsg(const bosdyn_spot::LogicalContactConstPtr& msg)
  {
    champ_msgs::ContactsStampedPtr champMsg;
    champMsg.reset(new champ_msgs::ContactsStamped);

    champMsg->header = msg->header;
    champMsg->contacts = msg->contacts;

    this->champPub.publish(champMsg);
  }

  protected: ros::Publisher champPub;
  protected: ros::Subscriber rosSub;
};

}

PLUGINLIB_EXPORT_CLASS(subt_spot::ChampContactSensor, nodelet::Nodelet)