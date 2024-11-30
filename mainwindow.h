#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ViewOrdersDialog;
class PlaceOrderDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStringList getMenuItems() const;
    ViewOrdersDialog* getViewOrdersDialog() const; // Add this method

private slots:
    void on_viewOrdersButton_clicked();
    void on_placeOrderButton_clicked();

private:
    Ui::MainWindow *ui;
    ViewOrdersDialog *viewOrdersDialog;
    PlaceOrderDialog *placeOrderDialog;
    QStringList menuItems;
};

#endif // MAINWINDOW_H
