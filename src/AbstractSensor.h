#ifndef ABSTRACT_SENSOR_H
#define ABSTRACT_SENSOR_H

#include <string>
#include "SensorVisitor.h"
#include <vector>
namespace Sensor {

class AbstractSensor {
private:
    const int identifier;
    std::string name;
    std::string description;

protected:
    AbstractSensor(const int& identifier, const std::string& name, const std::string& description,
                   const std::vector<double>& data);

    // Costruttore senza data
    AbstractSensor(const int& identifier, const std::string& name, const std::string& description);

    // Costruttore di copia
    AbstractSensor(const AbstractSensor& other);

    std::vector<double> data;


public:
    const int& getIdentifier() const;
    std::string getName() const;
    void setName(const std::string& name);
    std::string getDescription() const;
    void setDescription(const std::string& description);

    virtual std::vector<double> getData() const;
    virtual void setData(const std::vector<double>& new_data);

    virtual void accept(SensorVisitor& visitor) const = 0; // Metodo virtuale puro

    virtual ~AbstractSensor() = default;
};

} // namespace Sensor

#endif // ABSTRACT_SENSOR_H
