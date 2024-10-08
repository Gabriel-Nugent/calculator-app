#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , calc(new App::Calc)
{
    ui->setupUi(this);
    attachHandlers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// connects signals to slots
// https://doc.qt.io/qt-6/signalsandslots.html
void MainWindow::attachHandlers() {
    // connect calculator digit buttons
    connect(ui->zero,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->one,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->two,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->three,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->four,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->five,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->six,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->seven,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->eight,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->nine,&QPushButton::clicked,this,&MainWindow::onButtonClick);

    // connect calculator operator buttons
    connect(ui->add,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->subtract,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->multiply,&QPushButton::clicked,this,&MainWindow::onButtonClick);
    connect(ui->divide,&QPushButton::clicked,this,&MainWindow::onButtonClick);

    // connect calculator main functions
    connect(ui->equals,&QPushButton::clicked,this,&MainWindow::onButtonEquals);
    connect(ui->clear,&QPushButton::clicked,this,&MainWindow::onButtonClear);
}

// handles all ui button clicks that send a character to the calculator
void MainWindow::onButtonClick() {
    // retrieve the clicked button signal
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    calc->addSymbol(clickedButton->text().toStdString());
    ui->display->setText(QString::fromStdString(calc->getExpression()));
}

// handles clearing the calculator display
void MainWindow::onButtonClear() {
    calc->clear();
    ui->display->setText("");
}

// handles calculating the final result
void MainWindow::onButtonEquals() {
    std::string result = std::to_string(calc->getTotal());

    // remove trailing whitespace
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);

    // remove decimal if it is the last character
    if (result[result.size()-1] == '.') {
        result.erase(result.size()-1, std::string::npos);
    }

    // update display
    ui->display->setText(QString::fromStdString(result));

    calc->clear();
}
