#include "wordfile.h"
int fsize,fspace,fCsize,fEsize,fHsize;//字体大小，行间距，中文字宽，英文字宽，字高
int min_w,min_h,max_w,max_h;//编辑区左边界，上边界，右边界，下边界
int mouse_x,mouse_y;//鼠标的xy坐标
int mouse_flag=0;//标志是否为框选状态，0代表正常模式，1代表正按下拖动，2代表已经松开且选中有效区域

MiniLine* del_l=NULL;//backspace删除行时，记录要删除的行

WordFile::WordFile()//新建空文件，有一个空段
{
    head=new MiniLine;
    head->nextL=NULL;
}

Cursor::Cursor()//新建光标
{
    the_x=0;
    the_y=0;
    the_l=1;
    the_c=1;
    the_p=1;
    the_b=1;
    is_show=1;
    b_ptr=NULL;
    l_ptr=NULL;
}

void Cursor::copy_Cur(Cursor &other)//将other光标拷贝给当前光标
{
    the_x=other.the_x;
    the_y=other.the_y;
    the_l=other.the_l;
    the_c=other.the_c;
    the_p=other.the_p;
    the_b=other.the_b;
    is_show=other.is_show;
    b_ptr=other.b_ptr;
    l_ptr=other.l_ptr;
}

int Cursor::operator ++(int)//光标右移一位，处理不了换页事件
{
    int unicode;
    int rear_flag=0;//判断是否是段尾,0不是，1是
    int the_size;
    QChar c;

    if(b_ptr==NULL){
        if(l_ptr->length+1==the_p)
            rear_flag=1;
        else{//在段尾输入时不需要换行，不修改rear_flag
            b_ptr=l_ptr->Lrear;
            the_c=1;
            the_b=b_ptr->Bnum;
        }
    }
    else if(b_ptr->Bhead[the_c-1].isNull()){
        rear_flag=1;
    }//先判断是否是段尾，块为空或所指字符为空即为段尾

    if(rear_flag==0){//不在段尾
        c=b_ptr->Bhead[the_c-1];
        unicode=c.unicode();
        if(unicode>0x1000&&unicode<0xffff){
            the_x+=fCsize;
            the_size=fCsize;
        }
        else {
            the_x+=fEsize;
            the_size=fEsize;
        }//读取光标所指字符，并且判断中英文后光标后移

        if(the_x>max_w-fEsize/2){//超出右边界，需要换行
            the_x=min_w-fEsize/2+the_size;
            the_y+=fHsize+fspace;
        }

        the_c++;//光标后移
        if(the_c>100){//跨块
            the_c=1;
            this->b_ptr=b_ptr->nextB;
            the_b++;
        }
        the_p++;
    }
    else if(l_ptr->nextL!=NULL){//在段尾，且不在最后一行，光标直接移动到下一行
        the_x=min_w-fEsize/2;
        the_y+=fHsize+fspace;
        l_ptr=l_ptr->nextL;
        b_ptr=l_ptr->Lhead;
        the_b=1;
        the_l++;
        the_c=1;
        the_p=1;
    }
    else return -1;//在最后一行末尾，不处理

    if(the_y<=max_h)
        return 1;//正常情况
    else return 0;//需要向下翻页
}

int Cursor::operator --(int)//光标左移，不处理换行，换页事件
{
    int unicode;
    int head_flag=0;//判断是否是段首，1是，0不是
    int the_size;
    QChar c;
    if(the_p==1){
        head_flag=1;
    }//先判断是否是段首

    if(head_flag==0){//不是段首
        the_c--;
        the_p--;//光标前移
        if(the_c<=0){//跨块
            the_c=100;
            if(b_ptr!=NULL)
                b_ptr=b_ptr->preB;
            else
                b_ptr=l_ptr->Lrear;
            the_b=b_ptr->Bnum;
        }

        c=b_ptr->Bhead[the_c-1];
        unicode=c.unicode();
        if(unicode>0x1000&&unicode<0xffff){
            the_x-=fCsize;
            the_size=fCsize;
        }
        else {
            the_x-=fEsize;
            the_size=fEsize;
        }//读取光标所指字符，并且判断中英文后光标前移

        if(the_x<=min_w-fEsize/2&&the_p!=1){
            the_y-=fHsize+fspace;
        }//在同一段中移到前一行末尾
    }
    else if(l_ptr->preL!=NULL){//光标在段首且不在第一段，直接移到前一段段尾
        the_x=min_w-fEsize/2-1;
        the_y-=fHsize+fspace;
        l_ptr=l_ptr->preL;
        b_ptr=l_ptr->Lrear;
        the_b=b_ptr->Bnum;
        the_l--;
        the_c=b_ptr->length+1;
        if(the_c>100){
            the_c=1;
            the_b+=1;
            b_ptr=NULL;
        }
        the_p=l_ptr->length+1;
    }

    if(the_y<min_h){
        return -1;//需要向上翻页
    }
    else if(the_x<=min_w-fEsize/2&&the_p!=1){
        mouse_x=max_w-1;
        mouse_y=the_y;
        return 0;//需要定位到上一行行尾
    }
    else return 1;//正常情况
}

