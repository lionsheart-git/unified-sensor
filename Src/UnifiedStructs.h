
#ifndef UNIFIED_SENSOR_UNIFIED_STRUCTS_HPP
#define UNIFIED_SENSOR_UNIFIED_STRUCTS_HPP

#include <stdint.h>

/** Module types */
typedef enum
{
    DATA_TYPE_UNDEFINED = 0,
    DATA_TYPE_ACCELEROMETER = 1 << 1, /**< Gravity + linear acceleration */
    DATA_TYPE_MAGNETIC_FIELD = 1 << 2,
    DATA_TYPE_ORIENTATION = 1 << 3,
    DATA_TYPE_GYROSCOPE = 1 << 4,
    DATA_TYPE_LIGHT = 1 << 5,
    DATA_TYPE_PRESSURE = 1 << 6,
    DATA_TYPE_PROXIMITY = 1 << 7,
    DATA_TYPE_GRAVITY = 1 << 8,
    DATA_TYPE_LINEAR_ACCELERATION = 1 << 9, /**< Acceleration not including gravity */
    DATA_TYPE_ROTATION_VECTOR = 1 << 10,
    DATA_TYPE_RELATIVE_HUMIDITY = 1 << 11,
    DATA_TYPE_AMBIENT_TEMPERATURE = 1 << 12,
    DATA_TYPE_OBJECT_TEMPERATURE = 1 << 13,
    DATA_TYPE_VOLTAGE = 1 << 14,
    DATA_TYPE_CURRENT = 1 << 15,
    DATA_TYPE_COLOR = 1 << 16,
    DATA_TYPE_POSITION = 1 << 17,
    DATA_TYPE_ALTITUDE = 1 << 18
} data_type_t;

/** struct is used to return a vector in a common format. */
typedef struct
{
    union
    {
        float v[3]; ///< 3D vector elements
        struct
        {
            float x; ///< X component of vector
            float y; ///< Y component of vector
            float z; ///< Z component of vector
        };         ///< Struct for holding XYZ component
        /* Orientation sensors */
        struct
        {
            float roll; /**< Rotation around the longitudinal axis (the plane body, 'X
                     axis'). Roll is positive and increasing when moving
                     downward. -90 degrees <= roll <= 90 degrees */
            float pitch;   /**< Rotation around the lateral axis (the wing span, 'Y
                        axis'). Pitch is positive and increasing when moving
                        upwards. -180 degrees <= pitch <= 180 degrees) */
            float heading; /**< Angle between the longitudinal axis (the plane body)
                        and magnetic north, measured clockwise when viewing from
                        the top of the device. 0-359 degrees */
        };               ///< Struct for holding roll/pitch/heading
    };                 ///< Union that can hold 3D vector array, XYZ components or
    ///< roll/pitch/heading
} data_3d_vec_t;

/**
 * @struct data_2dvec_t
 * @brief Two dimensional vector for contain 2 data values.
 */
typedef struct {
    float v[2];
    union {
        struct {
            float longitude;
            float latitude;
        };
    };
} data_2dvec_t;

/**
 * @struct data_color_t
 * @brief Used to return color data in a common format.
 */
typedef struct
{
    union
    {
        float c[3]; ///< Raw 3-element data
        /* RGB color space */
        struct
        {
            float r;   /**< Red component */
            float g;   /**< Green component */
            float b;   /**< Blue component */
        };           ///< RGB data in floating point notation
    };             ///< Union of various ways to describe RGB colorspace
    uint32_t rgba; /**< 24-bit RGBA value */
} data_color_t;

/**
 * @typedef data_event_t
 * @brief Provides a single data event in a common format. */
typedef struct
{
    int32_t version;   /**< must be sizeof(struct data_event_t) */
    int32_t sensor_id; /**< unique sensor identifier */
    int32_t type;      /**< data type */
    int32_t system_time; /**< system time in milliseconds */
    uint32_t clock; /**< seconds since 2000-01-01 */
    bool valid;
    union
    {
        float data[4];              /**< Raw data */
        data_3d_vec_t acceleration; /**< acceleration values are in meter per second per second (m/s^2) */
        data_3d_vec_t magnetic; /**< magnetic vector values are in micro-Tesla (uT) */
        data_3d_vec_t orientation; /**< orientation values are in degrees */
        data_3d_vec_t gyro;        /**< gyroscope values are in rad/s */
        data_2dvec_t coordinates; /**< Coordinates (latitude and longitude) of current position */
        uint8_t satellites; /**< Current number of satellites used by GNSS */
        float hdop; /**< HDOP of GNSS signal */
        float speed; /**< Current speed, for example measured by GNSS (mps) */
        float altitude; /**< Altitude in meters (m) */
        float temperature; /**< temperature is in degrees centigrade (Celsius) */
        float distance;    /**< distance in centimeters (cm) */
        float light;       /**< light in SI lux units (lux) */
        float pressure;    /**< pressure in hectopascal (hPa) */
        float relative_humidity; /**< relative humidity in percent (%) */
        float current;           /**< current in milliamps (mA) */
        float voltage;           /**< voltage in volts (V) */
        data_color_t color;   /**< color in RGB component values */
    };                         ///< Union for the wide ranges of data we can carry
} data_event_t;

/**
 * @struct module_t
 * @brief Struct module_t is used to describe basic information about a specific sensor.
 */
typedef struct
{
    char name[12];      /**< sensor name */
    int32_t version;    /**< version of the hardware + driver */
    int32_t sensor_id;  /**< unique sensor identifier */
    int32_t data_types;  /**< The possible data types this sensor can provide. */
} module_t;

/**
 * @struct sensor_t
 * @brief Sensor a sensor provides.
 */
typedef struct {
    int32_t version;    /**< must be sizeof(struct sensor_t) */
    int32_t sensor_id;  /**< unique sensor identifier */
    int32_t type;       /**< data type */
    float max_value;    /**< maximum value of this sensor's value in SI units */
    float min_value;    /**< minimum value of this sensor's value in SI units */
    float resolution;   /**< smallest difference between two values reported by this sensor */
    int32_t min_delay;  /**< min delay in microseconds between events. zero = not a constant rate */
} sensor_t;

typedef struct {
    int32_t version;    /**< must be sizeof(struct init_data_t) */
    int32_t sensor_id;  /**< unique sensor identifier */
    union {
        int32_t counter;
    };
    union {
        float ground_level_pressure;
    };
} init_data_t;

#endif //UNIFIED_SENSOR_UNIFIED_STRUCTS_HPP
