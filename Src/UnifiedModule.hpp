
#ifndef UNIFIED_SENSOR_UNIFIEDMODULE_HPP
#define UNIFIED_SENSOR_UNIFIEDMODULE_HPP

#include "Unified_Structs.hpp"

class UnifiedSensor;

class UnifiedModule
{

public:
    // Constructor(s)
    UnifiedModule() = default;
    virtual ~UnifiedModule() = default;

    /**
     * @brief Get the data the sensor provides.
     * @return
     */
    virtual UnifiedSensor Sensor(data_type_t) = 0;

    /*! @brief Get info about the sensor itself */
    virtual void Module(module_t *) = 0;
};

#endif //UNIFIED_SENSOR_UNIFIEDMODULE_HPP
