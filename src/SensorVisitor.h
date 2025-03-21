#ifndef SENSORVISITOR_H
#define SENSORVISITOR_H

namespace Sensor {

class GeigerSensor;
class TemperatureSensor;
class PressureSensor;

class SensorVisitor {
public:
    virtual ~SensorVisitor() = default;

    virtual void visit(const GeigerSensor& sensor) = 0;
    virtual void visit(const TemperatureSensor& sensor)  = 0;
    virtual void visit(const PressureSensor& sensor)  = 0;
};

} // namespace Sensor

#endif // SENSORVISITOR_H
