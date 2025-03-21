QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += charts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddSensorDialog.cpp \
    GeigerSensor.cpp \
    ModifySensorDialog.cpp \
    PressureSensor.cpp \
    TemperatureSensor.cpp \
    abstractsensor.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AbstractSensor.h \
    AddSensorDialog.h \
    GeigerSensor.h \
    ModifySensorDialog.h \
    PressureSensor.h \
    SensorRandomDataVisitor.h \
    SensorTypeVisitor.h \
    SensorVisitor.h \
    TemperatureSensor.h \
    mainwindow.h

FORMS += \
    AddSensorDialog.ui \
    ModifySensorDialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
