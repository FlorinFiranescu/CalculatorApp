#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString butNume = "button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butNume);
        // connect the numButtons[i] with the callback NumPressed
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->addButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->subtractButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->multiplyButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->divideButton, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->equalButton, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->signChangeButton, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    // the sender is going to return a pointer
    // to the pressed button
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){
      ui->Display->setText(butVal);
    } else {
        QString newVal = displayVal + butVal;
        double dbNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dbNewVal, 'g', 16));
    }
}

void MainWindow::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }
    ui->Display->setText("");
}
void MainWindow::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dbDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dbDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dbDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dbDisplayVal;
        } else {
            solution = calcVal / dbDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    if(displayVal.length()){
        if(displayVal.startsWith("-")){
            // is negative
            displayVal = displayVal.remove(0, 1);
        } else{
            // is positive
            displayVal = "-" + displayVal;
        }
    }
    double dblDisplayVal = displayVal.toDouble();
    ui->Display->setText(QString::number(dblDisplayVal));
}

