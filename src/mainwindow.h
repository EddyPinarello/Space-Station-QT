#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
#include "AbstractSensor.h"
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private :
    void onAddSensorClicked();
    void onDeleteSensorClicked();
    void onSensorListItemClicked(QListWidgetItem *item);
    void updateSensorList();
    void onModifySensorClicked();

    void onSearchButtonClicked();
    void onSimulateSensorClicked();
    void onSearchTextChanged(const QString &text);
    QString formatRandomData(const std::vector<double>& data);
    void clearChartsContainer();
    void searchSensorByName(const QString &name);
    void saveSensorListToFile();
    void openSensorListFromFile();
    Ui::MainWindow *ui;
    std::vector<Sensor::AbstractSensor*> sensors;

    // Aggiungi membri per il chart
    QChartView *chartView;
    QBarSeries *series;
    QBarSet *barSet;
    QChart *chart;
};

#endif // MAINWINDOW_H
