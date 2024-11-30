#include "viewordersdialog.h"
#include "ui_viewordersdialog.h"

ViewOrdersDialog::ViewOrdersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewOrdersDialog)
{
    ui->setupUi(this);
    ui->tableWidgetOrderQueue->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ViewOrdersDialog::~ViewOrdersDialog()
{
    delete ui;
}

void ViewOrdersDialog::addOrder(const QStringList &order)
{
    QStringList orderWithNumber = order;
    orderWithNumber.prepend(QString::number(orderNumber++));
    ordersQueue.push(orderWithNumber);
}

void ViewOrdersDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    ui->tableWidgetOrderQueue->setRowCount(ordersQueue.size());
    ui->tableWidgetOrderQueue->setColumnCount(3);
    ui->tableWidgetOrderQueue->setHorizontalHeaderLabels(QStringList() << "Order Number" << "Item Name" << "Price");

    std::queue<QStringList> tempQueue = ordersQueue;
    int row = 0;

    while (!tempQueue.empty()) {
        QStringList order = tempQueue.front();
        tempQueue.pop();
        QTableWidgetItem *orderNumberItem = new QTableWidgetItem("#" + order[0]);
        QTableWidgetItem *itemName = new QTableWidgetItem(order[1]);
        QTableWidgetItem *itemPrice = new QTableWidgetItem(order[2]);
        orderNumberItem->setTextAlignment(Qt::AlignCenter);
        itemName->setTextAlignment(Qt::AlignCenter);
        itemPrice->setTextAlignment(Qt::AlignCenter);

        QColor backgroundColor(0, 0, 0, 204);
        orderNumberItem->setBackground(backgroundColor);
        itemName->setBackground(backgroundColor);
        itemPrice->setBackground(backgroundColor);

        ui->tableWidgetOrderQueue->setItem(row, 0, orderNumberItem);
        ui->tableWidgetOrderQueue->setItem(row, 1, itemName);
        ui->tableWidgetOrderQueue->setItem(row, 2, itemPrice);
        row++;
    }

    ui->tableWidgetOrderQueue->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    if (!ordersQueue.empty()) {
        QStringList nextOrder = ordersQueue.front();
        ui->labelFront->setText(QString("Next Order: #%1 - %2").arg(nextOrder[0], nextOrder[1]));
    } else {
        ui->labelFront->setText("Next Order: ...");
    }

    if (!servedOrdersStack.empty()) {
        QStringList lastServedOrder = servedOrdersStack.top();
        ui->labelPeek->setText(QString("Last Order served: #%1 - %2").arg(lastServedOrder[0], lastServedOrder[1]));
    } else {
        ui->labelPeek->setText("Last Order served: ...");
    }
}

void ViewOrdersDialog::on_pushButtonDequeuePush_clicked()
{
    if (!ordersQueue.empty()) {
        QStringList order = ordersQueue.front();
        ordersQueue.pop();

        servedOrdersStack.push(order);

        ui->tableWidgetOrderQueue->setRowCount(ordersQueue.size());
        std::queue<QStringList> tempQueue = ordersQueue;
        int row = 0;

        while (!tempQueue.empty()) {
            QStringList order = tempQueue.front();
            tempQueue.pop();
            QTableWidgetItem *orderNumberItem = new QTableWidgetItem("#" + order[0]);
            QTableWidgetItem *itemName = new QTableWidgetItem(order[1]);
            QTableWidgetItem *itemPrice = new QTableWidgetItem(order[2]);
            orderNumberItem->setTextAlignment(Qt::AlignCenter);
            itemName->setTextAlignment(Qt::AlignCenter);
            itemPrice->setTextAlignment(Qt::AlignCenter);

            QColor backgroundColor(0, 0, 0, 204);
            orderNumberItem->setBackground(backgroundColor);
            itemName->setBackground(backgroundColor);
            itemPrice->setBackground(backgroundColor);

            ui->tableWidgetOrderQueue->setItem(row, 0, orderNumberItem);
            ui->tableWidgetOrderQueue->setItem(row, 1, itemName);
            ui->tableWidgetOrderQueue->setItem(row, 2, itemPrice);
            row++;
        }

        ui->listWidgetOrderServed->clear();
        std::stack<QStringList> tempStack = servedOrdersStack;
        while (!tempStack.empty()) {
            QStringList servedOrder = tempStack.top();
            tempStack.pop();
            QListWidgetItem *listItem = new QListWidgetItem("#" + servedOrder[0] + " - " + servedOrder[1] + " - " + servedOrder[2]);
            listItem->setTextAlignment(Qt::AlignCenter);
            listItem->setBackground(QColor(0, 0, 0, 204));
            listItem->setForeground(Qt::white);
            listItem->setFont(QFont("Arial", 10, QFont::Bold));
            listItem->setData(Qt::UserRole, "border-bottom: 1px solid white;");
            ui->listWidgetOrderServed->addItem(listItem);
        }

        ui->labelDequeuePush->setText(QString("Order #%1 has been served").arg(order[0]));

        if (!ordersQueue.empty()) {
            QStringList nextOrder = ordersQueue.front();
            ui->labelFront->setText(QString("Next Order: #%1 - %2").arg(nextOrder[0], nextOrder[1]));
        } else {
            ui->labelFront->setText("Next Order: ...");
        }

        if (!servedOrdersStack.empty()) {
            QStringList lastServedOrder = servedOrdersStack.top();
            ui->labelPeek->setText(QString("Last Order served: #%1 - %2").arg(lastServedOrder[0], lastServedOrder[1]));
        } else {
            ui->labelPeek->setText("Last Order served: ...");
        }
    }
}

void ViewOrdersDialog::on_pushButtonPop_clicked()
{
    if (!servedOrdersStack.empty()) {
        servedOrdersStack.pop();

        ui->listWidgetOrderServed->clear();
        std::stack<QStringList> tempStack = servedOrdersStack;
        while (!tempStack.empty()) {
            QStringList servedOrder = tempStack.top();
            tempStack.pop();
            QListWidgetItem *listItem = new QListWidgetItem("#" + servedOrder[0] + " - " + servedOrder[1] + " - " + servedOrder[2]);
            listItem->setTextAlignment(Qt::AlignCenter);
            listItem->setBackground(QColor(0, 0, 0, 204));
            listItem->setForeground(Qt::white);
            listItem->setFont(QFont("Arial", 10, QFont::Bold));
            listItem->setData(Qt::UserRole, "border-bottom: 1px solid white;");
            ui->listWidgetOrderServed->addItem(listItem);
        }

        if (!servedOrdersStack.empty()) {
            QStringList lastServedOrder = servedOrdersStack.top();
            ui->labelPeek->setText(QString("Last Order served: #%1 - %2").arg(lastServedOrder[0], lastServedOrder[1]));
        } else {
            ui->labelPeek->setText("Last Order served: ...");
        }
    }
}

