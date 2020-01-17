#include "driver.h"

void filterVelocityCallback(const geometry_msgs::Twist &msg) {

	int vitesse = abs(msg.linear.x);
	char sens;

	if (msg.linear.x == 0)
	{
		if (msg.angular.z > 0)
		{
			sens = 'q';
		}
		else if (msg.angular.z < 0)
		{
			sens = 'd';
		}
	} else {
		sens = msg.linear.x > 0 ? 'a' : 'r';
	}

	if (msg.linear.x == 200) {
	    ROS_INFO_STREAM("stop_motor and shutdown");
		stop_servo_motor();
		stop_motor();

		ros::shutdown();
	} else if (msg.linear.x == 0 && msg.angular.z == 0) {
	    ROS_INFO_STREAM("stop_motor");
		stop_servo_motor();
		stop_motor();

		init_motor();
	} else {
		ROS_INFO_STREAM("set_motor : angle = " << msg.angular.z << " - vitesse = " << vitesse << " - sens = " << sens);

		// Angle, Vitesse 0~100, Sens a-r-q-d
		set_servo_motor(msg.angular.z);
		set_motor(vitesse, sens);
	}
}

int main(int argc, char ** argv) {
  // Initialisation ROS
  ros::init(argc, argv, "driver");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("cmd_vel", 1000, &filterVelocityCallback);

  // Initialisation Lib Pi GPIO
  putenv("WIRINGPI_GPIOMEM=1");
  wiringPiSetup();

  // Initialisation Lib pca9685
  int fd = pca9685Setup(PIN_BASE, 0x40, FREQUENCE);

  if (fd < 0) {
    printf("Error in initialisation of Lib pca9685\n");
    return fd;
  }

  // Reset all output
  pca9685PWMReset(fd);

  init_motor();

  ROS_INFO_STREAM("init_motor");

  ros::spin();

  return 0;
}
