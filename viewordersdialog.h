#ifndef VIEWORDERSDIALOG_H
#define VIEWORDERSDIALOG_H

#include <QDialog>
#include <queue>
#include <QString>
#include <QStringList>
#include <stack>
#include "ui_viewordersdialog.h"

namespace Ui {
    class ViewOrdersDialog;
}

class ViewOrdersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewOrdersDialog(QWidget *parent = nullptr);
    ~ViewOrdersDialog();

    void addOrder(const QStringList &order);

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButtonDequeuePush_clicked();
    void on_pushButtonPop_clicked();

private:
    Ui::ViewOrdersDialog *ui;
    std::queue<QStringList> ordersQueue;
    std::stack<QStringList> servedOrdersStack;
    int orderNumber = 1;
};

#endif // VIEWORDERSDIALOG_H
