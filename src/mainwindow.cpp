#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GeigerSensor.h"
#include "TemperatureSensor.h"
#include "PressureSensor.h"
#include "ModifySensorDialog.h"
#include "AddSensorDialog.h"
#include "SensorTypeVisitor.h"
#include "SensorRandomDataVisitor.h"
#include "QMessageBox"
#include <QtCharts>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QListWidgetItem>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QChartView>
#include <QLineSeries>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chartView(new QChartView(this)),
    series(new QBarSeries()),
    barSet(new QBarSet("Random Data")),
    chart(new QChart())
{
    ui->setupUi(this);
    ui->ChartsContainer->setLayout(new QVBoxLayout());
    connect(ui->AddSensor, &QPushButton::clicked, this, &MainWindow::onAddSensorClicked);
    connect(ui->ListSensor, &QListWidget::itemClicked, this, &MainWindow::onSensorListItemClicked);
    connect(ui->DeleteSensor, &QPushButton::clicked, this, &MainWindow::onDeleteSensorClicked);
    connect(ui->searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(ui->ModifySensor, &QPushButton::clicked, this, &MainWindow::onModifySensorClicked);
    connect(ui->SimulateSensor, &QPushButton::clicked, this, &MainWindow::onSimulateSensorClicked);
    connect(ui->SaveSensorsButton, &QPushButton::clicked, this, &MainWindow::saveSensorListToFile);
    connect(ui->OpenSensorsButton, &QPushButton::clicked, this, &MainWindow::openSensorListFromFile);

}

MainWindow::~MainWindow()
{
    for(Sensor::AbstractSensor* sensor : sensors){ delete sensor; }
    sensors.clear();
    delete ui;
}

void MainWindow::onAddSensorClicked() {
    AddSensorDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString type = dialog.getSensorType();
        QString id = dialog.getSensorId();
        QString name = dialog.getSensorName();
        QString description = dialog.getSensorDescription(); // Get the description from the dialog

        // Controllo validità dell'ID e del nome
        if (id.length() < 5) {
            QMessageBox::critical(this, "Errore", "L'ID deve essere di almeno 5 caratteri.");
            return;
        }

        if (name.isEmpty()) {
            QMessageBox::critical(this, "Errore", "Il nome non può essere vuoto.");
            return;
        }

        const int identifier = id.toUInt();

        // Controllo se esiste già un sensore con lo stesso ID
        for (const auto& addedSensor : sensors) {
            if (identifier == addedSensor->getIdentifier()) {
                QMessageBox::critical(this, "Errore", "Esiste già un sensore con lo stesso ID.");
                return;
            }
        }

        // Creazione del sensore
        Sensor::AbstractSensor* sensor = nullptr;
        if (type == "Geiger") {
            sensor = new Sensor::GeigerSensor(identifier, name.toStdString(), description.toStdString(), 0.0, 100.0, std::vector<double>());
        } else if (type == "Temperature") {
            sensor = new Sensor::TemperatureSensor(identifier, name.toStdString(), description.toStdString(), -20.0, 50.0, std::vector<double>());
        } else if (type == "Pressure") {
            sensor = new Sensor::PressureSensor(identifier, name.toStdString(), description.toStdString(), 950.0, 1050.0, std::vector<double>());
        }

        if (sensor) {
            sensors.push_back(sensor);
        }

        updateSensorList();
    }
}


void MainWindow::updateSensorList()
{
    ui->ListSensor->clear();
    for (const auto& sensor : sensors) {
        QString idStr = QString::fromStdString(std::to_string(sensor->getIdentifier()));
        QString sensorInfo = QString("ID: %1, Name: %2")
                                .arg(idStr)
                                .arg(QString::fromStdString(sensor->getName()));
        ui->ListSensor->addItem(sensorInfo);
    }
}

