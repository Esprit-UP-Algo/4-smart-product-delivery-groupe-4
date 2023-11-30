#ifndef OUBLIER_H
#define OUBLIER_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class oublier;
}

class oublier : public QMainWindow
{
    Q_OBJECT

public:
    explicit oublier(QWidget *parent = nullptr);
    ~oublier();

signals:
    void passwordRecovered(const QString &password);

private slots:
    void on_pushButton_valider_clicked();

private:
    Ui::oublier *ui;
};

#endif // OUBLIER_H
