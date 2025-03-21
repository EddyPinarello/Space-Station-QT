#include "GeigerSensor.h"
#include "SensorVisitor.h"

namespace Sensor {

GeigerSensor::GeigerSensor(const int& identifier, const std::string& name, const std::string& description,
                           const double& min_value, const double& max_value, const std::vector<double>& new_data)
    : AbstractSensor(identifier, name, description, new_data),
    min_value(min_value), max_value(max_value) {
}

GeigerSensor::GeigerSensor(const std::string& id, const std::string& name, const std::string& description)
    : AbstractSensor(std::stoul(id), name, description), min_value(0.0), max_value(100.0){
}

std::vector<double> GeigerSensor::getData() const {
    return data;
}

void GeigerSensor::setData(const std::vector<double>& new_data) {
    data = new_data;
}

double GeigerSensor::getMinValue() const {
    return 0.0;
}
/*
void GeigerSensor::setMinValue(const double& value) {
    min_value = value;
}*/

double GeigerSensor::getMaxValue() const {
    return 100.0;
}
/*
void GeigerSensor::setMaxValue(const double& value) {
    max_value = value;
}
*/
void GeigerSensor::accept(SensorVisitor& visitor) const {
    visitor.visit(*this); // Implementazione del metodo accept
}
}
