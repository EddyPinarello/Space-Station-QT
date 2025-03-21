#ifndef MODIFYSENSORDIALOG_H
#define MODIFYSENSORDIALOG_H

#include <QDialog>

namespace Ui {
class ModifySensorDialog;
}

class ModifySensorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifySensorDialog(QWidget *parent = nullptr);
    ~ModifySensorDialog();

    QString getModifiedName() const;
    QString getModifiedDescription() const;

    void setSensorInfo(const QString &name, const QString &description);

private:
    Ui::ModifySensorDialog *ui;
};

#endif // MODIFYSENSORDIALOG_H
