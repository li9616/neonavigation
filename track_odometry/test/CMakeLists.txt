catkin_add_gtest(test_tf_projection src/test_tf_projection.cpp)
target_link_libraries(test_tf_projection ${catkin_LIBRARIES})

add_rostest_gtest(test_track_odometry
  test/track_odometry_rostest.test
  src/test_track_odometry.cpp
)
target_link_libraries(test_track_odometry ${catkin_LIBRARIES})
add_dependencies(test_track_odometry track_odometry)
