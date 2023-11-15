#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "medicament_ui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::openMedicamentUI);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openMedicamentUI()
{
    Medicament_ui *medicamentDialog = new Medicament_ui();
    medicamentDialog->show();

    close();
}
