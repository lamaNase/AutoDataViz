# Real-Time Automotive Data Visualization and Analysis System 🚗

This project is a real-time automotive data visualization system designed to provide a comprehensive view of a vehicle's performance and surroundings.
By integrating data from multiple sensors, including cameras, GPS, speed, steering, IMU, brake, and throttle, the system displays a live feed of visual and
numerical information. The interface includes synchronized camera views, real-time data updates, and a Google map displaying the vehicle's current location, all
managed through a multi-threaded C++ application using Qt.

# Vehicle Data Features and Sensors 🚙 📡

## Camera Feeds 📸

The Camera Feeds feature captures and displays real-time images from the vehicle's front, back, left, and right cameras. These images provide a 360-degree visual
context of the car's surroundings, crucial for monitoring and analysis during the drive.

The challenge with this feature is handling real-time image processing efficiently, ensuring that all camera feeds are synchronized, and managing the display of
high-resolution images without affecting the overall performance of the system.


## GPS 📍

The GPS Data feature provides important information about the vehicle's location, including **longitude**, **latitude**, and **altitude**. This data is essential
for mapping the car's position in real-time and understanding its movement and elevation changes during the drive.

- **Longitude & Latitude**: To accurately track and display the vehicle's current position on a map, allowing for real-time location monitoring.
- **Altitude:** To provide information about the vehicle's elevation, which can be important in understanding terrain changes and driving conditions.


## IMU (Inertial Measurement Unit) Data 📊

The IMU Data feature provides critical information about the vehicle's motion and orientation using three primary measurements: **acceleration**, **gyroscopic
data**, and **magnetic field data**. These measurements are essential for understanding the car's dynamic behavior and stability.

- **Acceleration**: Measures the rate of change of velocity along the X, Y, and Z axes.
- **Gyroscopic Data**: Measures the rate of rotation around the X, Y, and Z axes.
- **Magnetic Field Data**: Measures the strength of the magnetic field along the X, Y, and Z axes, which can help with orientation tracking.
- **Orientation Data**: pitch, roll, yaw: Represents the vehicle's orientation in terms of pitch (tilting forward or backward), roll (tilting left or right), and
  yaw (rotation around the vertical axis). This information is essential for understanding the vehicle’s orientation and maintaining stability.


## Speed Data 🏎️

The Speed Data feature tracks and displays the vehicle's speed over time, providing real-time insights into the car's velocity during the drive. This information
is important for monitoring the vehicle's performance and behavior.


## Steering Data 🎡

The Steering Data feature provides information about the vehicle's steering angle, which is important for understanding how the car is being maneuvered. This data
helps in analyzing the driver’s input and the vehicle’s handling characteristics.


## Throttle Data 🛠️

The Throttle Data feature monitors and displays the vehicle’s throttle position, which indicates how much the driver is pressing the accelerator pedal. This data
is crucial for understanding the vehicle's acceleration and overall performance.


## Break Data 🛑

The Brake Data feature tracks and displays the vehicle’s brake status, indicating how much the driver is applying the brakes. This data is essential for
understanding braking behavior and analyzing the vehicle’s deceleration and stopping performance.

# Interactive Map 🗺️ 📍

This project includes an interactive map component powered by the Leaflet.js library. The map is centered on a specific set of coordinates and allows users to
visualize a marker on the map. The marker's location can be dynamically updated, and the map view will adjust accordingly. This feature is useful for displaying
real-time location data, such as tracking the movement of a vehicle or updating geographic points of interest.

The map is styled with a dark background to ensure a clean and modern look, making it easy to integrate into various web applications.


# Class Diagram 📊


![AutoData](https://github.com/user-attachments/assets/a87ec348-bd95-4f35-953e-173fc003871a)




# How can you run the code ❓
You can run the program through executing the following commands:

    mkdir build

    cd build

    cmake ..

    make

    ./AutoDataViz



# Dataset 🗂️

You can find the dataset used for this project in the below link:


https://github.com/user-attachments/assets/f70d265f-0ea5-4191-a2b0-7a6e76521443






# Result 📹 🎬


https://github.com/user-attachments/assets/6e944ece-0bbe-4973-b1b3-57ef2f38994f