void MainWindow::onSensorListItemClicked(QListWidgetItem *item)
{
    if (!item) {
        return; // Nessun elemento selezionato, esce dalla funzione
    }

    QString itemText = item->text();
    static QRegularExpression re("ID: (\\d+), Name: (.+)");
    QRegularExpressionMatch match = re.match(itemText);
    if (match.hasMatch()) {
        QString idStr = match.captured(1);
        QString name = match.captured(2);

        // Cerca il sensore corrispondente nella lista di sensori
        for (auto it = sensors.begin(); it != sensors.end(); ++it) {
            if ((*it)->getIdentifier() == idStr.toInt()) {
                Sensor::AbstractSensor *selectedSensor = *it;

                // Recupera la descrizione del sensore
                QString description = QString::fromStdString(selectedSensor->getDescription());

                // PARTE VISITOR PER CAPIRE IL TIPO DEL SENSOR CHE STO SCORRENDO
                SensorTypeVisitor typeVisitor;
                selectedSensor->accept(typeVisitor);



                // Aggiorna i QLabel nel MainWindow con le informazioni del sensore
                ui->IDLabel->setText(idStr);
                ui->TypeLabel->setText(typeVisitor.sensorType); // Usa il tipo del sensore determinato dal visitor
                ui->NameLabel->setText(name);
                ui->DescriptionLabel->setText(description);


                break; // Esci dal ciclo una volta trovato il sensore corrispondente

            }
        }
        clearChartsContainer();
    }
}



void MainWindow::onDeleteSensorClicked()
{
    clearChartsContainer();
    QListWidgetItem *selectedItem = ui->ListSensor->currentItem();
    if (!selectedItem) {
        return; // Nessun elemento selezionato, esce dalla funzione
    }

    QString itemText = selectedItem->text();
    static QRegularExpression re("ID: (\\d+), Name: (.+)");
    QRegularExpressionMatch match = re.match(itemText);
    if (match.hasMatch()) {
        QString idStr = match.captured(1);
        const int id = idStr.toUInt();

        // Cerca e rimuove il sensore con l'ID corrispondente
        for (auto it = sensors.begin(); it != sensors.end(); ++it) {
            if ((*it)->getIdentifier() == id) {
                ui->IDLabel->clear(); // Pulisce l'IDLabel dopo la rimozione
                ui->NameLabel->clear(); // Pulisce il NameLabel dopo la rimozione
                ui->DescriptionLabel->clear(); // Pulisce il DescriptionLabel dopo la rimozione
                ui->TypeLabel->clear(); // Pulisce il TypeLabel dopo la rimozione
                delete selectedItem; // Rimuove l'elemento selezionato dalla lista
                sensors.erase(it); // Rimuove l'elemento dal vettore
                delete *it; // Rimuove l'oggetto dalla memoria
                updateSensorList(); // Aggiorna la visualizzazione della lista
                return;
            }
        }
    }
}


void MainWindow::onSearchTextChanged(const QString &text)
{
    searchSensorByName(text);
}

void MainWindow::searchSensorByName(const QString &name)
{
    ui->ListSensor->clear();
    for (const auto& sensor : sensors) {
        QString sensorName = QString::fromStdString(sensor->getName());
        if (sensorName.contains(name, Qt::CaseInsensitive)) {
            QString sensorInfo = QString("ID: %1, Name: %2")
                                     .arg(sensor->getIdentifier())
                                     .arg(sensorName);
            ui->ListSensor->addItem(sensorInfo);
        }
    }
}


void MainWindow::onModifySensorClicked()
{
    QListWidgetItem *selectedItem = ui->ListSensor->currentItem();
    if (!selectedItem) {
        return; // Nessun elemento selezionato, esce dalla funzione
    }

    QString itemText = selectedItem->text();
    static QRegularExpression re("ID: (\\d+), Name: (.+)");
    QRegularExpressionMatch match = re.match(itemText);
    if (match.hasMatch()) {
        QString idStr = match.captured(1);
        QString name = match.captured(2);

        int id = idStr.toInt();
        Sensor::AbstractSensor *selectedSensor = nullptr;

        // Trova il sensore nel vettore `sensors` per l'ID corrispondente
        for (auto it = sensors.begin(); it != sensors.end(); ++it) {
            if ((*it)->getIdentifier() == id) {
                selectedSensor = *it;
                break;
            }
        }

        if (selectedSensor) {
            QString description = QString::fromStdString(selectedSensor->getDescription());

            ModifySensorDialog dialog(this);
            dialog.setSensorInfo(name, description); // Imposta sia il nome che la descrizione

            if (dialog.exec() == QDialog::Accepted) {
                QString modifiedName = dialog.getModifiedName();
                QString modifiedDescription = dialog.getModifiedDescription();
                if (modifiedName.isEmpty()) {
                    QMessageBox::critical(this, "Errore", "Il nome non può essere vuoto.");
                    return;
                }

                // Applica le modifiche al sensore trovato
                selectedSensor->setName(modifiedName.toStdString());
                selectedSensor->setDescription(modifiedDescription.toStdString());

                // Aggiorna la lista dei sensori e l'interfaccia grafica
                ui->NameLabel->setText(modifiedName);
                ui->DescriptionLabel->setText(modifiedDescription);
                updateSensorList();
            }
        }
    }
}


