
#ifndef UNIFIED_LOGGER_UNIFIEDSENSOR_HPP
#define UNIFIED_LOGGER_UNIFIEDSENSOR_HPP

#include "Unified_Structs.hpp"

class UnifiedSensor
{
    // Constructor(s)
    UnifiedSensor() = default;
    virtual ~UnifiedSensor() = default;

    /**
     * @brief Get the latest sensor event.
     * @returns True if able to fetch an event.
     */
    virtual bool Event(data_event_t *) = 0;

    /**
     * @brief Information about this sensor.
     * @return True, if able to fetch info.
     */
    virtual bool Sensor(sensor_t *) = 0;

    /**
     * @brief Initializes the sensors and performs necessary calibrations.
     * @return Struct containing initialization data.
     * @retval True, calibration sequence was successful.
     */
    virtual bool Init(init_data_t *) = 0;
};



#endif //UNIFIED_LOGGER_UNIFIEDSENSOR_HPP
