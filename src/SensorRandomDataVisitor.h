#include "SensorVisitor.h"
#include "GeigerSensor.h"
#include "TemperatureSensor.h"
#include "PressureSensor.h"
#include <random>
#include <QDateTime>

class SensorRandomDataVisitor : public Sensor::SensorVisitor {
public:
    std::vector<double> randomData; // Per contenere i dati casuali

    SensorRandomDataVisitor() : randomData(6) {
        // Inizializzazione del generatore di numeri casuali
        std::random_device rd;
        generator.seed(rd());
    }

    void visit(const Sensor::GeigerSensor& sensor) override {
        generateRandomData(sensor.getMinValue(), sensor.getMaxValue()); // 0 to 100 for GeigerSensor
    }

    void visit(const Sensor::TemperatureSensor& sensor) override {
        generateRandomData(sensor.getMinValue(), sensor.getMaxValue()); // -20 to 50 for TemperatureSensor
    }

    void visit(const Sensor::PressureSensor& sensor) override {
        generateRandomData(sensor.getMinValue(), sensor.getMaxValue()); // 950 to 1050 for PressureSensor
    }

private:
    std::mt19937 generator;

    void generateRandomData(double min, double max) {
        std::uniform_real_distribution<double> distribution(min, max);
        for (auto& data : randomData) {
            data = distribution(generator);
        }
    }
};

