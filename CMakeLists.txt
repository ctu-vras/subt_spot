cmake_minimum_required(VERSION 3.0.2)
project(subt_spot)

find_package(catkin REQUIRED COMPONENTS
  bosdyn_spot
  champ_msgs
  nodelet
  roscpp
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_library(champ_contact_sensor src/champ_contact_sensor.cc)
add_dependencies(champ_contact_sensor ${catkin_EXPORTED_TARGETS})
target_link_libraries(champ_contact_sensor ${catkin_LIBRARIES})

install(TARGETS champ_contact_sensor
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(FILES nodelets.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})