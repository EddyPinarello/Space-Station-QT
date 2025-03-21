#ifndef ADDSENSORDIALOG_H

#define ADDSENSORDIALOG_H

#include <QDialog>

namespace Ui {
    class AddSensorDialog;
}
class AddSensorDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddSensorDialog(QWidget *parent = nullptr);
    ~AddSensorDialog();

    QString getSensorType() const;
    QString getSensorId() const;
    QString getSensorName () const;
    QString getSensorDescription() const;

private:
    Ui :: AddSensorDialog *ui;
};
#endif // ADDSENSORDIALOG_H
