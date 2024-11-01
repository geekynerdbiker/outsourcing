cmake_minimum_required(VERSION 3.0.2)
project(cpp-ros)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp geometry_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_1c src/1c.cpp)
target_link_libraries(${PROJECT_NAME}_1c ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_1oop src/1oop.cpp)
target_link_libraries(${PROJECT_NAME}_1oop ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_2c src/2c.cpp)
target_link_libraries(${PROJECT_NAME}_2c ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_2oop src/2oop.cpp)
target_link_libraries(${PROJECT_NAME}_2oop ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_3c src/3c.cpp)
target_link_libraries(${PROJECT_NAME}_3c ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_3oop src/3oop.cpp)
target_link_libraries(${PROJECT_NAME}_3oop ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_4c src/4c.cpp)
target_link_libraries(${PROJECT_NAME}_4c ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_4oop src/4oop.cpp)
target_link_libraries(${PROJECT_NAME}_4oop ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_5c src/5c.cpp)
target_link_libraries(${PROJECT_NAME}_5c ${catkin_LIBRARIES})
 
add_executable(${PROJECT_NAME}_5oop src/5oop.cpp)
target_link_libraries(${PROJECT_NAME}_5oop ${catkin_LIBRARIES})
