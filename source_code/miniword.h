#ifndef MINIWORD_H
#define MINIWORD_H

#include <QMainWindow>
#include <Qtimer>
#include <wordfile.h>
#include <QScrollBar>
#include "ui_miniword.h"
#include "QKeyEvent"
#include "QPainter"
#include<windows.h>
#include<QMessageBox>
#include<searchwindow.h>
#include<ui_searchwindow.h>
#include "replacewindow.h"
#include "ui_replacewindow.h"

void get_nextval(QString s, int *nextval);


extern int fsize,fspace,fCsize,fEsize,fHsize;
extern int min_w,min_h,max_w,max_h;
extern int mouse_x,mouse_y;
extern MiniLine* del_l;
extern int mouse_flag;

namespace Ui {
class MiniWord;
}

class MiniWord : public QMainWindow
{
    Q_OBJECT

public:
    explicit MiniWord(QWidget *parent = 0);
    ~MiniWord();
    void keyPressEvent(QKeyEvent*event);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);
    void mouseMoveEvent(QMouseEvent*event);
    void inputMethodEvent(QInputMethodEvent*event);
    void paintEvent(QPaintEvent*event);
    void setpaintersize(int minw, int maxw, int minh, int maxh);
    void Minit();
    void initl_t();
    void initsec_thi();
    void LocCur_p();
    void DownLeft_top();
    void UpLeft_top();
    void KeyOperate(long key, int IsUp);
    void BDelete();
    void BCopy();
    void BPast(QString);
    void MiniBack();
    void MiniRight();
    void MiniLeft();
    void MiniDelete();
    void MiniEnter();

    int kmp(QString s);

    Cursor left_top;
    Cursor cur_p;
    Cursor sec_p;
    Cursor thi_p;
    QString copy_s;
    int the_weight,the_height;
    int enter_flag;

private slots:
    void on_action_newFile_triggered();

    void on_action_openfile_triggered();

    void on_action_quit_triggered();

    void on_action_savefile_triggered();

    void on_action_search_triggered();

    void on_action_replace_triggered();

    void on_action_save_as_triggered();

    void receiveData_to_search(QString);  //查找

    void receiveData_to_replace(QString,QString); //替换

    void receiveData_to_replace_all(QString,QString); //替换全部

    void cur_p_show();


    void on_action_addsize_triggered();

    void on_action_cutsize_triggered();

private:
    Ui::MiniWord *ui;
    WordFile* wordfile;			     //文件指针
    QString file_name;			          //文件名
    QString path;
    bool SAVED;					           //是否已保存的标志
    QTimer* mytimer;
    void closeEvent(QCloseEvent *event);

};

#endif // MINIWORD_H
