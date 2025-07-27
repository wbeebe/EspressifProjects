#pragma once

#include <stdint.h>

// Sensor types
//
typedef enum {
  SENSOR_TYPE_ACCELEROMETER = (1), // Gravity + linear acceleration
  SENSOR_TYPE_MAGNETIC_FIELD = (2),
  SENSOR_TYPE_ORIENTATION = (3),
  SENSOR_TYPE_GYROSCOPE = (4),
  SENSOR_TYPE_LIGHT = (5),
  SENSOR_TYPE_PRESSURE = (6),
  SENSOR_TYPE_PROXIMITY = (8),
  SENSOR_TYPE_GRAVITY = (9),
  SENSOR_TYPE_LINEAR_ACCELERATION = (10), // Acceleration not including gravity
  SENSOR_TYPE_ROTATION_VECTOR = (11),
  SENSOR_TYPE_RELATIVE_HUMIDITY = (12),
  SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
  SENSOR_TYPE_OBJECT_TEMPERATURE = (14),
  SENSOR_TYPE_VOLTAGE = (15),
  SENSOR_TYPE_CURRENT = (16),
  SENSOR_TYPE_COLOR = (17)
} sensors_type_t;


// struct sensors_vec_s is used to return a vector in a common format.
//
typedef struct {
  union {
    float v[3]; // 3D vector elements
    struct {
      float x;  // X component of vector
      float y;  // Y component of vector
      float z;  // Z component of vector
    };          // Struct for holding XYZ component

    // Orientation sensors
    struct {
      float roll;   // Rotation around the longitudinal axis (the plane body, 'X
                    // axis'). Roll is positive and increasing when moving
                    // downward. -90 degrees <= roll <= 90 degrees */

      float pitch;  // Rotation around the lateral axis (the wing span, 'Y
                    // axis'). Pitch is positive and increasing when moving
                    // upwards. -180 degrees <= pitch <= 180 degrees) */

      float heading; // Angle between the longitudinal axis (the plane body)
                     // and magnetic north, measured clockwise when viewing from
                     // the top of the device. 0-359 degrees */
    };               // Struct for holding roll/pitch/heading
  };                 // Union that can hold 3D vector array, XYZ components or
                     // roll/pitch/heading
  int8_t status;     // Status byte
  uint8_t reserved[3]; // Reserved
} sensors_vec_t;

typedef struct {
  union {
    float data[4];              // Raw data
    sensors_vec_t acceleration; // acceleration values are in m/s/s or (m/s^2)
    sensors_vec_t magnetic;     // magnetic vector values are in micro-Tesla (uT)
    sensors_vec_t orientation;  // orientation values are in degrees
    sensors_vec_t gyro;         // gyroscope values are in rad/s
  };
} sensors_event_t;