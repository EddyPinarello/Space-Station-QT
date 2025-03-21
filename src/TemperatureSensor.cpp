#include "TemperatureSensor.h"

namespace Sensor {

TemperatureSensor::TemperatureSensor(const int& identifier, const std::string& name, const std::string& description,
                                     const double& min_value, const double& max_value, const std::vector<double>& new_data)
    : AbstractSensor(identifier, name, description, new_data),
    min_value(min_value), max_value(max_value){
}

TemperatureSensor::TemperatureSensor(const std::string& id, const std::string& name, const std::string& description)
    : AbstractSensor(std::stoul(id), name, description), min_value(0.0), max_value(100.0) {
}

std::vector<double> TemperatureSensor::getData() const {
    return data;
}

void TemperatureSensor::setData(const std::vector<double>& new_data) {
    data = new_data;
}

double TemperatureSensor::getMinValue() const {
    return -20.0;
}
/*
void TemperatureSensor::setMinValue(const double& value) {
    min_value = value;
}
*/

double TemperatureSensor::getMaxValue() const {
    return 50.0;
}
/*
void TemperatureSensor::setMaxValue(const double& value) {
    max_value = value;
}*/

void TemperatureSensor::accept(SensorVisitor& visitor) const {
    visitor.visit(*this); // Implementazione del metodo accept
}
}
