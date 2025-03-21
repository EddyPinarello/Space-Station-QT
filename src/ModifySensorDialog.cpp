#include "ModifySensorDialog.h"
#include "ui_ModifySensorDialog.h"

ModifySensorDialog::ModifySensorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifySensorDialog)
{
    ui->setupUi(this);
    connect(ui->ModifyButton, &QPushButton::clicked, this ,&QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

ModifySensorDialog::~ModifySensorDialog()
{
    delete ui;
}

QString ModifySensorDialog::getModifiedName() const
{
    return ui->nameLineEdit->text();
}

QString ModifySensorDialog::getModifiedDescription() const
{
    return ui->descriptionLineEdit->text();
}

void ModifySensorDialog::setSensorInfo(const QString &name, const QString &description)
{
    ui->nameLineEdit->setText(name);
    ui->descriptionLineEdit->setText(description);
}
