#ifndef PLACEORDERDIALOG_H
#define PLACEORDERDIALOG_H

#include <QDialog>
#include "ui_placeorderdialog.h"

namespace Ui {
    class PlaceOrderDialog;
}

class PlaceOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceOrderDialog(QWidget *parent = nullptr);
    ~PlaceOrderDialog();

private slots:
    void on_lineEditItemId_textChanged(const QString &arg1);

    void on_pushButtonConfirm_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::PlaceOrderDialog *ui;
    QStringList menuItems; // Add this line
};

#endif // PLACEORDERDIALOG_H
