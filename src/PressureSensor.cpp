#include "PressureSensor.h"
#include "SensorVisitor.h"

namespace Sensor {

PressureSensor::PressureSensor(const int& identifier, const std::string& name, const std::string& description,
                               const double& min_value, const double& max_value, const std::vector<double>& new_data)
    : AbstractSensor(identifier, name, description, new_data),
    min_value(min_value), max_value(max_value) {
}

PressureSensor::PressureSensor(const std::string& id, const std::string& name, const std::string& description)
    : AbstractSensor(std::stoul(id), name, description), min_value(950.0), max_value(1050.0) {
}

std::vector<double> PressureSensor::getData() const {
    return data;
}

void PressureSensor::setData(const std::vector<double>& new_data) {
    data = new_data;
}

double PressureSensor::getMinValue() const {
    return min_value;
}
/*
void PressureSensor::setMinValue(const double& value) {
    min_value = value;
}*/

double PressureSensor::getMaxValue() const {
    return max_value;
}
/*
void PressureSensor::setMaxValue(const double& value) {
    max_value = value;
}*/

void PressureSensor::accept(SensorVisitor& visitor) const {
    visitor.visit(*this);
}

} // namespace Sensor
