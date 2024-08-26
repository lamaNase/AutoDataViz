cmake_minimum_required(VERSION 3.10)
project(AutoDataViz)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Find the Qt5 package
find_package(Qt5 COMPONENTS Core Widgets WebEngineWidgets REQUIRED)

# Add executable
add_executable(AutoDataViz 
    main.cpp 
    ./clock/clock.cpp 
    ./Sensors/sources/camera.cpp  
    ./Runner/runner.cpp 
    ./DataSources/sources/cameraData.cpp 
    ./Sensors/sources/gps.cpp 
    ./DataSources/sources/gpsData.cpp 
    ./Sensors/sources/imu.cpp 
    ./DataSources/sources/imuData.cpp 
    ./Sensors/sources/stearing.cpp 
    ./DataSources/sources/stearingData.cpp 
    ./Sensors/sources/speed.cpp 
    ./DataSources/sources/speedData.cpp 
    ./Sensors/sources/throttle.cpp 
    ./DataSources/sources/throttleData.cpp 
    ./Sensors/sources/brake.cpp 
    ./DataSources/sources/brakeData.cpp 
    ./GUI/ui.cpp)

# Link OpenCV and Qt5 libraries
target_link_libraries(AutoDataViz 
    ${OpenCV_LIBS} 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::WebEngineWidgets)

