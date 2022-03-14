#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>

namespace Ui {
class SearchWindow;
}

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchWindow(QWidget *parent = 0);
    ~SearchWindow();

private slots:
    void on_pushButton_clicked();

    void on_closeButton_clicked();

signals:
    void  sendData(QString);


private:
    Ui::SearchWindow *ui;
};

#endif // SEARCHWINDOW_H
