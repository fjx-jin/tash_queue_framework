source /opt/ros/iron/setup.bash
colcon build --cmake-args  \
        '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON' \
        '-DCMAKE_BUILD_TYPE=Debug' \
        '-DBUILD_TESTING=ON' \
        --packages-select $*
        # '-DSIMU_MOCK=OFF' \
source ./install/setup.bash
