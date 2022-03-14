#include "searchwindow.h"
#include "ui_searchwindow.h"
#include<qDebug>
SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchWindow)
{

    this->setMaximumHeight(200);
    this->setMaximumWidth(600);
    ui->setupUi(this);;
    setWindowTitle(QStringLiteral("查找"));
    setAttribute(Qt::WA_DeleteOnClose);
}

SearchWindow::~SearchWindow()
{
    delete ui;
}


void SearchWindow::on_pushButton_clicked()
{
    emit sendData(ui->lineEdit->text());
}

void SearchWindow::on_closeButton_clicked()
{
    close();
}
