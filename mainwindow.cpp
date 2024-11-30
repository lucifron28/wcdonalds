#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewordersdialog.h"
#include "placeorderdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidgetMenu->setColumnCount(4);
    ui->tableWidgetMenu->setHorizontalHeaderLabels(QStringList()
                                                   << "Item Name"
                                                   << "Description"
                                                   << "Price"
                                                   << "Category");

    menuItems = {
        "Margherita Pizza,Classic cheese and tomato pizza,8.99,Main Course",
        "Caesar Salad,Romaine lettuce with Caesar dressing,5.99,Appetizer",
        "Chocolate Lava Cake,Warm chocolate cake with molten center,6.50,Dessert",
        "Spaghetti Carbonara,Pasta with creamy bacon sauce,10.99,Main Course",
        "Lemonade,Freshly squeezed lemonade,2.50,Beverage",
        "Garlic Bread,Crispy bread with garlic butter,3.99,Appetizer",
        "Tiramisu,Classic Italian coffee dessert,5.50,Dessert",
        "Grilled Salmon,Salmon fillet with lemon butter sauce,14.99,Main Course",
        "Cappuccino,Freshly brewed Italian coffee,3.50,Beverage",
        "Chicken Wings,Spicy grilled chicken wings,7.99,Appetizer"
    };

    ui->tableWidgetMenu->setRowCount(menuItems.size());

    for (int i = 0; i < menuItems.size(); ++i) {
        QStringList details = menuItems[i].split(",");
        for (int j = 0; j < details.size(); ++j) {
            ui->tableWidgetMenu->setItem(i, j, new QTableWidgetItem(details[j]));
        }
    }

    // Adjust the table for better visibility
    ui->tableWidgetMenu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetMenu->setEditTriggers(QAbstractItemView::NoEditTriggers);

    viewOrdersDialog = new ViewOrdersDialog(this);
    placeOrderDialog = new PlaceOrderDialog(this);

    connect(ui->pushButtonOrderHistory, &QPushButton::clicked, this, &MainWindow::on_viewOrdersButton_clicked);
    connect(ui->pushButtonPlaceOrdrer, &QPushButton::clicked, this, &MainWindow::on_placeOrderButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList MainWindow::getMenuItems() const {
    return menuItems;
}

void MainWindow::on_viewOrdersButton_clicked() {
    viewOrdersDialog->exec();
}

void MainWindow::on_placeOrderButton_clicked() {
    placeOrderDialog->exec();
}

ViewOrdersDialog* MainWindow::getViewOrdersDialog() const {
    return viewOrdersDialog;
}
