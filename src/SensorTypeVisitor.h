#ifndef SENSORTYPEVISITOR_H
#define SENSORTYPEVISITOR_H

#include "SensorVisitor.h"
#include "GeigerSensor.h"
#include "TemperatureSensor.h"
#include "PressureSensor.h"
#include <QString>

class SensorTypeVisitor : public Sensor::SensorVisitor {
public:
    QString sensorType; // Cambiato da puntatore a oggetto QString

    SensorTypeVisitor() {}

    void visit(const Sensor::GeigerSensor&) override {
        sensorType = "Geiger";
    }

    void visit(const Sensor::TemperatureSensor&) override {
        sensorType = "Temperature";
    }

    void visit(const Sensor::PressureSensor&) override {
        sensorType = "Pressure";
    }
};

#endif // SENSORTYPEVISITOR_H
