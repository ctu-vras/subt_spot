# subt_spot

This is an integration package between SubT challenge solution code and robots
based on the `BOSDYN_SPOT` platform.

The package is created by team CTU-CRAS-Norlab, but other teams are encouraged to
either use it as it is, or fork it and make their custom changes. The motion controller
provided by this package is very basic, so there is need for improvement to make the
robot actually useful.

## Installation

This package depends on the `bosdyn_spot` package, which is a part of the [SubT virtual
simulator](https://github.com/osrf/subt). So it is best if you take the simulator image as a base for your workspace.

For control, library [CHAMP](https://github.com/chvmp/champ) is supported by this package.
You will need the https://github.com/chvmp/champ repo in your workspace. For convenience,
also add https://github.com/chvmp/champ_teleop .

The set of CHAMP dependencies is described in file [dependencies.rosinstall](). This file
can be automatically used in `wstool` and `vcstools`.

After you get all the required repositories in your workspace, install their dependencies:

    rosdep install --from-paths src --ignore-src -r

And then build you workspace as usual.

## Interface

The integration with CHAMP provides a simple interface exposing `cmd_vel` topic for
controlling the motion of the robot. Topic `body_pose` of type `geometry_msgs/Pose`
controls the pose of the body relative to the ground.

CHAMP also computes a basic odometry which publishes frame `odom`.

Please note that CHAMP is an open-loop controller and has no feedback
other than the direct positional feedback in joints which is utilized in PIDs of
the positional controllers of each joint. But this is a kind of low-level feedback and
it doesn't take into account the pose of the whole body to prevent the robot from falling. 

For detailed instructions on how to control at a lower level (each joint separately),
please refer to `specifications.md` in the `bosdyn_spot` package.