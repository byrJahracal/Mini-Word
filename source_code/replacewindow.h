#ifndef REPLACEWINDOW_H
#define REPLACEWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReplaceWindow;
}

class ReplaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReplaceWindow(QWidget *parent = 0);
    ~ReplaceWindow();

private slots:
    void on_search_clicked();

    void on_replace_clicked();

    void on_relpace_all_clicked();

    void on_cancel_clicked();

signals:
    void  sendData_to_search(QString);     //传查找数据

    void  sendData_to_replace(QString,QString);   //传替换

    void  sendData_to_replace_all(QString,QString);   //传全部替换

private:
    Ui::ReplaceWindow *ui;
};

#endif // REPLACEWINDOW_H
