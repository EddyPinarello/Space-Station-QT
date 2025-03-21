// RandomDataVisitor.h (header file)

#ifndef RANDOMDATAVISITOR_H
#define RANDOMDATAVISITOR_H

#include "SensorVisitor.h"
#include "GeigerSensor.h"
#include "PressureSensor.h"
#include "TemperatureSensor.h"

class RandomDataVisitor : public Sensor::SensorVisitor {
public:
    void visit(Sensor::GeigerSensor& sensor)   {
        sensor.setRandomData();
        sensor.getData();
    }

    void visit(Sensor::TemperatureSensor& sensor)  {
        sensor.setRandomData();
         sensor.getData();
    }

    void visit(Sensor::PressureSensor& sensor)  {
        sensor.setRandomData();
         sensor.getData();
    }
};

#endif // RANDOMDATAVISITOR_H
