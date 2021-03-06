#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    // this slots are going to be executed whenever
    // a signal is going to be submited
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void ChangeNumberSign();
};
#endif // MAINWINDOW_H
