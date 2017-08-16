#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addPerson_clicked();

    void on_computeMon_clicked();

private:
    Ui::MainWindow *ui;
    QBoxLayout *leftLay;
    QBoxLayout *values;
};

#endif // MAINWINDOW_H