void MainWindow::onSimulateSensorClicked(){
    QListWidgetItem *selectedItem = ui->ListSensor->currentItem();
    if (!selectedItem) {
        return; // Nessun elemento selezionato, esce dalla funzione
    }

    QString itemText = selectedItem->text();
    static QRegularExpression re("ID: (\\d+)");
    QRegularExpressionMatch match = re.match(itemText);
    if (match.hasMatch()) {
        QString idStr = match.captured(1);
        int id = idStr.toInt();
        Sensor::AbstractSensor *selectedSensor = nullptr;

        // Trova il sensore nel vettore `sensors` per l'ID corrispondente
        for (auto it = sensors.begin(); it != sensors.end(); ++it) {
            if ((*it)->getIdentifier() == id) {
                selectedSensor = *it;
                break;
            }
        }
        if (selectedSensor) {
            SensorRandomDataVisitor randomDataVisitor;
            selectedSensor->accept(randomDataVisitor);
            // Aggiorna QLabel per i dati casuali del sensore
            QString randomDataText;
            for (size_t i = 0; i < randomDataVisitor.randomData.size(); ++i) {
                randomDataText += QString("Data %1: %2\n").arg(i + 1).arg(randomDataVisitor.randomData[i]);
            }
            // Crea il grafico con i dati simulati
            QLineSeries *series = new QLineSeries();
            for (size_t i = 0; i < randomDataVisitor.randomData.size(); ++i) {
                series->append(static_cast<qreal>(i), randomDataVisitor.randomData[i]);
            }

            QChart *chart = new QChart();
            chart->legend()->hide();
            chart->addSeries(series);
            chart->createDefaultAxes();
            chart->setTitle("Simulated Sensor Data");

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            // Rimuove il vecchio grafico se esiste
            QLayoutItem *child;
            while ((child = ui->ChartsContainer->layout()->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }

            // Aggiunge il nuovo grafico al layout
            ui->ChartsContainer->layout()->addWidget(chartView);
        }
    }
}
void MainWindow::clearChartsContainer() {
    QLayout *layout = ui->ChartsContainer->layout();
    if (layout != nullptr) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
    }
}

void MainWindow::saveSensorListToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Sensor List", "", "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream out(&file);

    // Itera attraverso il vettore di sensori e scrivi le informazioni nel file
    for (const auto &sensor : sensors) {
        QString idStr = QString::number(sensor->getIdentifier());
        QString name = QString::fromStdString(sensor->getName());
        QString description = QString::fromStdString(sensor->getDescription());

        SensorTypeVisitor typeVisitor;
        sensor->accept(typeVisitor);
        QString sensorType = typeVisitor.sensorType;

        out << "ID: " << idStr << ", Name: " << name << ", Type: " << sensorType << ", Description: " << description << "\n";
    }

    file.close();
    QMessageBox::information(this, "Success", "Sensor list saved successfully.");
}


void MainWindow::openSensorListFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Sensor List", "", "Text Files (*.txt);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    sensors.clear(); // Pulisce la lista di sensori corrente

    QRegularExpression re("ID: (\\d+), Name: ([^,]+), Type: ([^,]+), Description: (.*)$");

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatch match = re.match(line);
        if (match.hasMatch()) {
            int id = match.captured(1).toInt();
            QString name = match.captured(2);
            QString type = match.captured(3);
            QString description = match.captured(4);

            // Creazione del sensore basato sul tipo
            Sensor::AbstractSensor* sensor = nullptr;
            if (type == "Geiger") {
                sensor = new Sensor::GeigerSensor(id, name.toStdString(), description.toStdString(), 0.0, 100.0, std::vector<double>());
            } else if (type == "Temperature") {
                sensor = new Sensor::TemperatureSensor(id, name.toStdString(), description.toStdString(), -20.0, 50.0, std::vector<double>());
            } else if (type == "Pressure") {
                sensor = new Sensor::PressureSensor(id, name.toStdString(), description.toStdString(), 950.0, 1050.0, std::vector<double>());
            }

            if (sensor) {
                sensors.push_back(sensor);
            }
        }
    }

    file.close();
    updateSensorList(); // Aggiorna la lista dei sensori nella UI
    QMessageBox::information(this, "Success", "Sensor list loaded successfully.");
}
