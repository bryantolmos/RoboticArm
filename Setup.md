# Ur10 Gazebo Simulation & Rviz

# Setup Guide

## Bryant Olmos Group-CSE32 4

**System Requirements:**

Ubuntu 22.
8GB RAM - although 16GB of RAM or more is highly recommended
NVIDIA Hardware
**Software Stack:**


Ros 2 Humble:
Installation guide link, when installing ROS2 before running the following command:
```
sudo apt install ros-humble-desktop
```

Make sure to replace the command with the following:
```
sudo apt install ros-humble-desktop-full
```

Additionally don't forget to run the following as well:
```
sudo apt install ros-dev-tools
```

MoveIt 2:
Run the following command:
```
sudo apt install ros-humble-moveit
```

Gazebo:
Installation guide link
Rosdep:
Run the following commands:
```
sudo apt install python3-rosdep
sudo rosdep init
rosdep update
sudo apt update
sudo apt dist-upgrade
```

Colcon with Mixin:
Run the following commands
```
sudo apt install python3-colcon-common-extensions
sudo apt install python3-colcon-mixin
colcon mixin add default https://raw.githubusercontent.com/colcon/colcon-mixin-
repository/master/index.yaml
colcon mixin update default
```

Vcstool:
Run the command:
```
sudo apt install python3-vcstool
```

**Creating & Sourcing Workspace:**

Next we must create a workspace were all repositories and packages will go, run the
following commands:
```
mkdir -p ~/{workspace name here}/src

colcon build

echo “source /opt/ros/humble/setup.bash” >> ~/.bashrc

echo “source ~/{workspace name}/install/setup.bash ” >> ~/.bashrc

source ~/.bashrc
```

**Package Installation & Dependency Management**

First we install the MongoDB libraries which are required for MoveIt’s persistent storage

```
sudo apt install libmongoc-dev libbson-dev
```


We then install some additional ROS2 required dependencies
```
sudo apt install ros-humble-gazebo-ros-pkgs
```

...
Note: if you get an error run the following commands:
```
sudo apt install aptitude
sudo aptitude install ros-humble-gazebo-ros-pkgs
```
...

```
sudo apt install ros-humble-ros2-control
sudo apt install ros-humble-velocity-controllers
sudo apt install ros-humble-moveit
```

Now we clone the following git repositories into the src/ directory in your workspace

```
git clone -b humble
https://github.com/UniversalRobots/Universal_Robots_ROS2_Description.git
git clone -b humble
```

```
https://github.com/UniversalRobots/Universal_Robots_ROS2_Driver.git
git clone -b humble
```

```
https://github.com/UniversalRobots/Universal_Robots_ROS2_Gazebo_Simulation.git
```


After cloning these repositories into source directory we run the following command to
ensure any additional ROS dependencies are installed successfully
```
cd .. && rosdep install --from-paths src --ignore-src -y
```



Finally we build our packages with the following command, make sure you build in the root
folder of your workspace
```
colcon build --mixin release
```


**Launching Gazebo & MoveIt**

First we need to launch gazebo:
```
source ~/.bashrc
```

```
ros2 launch ur_simulation_gazebo ur_sim_control.launch.py ur_type:=ur
launch_rviz:=false use_fake_hardware:=true
initial_joint_controller:=joint_trajectory_controller
```
In a new terminal launch MoveIt2:
```
source ~/.bashrc
```

```
ros2 launch ur_moveit_config ur_moveit.launch.py ur_type:=ur10 launch_rviz:=true
use_fake_hardware:=true use_sim_time:=true
```


**Testing Basic Motion Planning**

In Rviz use the planning tab, set the start state to “current”, drag the interactive marker on
the ur10 to set a goal pose, click on “Plan and Execute”, and you should see the ur10 robot
move in Rviz aswell as Gazebo


