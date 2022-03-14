#include "miniline.h"

MiniBlock::MiniBlock(){//新建一个空块
    Bhead =new QChar[100];
    nextB=NULL;
    preB=NULL;
    Bnum=1;
    length=0;
}

MiniBlock::MiniBlock(QString &s,int n){//新建一个内容为s，块号为n的块
    Bhead =new QChar[100];
    int i;
    int l=s.size();
    for(i=0;i<l;i++){
        Bhead[i]=s.at(i);
    }
    length=l;
    nextB=NULL;
    preB=NULL;
    Bnum=n;
}

MiniBlock::~MiniBlock(){//块析构
    delete []Bhead;
}

QChar MiniBlock::BAddCh(int p, QChar c){//在p位置（前）插入c,插入后越界则返回最后一个字符
    int i;
    QChar t='\0';//t为返回值
    if(length==100){
        t=Bhead[99];
    }
    else if(length!=0)
        Bhead[length]=Bhead[length-1];
    for(i=length;i>=p;i--){//p位置开始每个字符后移
        Bhead[i]=Bhead[i-1];
    }
    Bhead[p-1]=c;
    if(length<100){
        length++;
    }
    return t;
}

QChar MiniBlock::BDelCh(int p){//删除p位置的字符
    int i;
    QChar t=Bhead[p-1];
    int l=length;
    if(l==100){
        l=99;
    }
    for(i=p-1;i<l;i++){//p位置之后的字符全部前移
        Bhead[i]=Bhead[i+1];
    }
    length--;
    Bhead[length]='\0';
    return t;
}

MiniLine::MiniLine(){//新建一个空段
    Lhead =new MiniBlock();
    Lrear=Lhead;
    Bcount=1;
    length=0;
    nextL=NULL;
    preL=NULL;
    Lnum=1;
}

MiniLine::MiniLine(QString& s,int num){//新建一个内容为s，段号为num的段
    int l=s.size();
    length=l;
    int p=0,n=0;
    int count=1;
    if(l!=0){
        if(l>=100){
            n=100;
            l-=100;
        }
        else {
            n=l;
            l=0;
        }//l为s中剩余的字符数，n为当前需要放入块中的字符数
        QString bs = s.mid(p,n);
        Lhead =new MiniBlock(bs,count);
        MiniBlock* cur_ptr=Lhead;
        MiniBlock* pre_ptr=Lhead;
        for(p=100;p<length;p+=100){//以一百个字符为单位新建块
            if(l>=100){
                n=100;
                l-=100;
            }
            else {//最后一个块长度不一定为100
                n=l;
                l=0;
            }
            bs = s.mid(p,n);
            count++;
            cur_ptr=new MiniBlock(bs,count);
            cur_ptr->preB=pre_ptr;
            pre_ptr->nextB=cur_ptr;
            pre_ptr=cur_ptr;
        }
        Lrear=cur_ptr;
    }
    else{//空段
        Lhead =new MiniBlock();
        Lrear =Lhead;
    }
    Bcount=count;
    nextL=NULL;
    preL=NULL;
    Lnum=num;
}

MiniLine::~MiniLine(){//析构段
    MiniBlock* B=Lhead->nextB;
    while(B!=NULL){
        Lhead->~MiniBlock();
        Lhead=B;
        B=B->nextB;
    }
    Lhead->~MiniBlock();
}

void MiniLine::LAddCh(int p, QChar c){//在p位置（前）插入c
    int i;
    int b;//块号
    int l=p%100;//块中位置
    if(l==0){
        l=100;
        b=p/100-1;
    }
    else b=p/100;

    if(b+1>Bcount){//在段尾插入字符，且正好需要新建一个块
        Bcount++;
        Lrear->nextB=new MiniBlock();
        Lrear->nextB->preB=Lrear;
        Lrear=Lrear->nextB;
        Lrear->Bnum=Bcount;
    }
    MiniBlock* B=Lhead;
    for(i=0;i<b;i++){//定位到插入位置所在的块
        B=B->nextB;
    }
    for(i=b;i<Bcount;i++){//插入字符后，需要在插入位置之后的所有快中后移一个字符
        c=B->BAddCh(l,c);
        l=1;
        B=B->nextB;
    }
    if(!c.isNull()){//插入后可能需要在段尾新建一个块
        Bcount++;
        B=new MiniBlock();
        B->Bnum=Bcount;
        B->BAddCh(1,c);
        Lrear->nextB=B;
        B->preB=Lrear;
        Lrear=B;
    }
    length++;
}

void MiniLine::LDelCh(int p){//在p位置删除一个字符
    int i;
    QChar c;
    int b;//删除位置所在块
    int l=p%100;//在块中的位置
    if(l==0){
        l=100;
        b=p/100-1;
    }
    else b=p/100;//定位删除位置

    MiniBlock* pre_B=Lhead;
    MiniBlock* cur_B;
    for(i=0;i<b;i++){//移动到删除位置所在块
        pre_B=pre_B->nextB;
    }
    pre_B->BDelCh(l);//删除字符
    cur_B=pre_B->nextB;
    length--;
    if(cur_B!=NULL){//如果不是在最后一个块，需要将之后块中的字符前移
        for(i=b+1;i<=Bcount-2;i++){
            c=cur_B->BDelCh(1);
            pre_B->BAddCh(100,c);
            pre_B=cur_B;
            cur_B=cur_B->nextB;
        }
        c=cur_B->BDelCh(1);//将块中第一个字符删除
        pre_B->BAddCh(100,c);//再将后一个块的第一个字符插入到块尾
        if(cur_B->length==0){//可能需要删除最后一个块
            pre_B->nextB=NULL;
            delete cur_B;
            Lrear=pre_B;
            Bcount--;
        }
    }
    else if(pre_B->length==0&&length!=0){//可能要删除最后一个块，但是仅有一个块的话不删
        pre_B->preB->nextB=NULL;
        Lrear=pre_B->preB;
        delete pre_B;
        Bcount--;
    }

}





