#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "medicament_ui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  explicit  MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openMedicamentUI();



private:
    Ui::MainWindow *ui;
    Medicament_ui *medicamentUI ;
};
#endif // MAINWINDOW_H
