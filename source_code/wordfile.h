#ifndef WORDFILE_H
#define WORDFILE_H
#include <miniline.h>
#include "QFileDialog"
#include "QTextStream"

class Cursor{
public:
    Cursor();
    void copy_Cur(Cursor&);
    int the_x,the_y;//光标位置
    int the_l;//所在行号
    int the_b;//所在块号
    int the_c;//在块中的位置，1-100
    int the_p;//在行中的位置，1-无穷
    bool is_show;//是否显示
    MiniBlock* b_ptr;//所在块，可能为空
    MiniLine* l_ptr;//所在行
    int operator ++ (int);//返回1正常，返回0代表超出屏幕下届，-1代表已经是文章末尾
    int operator -- (int);//返回1正常，返回0代表退行，返回-1代表退行并超出上届
    int operator -- ();
    int enter();//返回0末尾换行，返回1非末尾换行
    void debug();
};

class WordFile
{
public:
    MiniLine *head;
    int Lcount;
    WordFile();
    ~WordFile();
};

#endif // WORDFILE_H