int Cursor::operator --()//backspa回删事件，不处理删除行，换页事件
{
    int unicode;
    int head_flag=0;//判断是否为段首
    int the_size;
    int r_flag=0;//返回值
    QChar c;


    if(the_p==1){
        head_flag=1;
    }//判断是否为段首
    if(head_flag==0){//不是段首
        if(the_x==min_w-fEsize/2){
            the_y-=fHsize+fspace;
            r_flag=-1;//光标在行首，需要删除上一行最后一个字符
        }
        else{//光标不在行首
            the_c--;
            the_p--;//光标前移
            if(the_c<=0){//跨块
                the_c=100;
                if(b_ptr!=NULL)
                    b_ptr=b_ptr->preB;
                else
                    b_ptr=l_ptr->Lrear;
                the_b=b_ptr->Bnum;
            }

            c=b_ptr->Bhead[the_c-1];//记录要删除的字符
            l_ptr->LDelCh(the_p);//删除字符

            unicode=c.unicode();
            if(unicode>0x1000&&unicode<0xffff){
                the_x-=fCsize;
                the_size=fCsize;
            }
            else {
                the_x-=fEsize;
                the_size=fEsize;
            }//判断所删字符是中英文，光标位置前移

            if(the_x<=min_w-fEsize/2&&the_p!=1){
                r_flag=1;//删除之后光标位于行首，则跳到上一行行尾
                the_y-=fHsize+fspace;
            }
        }
    }
    else if(l_ptr->preL!=NULL){
        r_flag=2;//光标在段首，且不在第一段
        del_l=l_ptr;//需要删除行，先记录下来删除段的内容
        MiniLine* num_l=NULL;
        num_l=l_ptr->nextL;
        del_l->preL->nextL=num_l;//修改上一段的nextL指针
        if(num_l!=NULL){//删除行的下一段不空
            num_l->preL=del_l->preL;//修改下一段的preL指针
            l_ptr=l_ptr->preL;
            b_ptr=l_ptr->Lhead;
            the_c=1;
            the_p=1;
            the_b=1;

            while(num_l!=NULL){//修改之后所有段的段号
                num_l->Lnum--;
                num_l=num_l->nextL;
            }
        }
        the_y-=fHsize+fspace;//光标位置上移
    }
    mouse_x=max_w-1;
    mouse_y=the_y;

    return r_flag;
}

int Cursor::enter(){//处理换行事件，只有光标在段尾时处理，否则交给上级函数处理
    int rear_flag=0;//判断是否为段尾，1是，0不是
    int r_flag=0;//返回值
    QChar c;
    if(b_ptr==NULL){
        rear_flag=1;
    }
    else{
        c=b_ptr->Bhead[the_c-1];
        if(c.isNull())
            rear_flag=1;
    }//先判断是否为段尾

    if(rear_flag==1){//是段尾，直接插入一个新段
        MiniLine* next_l=l_ptr->nextL;
        int n=l_ptr->Lnum+1;
        l_ptr->nextL=new MiniLine;
        l_ptr->nextL->preL=l_ptr;
        l_ptr=l_ptr->nextL;
        l_ptr->Lnum=n;
        b_ptr=l_ptr->Lhead;
        the_l=n;
        the_b=1;
        the_c=1;
        the_p=1;
        the_x=min_w-fEsize/2;
        the_y+=fHsize+fspace;
        if(next_l!=NULL){//不在最后一段，在中间添加一段
            l_ptr->nextL=next_l;
            next_l->preL=l_ptr;
            while(next_l!=NULL){//之后的段号都加一
                next_l->Lnum++;
                next_l=next_l->nextL;
            }
        }
    }
    else r_flag=1;//返回1正常
    return r_flag;//返回0代表需要处理回车符之后的字符后再换行
}

void Cursor::debug()//debug时用，输出光标信息
{
    qDebug()<<"the_b"<<the_b;
    qDebug()<<"the_p"<<the_p;
    qDebug()<<"the_c"<<the_c;
    qDebug()<<"the_l"<<the_l;
    qDebug()<<"the_x"<<the_x;
    qDebug()<<"the_y"<<the_y;
    if(l_ptr!=NULL)
        qDebug()<<"l_ptr"<<l_ptr->Lnum;
    if(b_ptr!=NULL)
        qDebug()<<"b_ptr"<<b_ptr->Bnum;
}

WordFile::~WordFile()
{
    delete head;
}


