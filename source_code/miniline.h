#ifndef MINILINE_H
#define MINILINE_H
#include "QChar"
#include "QString"
#include<qDebug.h>

class MiniBlock{
public:
    MiniBlock();
    MiniBlock(QString &,int);
    ~MiniBlock();

    QChar BAddCh(int, QChar );
    QChar BDelCh(int);

    QChar* Bhead;
    MiniBlock* nextB;
    MiniBlock* preB;

    int length;
    int Bnum;

};

class MiniLine
{
public:
    MiniLine();
    MiniLine(QString&,int);
    ~MiniLine();

    void LAddCh(int,QChar);//范围1-length+1
    void LDelCh(int);//范围1-length

    int length;
    int Bcount;
    int Lnum;

    MiniBlock* Lhead;
    MiniBlock* Lrear;

    MiniLine* nextL;
    MiniLine* preL;
};

#endif // MINILINE_H
