#include "placeorderdialog.h"
#include "ui_placeorderdialog.h"
#include "mainwindow.h"
#include "viewordersdialog.h"

PlaceOrderDialog::PlaceOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlaceOrderDialog)
{
    ui->setupUi(this);

    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    if (mainWindow) {
        menuItems = mainWindow->getMenuItems();
    }
    ui->lineEditItemId->setFocus();
}

PlaceOrderDialog::~PlaceOrderDialog()
{
    delete ui;
}

void PlaceOrderDialog::on_lineEditItemId_textChanged(const QString &arg1)
{
    bool ok;
    int itemID = arg1.toInt(&ok);
    if (ok && itemID > 0 && itemID <= menuItems.size()) {
        QStringList details = menuItems.at(itemID-1).split(",");
        QString itemName = details[0];
        QString itemPrice = details[2];
        ui->labelYourOrder->setText("Your order is " + itemName + " for ₱" + itemPrice);
    } else {
        ui->labelYourOrder->setText("Invalid item ID");
    }
}

void PlaceOrderDialog::on_pushButtonConfirm_clicked()
{
    QString orderText = ui->labelYourOrder->text();
    QStringList orderDetails = orderText.split(" for ₱");
    if (orderDetails.size() == 2) {
        QStringList order = { orderDetails[0].mid(13), orderDetails[1] };
        MainWindow *mainWindow = qobject_cast<MainWindow*>(this->parent());
        if (mainWindow) {
            ViewOrdersDialog *viewOrdersDialog = mainWindow->getViewOrdersDialog();
            if (viewOrdersDialog) {
                viewOrdersDialog->addOrder(order);
            }
        }
    }
    ui->lineEditItemId->clear();
    ui->labelYourOrder->setText("Your order is ...");
    this->close();
    ui->lineEditItemId->setFocus();
}

void PlaceOrderDialog::on_pushButtonCancel_clicked()
{
    ui->lineEditItemId->clear();
    this->close();
}

