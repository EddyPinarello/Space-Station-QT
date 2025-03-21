#include "AddSensorDialog.h"
#include "ui_AddSensorDialog.h"

AddSensorDialog::AddSensorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSensorDialog)
{
    ui->setupUi(this);
    connect(ui->addButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

AddSensorDialog::~AddSensorDialog()
{
    delete ui;
}

QString AddSensorDialog::getSensorType() const
{
    return ui->typeComboBox->currentText();
}

QString AddSensorDialog::getSensorId() const
{
    return ui->idLineEdit->text();
}

QString AddSensorDialog::getSensorName() const
{
    return ui->nameLineEdit->text();
}

QString AddSensorDialog::getSensorDescription() const
{
    return ui->descriptionLineEdit->text();
}
