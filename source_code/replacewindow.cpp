#include "replacewindow.h"
#include "ui_replacewindow.h"
#include<qdebug.h>
ReplaceWindow::ReplaceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReplaceWindow)
{

    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QStringLiteral("替换"));
}

ReplaceWindow::~ReplaceWindow()
{
    delete ui;
}

void ReplaceWindow::on_search_clicked()
{
    emit sendData_to_search(ui->lineEdit->text());
}

void ReplaceWindow::on_replace_clicked()
{
    emit sendData_to_replace(ui->lineEdit->text(),ui->lineEdit_2->text());
}

void ReplaceWindow::on_relpace_all_clicked()
{
    emit sendData_to_replace_all(ui->lineEdit->text(),ui->lineEdit_2->text());
}

void ReplaceWindow::on_cancel_clicked()
{
    close();
}
