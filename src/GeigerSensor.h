#ifndef GEIGERSENSOR_H
#define GEIGERSENSOR_H

#include "AbstractSensor.h"
#include "SensorVisitor.h"
#include <vector>
#include <string>

namespace Sensor {

class GeigerSensor : public AbstractSensor {
private:
    double min_value;
    double max_value;

public:
    GeigerSensor(const int& identifier, const std::string& name, const std::string& description,
                 const double& min_value, const double& max_value, const std::vector<double>& new_data);

    GeigerSensor(const std::string& id, const std::string& name, const std::string& description);

    std::vector<double> getData() const override;
    void setData(const std::vector<double>& new_data) override;

    double getMinValue() const;
    //void setMinValue(const double& value);

    double getMaxValue() const;
    //void setMaxValue(const double& value);

    void accept(SensorVisitor& visitor) const override;
};

} // namespace Sensor

#endif // GEIGERSENSOR_H
