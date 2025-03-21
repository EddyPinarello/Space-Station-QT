#include "AbstractSensor.h"

namespace Sensor {

AbstractSensor::AbstractSensor(const int& identifier, const std::string& name, const std::string& description,
                               const std::vector<double>& data)
    : identifier(identifier), name(name), description(description), data(data){
}

// Costruttore senza data
AbstractSensor::AbstractSensor(const int& identifier, const std::string& name, const std::string& description)
    : identifier(identifier), name(name), description(description){
}

// Costruttore di copia
AbstractSensor::AbstractSensor(const AbstractSensor& other)
    : identifier(other.identifier), name(other.name), description(other.description), data(other.data){
}

std::vector<double> AbstractSensor::getData() const {
    return data;
}

void AbstractSensor::setData(const std::vector<double>& new_data) {
    data = new_data;
}
const int& AbstractSensor::getIdentifier() const {
    return identifier;
}

std::string AbstractSensor::getName() const {
    return name;
}

void AbstractSensor::setName(const std::string& name) {
    this->name = name;
}

std::string AbstractSensor::getDescription() const {
    return description;
}

void AbstractSensor::setDescription(const std::string& description) {  // Adding setDescription for completeness
    this->description = description;
}

}
