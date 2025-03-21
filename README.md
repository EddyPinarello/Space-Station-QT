Preview Space Station desktop app FULL C++
![image](https://github.com/user-attachments/assets/90922948-578c-41df-9dbf-6ef7fc3041f6)

# Sensor Management Desktop Application

This is a Qt-based desktop application that functions as a CRUD (Create, Read, Update, Delete) system for managing various sensors. The application is built around an abstract sensor class, allowing for the addition of different types of sensors, such as Geiger, Pressure, and Temperature sensors. It also includes functionality for simulating sensor measurements.

## Features

- Manage different types of sensors, including adding, modifying, and deleting sensors.
- Abstract sensor class architecture, allowing for easy extension to new sensor types.
- Simulate sensor measurements to visualize sensor data.
- Implements the **Visitor** design pattern to separate algorithms from sensor objects, enabling operations like random data generation or type-specific actions without modifying the sensor classes.

