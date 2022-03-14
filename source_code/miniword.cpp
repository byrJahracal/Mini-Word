#include "miniword.h"

MiniWord::MiniWord(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MiniWord)
{
    setAttribute(Qt::WA_InputMethodEnabled, true);
    ui->setupUi(this);//ui设置
    fsize=24;
    Minit();//初始化
    mytimer = new QTimer(this);//光标定时器
    connect(mytimer, SIGNAL(timeout()), this, SLOT(cur_p_show()));
    mytimer->start(500);//光标每0.5秒跳变一次

    SAVED=true;
    wordfile=NULL;
    on_action_newFile_triggered();//初始默认新建一个文件
}

MiniWord::~MiniWord()
{
    delete ui;
}

void MiniWord::KeyOperate(long key, int IsUp){//处理普通输入事件，第二个参数为0小写状态，为1大写状态
    switch (key) {
    case Qt::Key_Left:{
        MiniLeft();
        qDebug()<<"方向键-左键"<<cur_p.the_p;
        break;
    }

    case Qt::Key_Right:{
        MiniRight();
        qDebug()<<"方向键-右键"<<cur_p.the_p;
        break;
    }

    case Qt::Key_Up:{//模拟鼠标在光标位置正上方点击
        mouse_x=cur_p.the_x+fEsize/2;
        mouse_y=cur_p.the_y-fHsize-fspace;
        if(mouse_y<min_h){//可能需要向上翻页
            mouse_y=cur_p.the_y;
            UpLeft_top();
        }
        LocCur_p();
        qDebug()<<"方向键-上键";
        break;
    }

    case Qt::Key_Down:{//模拟鼠标在光标位置正下方点击
        mouse_x=cur_p.the_x+fEsize/2;
        mouse_y=cur_p.the_y+fHsize+fspace;
        if(mouse_y>max_h){//可能需要向下翻页
            mouse_y=cur_p.the_y;
            DownLeft_top();
        }
        LocCur_p();
        qDebug()<<"方向键-下键";
        break;
    }

    case Qt::Key_Return:{
        SAVED=false;
        if(mouse_flag==2)//块操作时，要先删除块再换行
            BDelete();
        MiniEnter();
        qDebug()<<"回车return";
        break;
    }

    case Qt::Key_Enter:{
        SAVED=false;
        if(mouse_flag==2)//块操作时，要先删除块再换行
            BDelete();
        MiniEnter();
        qDebug()<<"回车enter";
        break;
    }

    case Qt::Key_Delete:{
        MiniDelete();//delete为向后删除
        SAVED=false;
        qDebug()<<"delete";
        break;
    }

    case Qt::Key_Backspace:{//backspace为向前删除
        SAVED=false;
        if(mouse_flag!=2)
            MiniBack();
        else
            BDelete();//块操作时为删除选中区域
        qDebug()<<"删除键";
        break;
    }

    case Qt::Key_PageDown:{//向下翻页
        DownLeft_top();//先翻页
        mouse_x=cur_p.the_x+fEsize/2;
        if(cur_p.the_y>min_h)
            mouse_y=cur_p.the_y-fHsize-fspace;
        LocCur_p();//光标上移
        qDebug()<<"pagedown键";
        break;
    }

    case Qt::Key_PageUp:{
        UpLeft_top();//先翻页
        mouse_x=cur_p.the_x+fEsize/2;
        if(cur_p.the_y<max_h)
            mouse_y=cur_p.the_y+fHsize+fspace;
        else mouse_y=max_h-1;
        LocCur_p();//光标下移
        qDebug()<<"pageup键";
        break;
    }
    case Qt::Key_Home:{
        initl_t();//回到文章开头
        qDebug()<<"home键";
        break;
    }
    case Qt::Key_End:{//调到文章末尾
        while(cur_p.l_ptr->nextL!=NULL||(cur_p.b_ptr!=NULL&&!(cur_p.b_ptr->Bhead[cur_p.the_c-1].isNull()))){
            MiniRight();//模拟不断按方向右键知道光标移动到末尾
        }
        qDebug()<<"end键";
        break;
    }
    case Qt::Key_Shift://shift建不处理
        qDebug()<<"shift键";
        break;

    default:{//输入有效英文字符
        SAVED=false;
        QChar c;
        if(key>=65 &&key<=90 && IsUp==0){//小写字母
            key+=32;
        }
        qDebug()<<"按下    "<<(char)key;
        c=(char)(key);
        if(mouse_flag==2){//块操作时要先删除选中区域
            BDelete();
        }
        cur_p.l_ptr->LAddCh(cur_p.the_p,c);//插入字符
        MiniRight();//光标后移
        break;
    }
    }
    update();
}

void MiniWord::BDelete()//块删除
{
    if(mouse_flag==2){//有选中区域时
        int stop_l=sec_p.the_l;
        int stop_b=sec_p.the_b;
        int stop_c=sec_p.the_c;//记录删除块的首位置
        while(cur_p.the_l!=stop_l||cur_p.the_b!=stop_b||cur_p.the_c!=stop_c){
            MiniBack();//从块尾开始一个一个回删，直到块位置停止
        }
    }
    mouse_flag=0;//取消选中块状态
}

void MiniWord::BCopy()//块拷贝
{
    if(mouse_flag==2){//有选中块时
        copy_s.clear();//先清空剪切板
        int stop_l=thi_p.the_l;
        int stop_b=thi_p.the_b;
        int stop_c=thi_p.the_c;//记录块尾位置
        cur_p.copy_Cur(sec_p);//光标移动到块首
        int i=0;
        QChar c;
        while(cur_p.the_l!=stop_l||cur_p.the_b!=stop_b||cur_p.the_c!=stop_c){//后移光标一个一个字符拷贝，直到块尾
            if(cur_p.b_ptr==NULL){
                c='\n';
            }
            else {
                c=cur_p.b_ptr->Bhead[cur_p.the_c-1];
                if(c.isNull())
                    c='\n';
            }//判断是否在段尾，选中区域跨段的话，在剪切板中存入一个'|n'
            copy_s[i]=c;
            i++;
            MiniRight();
        }
        copy_s[i]='\0';//剪切板结束标志
    }
}

void MiniWord::BPast(QString s)//块粘贴，在光标处粘贴字符串s
{
    if(!s.isNull()){
        QChar c;
        int i=0;
        c=s[i];
        while(!c.isNull()){//将块中字符一个一个插入到光标位置
            if(c!='\n'){//普通字符直接插入
                cur_p.l_ptr->LAddCh(cur_p.the_p,c);
                MiniRight();
            }
            else{//处理回车符
                MiniEnter();
            }
            i++;
            c=s[i];
        }
    }
}

void MiniWord::MiniBack()//处理backspace从光标处向前删除
{
    int flag = --cur_p;//回删一个字符
    if(mouse_y<min_h){//光标位置跑到编辑区域之上，需要向上翻页
        UpLeft_top();
        mouse_y=min_h;
        mouse_x=max_w-1;
    }
    if(flag!=0){//所有需要换行换段的情况都要从新定位光标到行尾或段尾
        LocCur_p();
    }
    if(flag==-1){//定位到上一行行尾后删除该行最后一个字符
        --cur_p;
    }
    else if(flag==2){//需要删除段的情况
        mouse_x=cur_p.the_x+fEsize/2;
        mouse_y=cur_p.the_y;
        int i=0,p=cur_p.the_p;
        MiniLine* l=cur_p.l_ptr;//光标已经定位到上一行行尾
        MiniBlock* b=del_l->Lhead;//读取刚刚删除掉的段
        QChar c=b->Bhead[i];
        while(!c.isNull()){//将删除段中的字符一个一个插入到上一段段尾
            l->LAddCh(p,c);
            p++;
            i++;
            if(i>=100){
                b=b->nextB;
                i=0;
            }
            if(b==NULL)
                c='\0';
            else
                c=b->Bhead[i];
        }
        delete del_l;
        LocCur_p();//再次确认光标位置
    }
}

void MiniWord::MiniRight()//处理方向键右键，光标右移
{
    int l=cur_p.the_l;
    int flag=cur_p++;//光标右移
    if(flag==0){//处理翻页事件
        DownLeft_top();//向下翻页
        if(enter_flag==1)//回车事件会调用这个函数，此时需要将sec_p（记录块操作块首的光标）上移
            sec_p.the_y-=fHsize+fspace;
        mouse_x=min_w;
        mouse_y=max_h;
        LocCur_p();//定位到下一行或段的首位
        if(cur_p.the_l==l)//保证光标只会出现在上一行行尾或这行行首中的一个位置
            MiniRight();
    }
}

void MiniWord::MiniLeft()//处理方向键左键，光标左移
{
    int flag=cur_p--;//光标左移
    if(flag==0)
        LocCur_p();//处理换行换段事件，定位到行尾
    else if(flag==-1){//处理换页事件
        UpLeft_top();//向上翻页
        mouse_y=min_h;
        mouse_x=max_w-1;
        LocCur_p();//重新定位光标
    }
}

void MiniWord::MiniDelete()//处理delete建，此处做光标右移再回删操作
{
    int flag=cur_p++;
    if(flag==0){
        DownLeft_top();
        mouse_x=min_w;
        mouse_y=max_h;
        LocCur_p();
    }//右移光标，详见MiniRight函数
    if(flag!=-1){
        flag=--cur_p;
        if(flag!=0){
            LocCur_p();
        }
        if(flag==-1){
            --cur_p;
        }
        else if(flag==2){
            mouse_x=cur_p.the_x+fEsize/2;
            mouse_y=cur_p.the_y;
            wordfile->Lcount--;
            int i=0,p=cur_p.the_p;
            MiniLine* l=cur_p.l_ptr;
            MiniBlock* b=del_l->Lhead;
            QChar c=b->Bhead[i];
            while(!c.isNull()){
                l->LAddCh(p,c);
                p++;
                i++;
                if(i>=100){
                    b=b->nextB;
                    i=0;
                }
                if(b==NULL)
                    c='\0';
                else
                    c=b->Bhead[i];
            }
            delete del_l;
            LocCur_p();
        }
    }//光标回删，详见MiniBack函数
}

void MiniWord::MiniEnter()//处理回车事件，换行处理
{
    int flag=cur_p.enter();//光标回车处理
    if(flag==1){//光标不在段尾，需要光标后内容下移
        QString save_s=copy_s;
        sec_p.copy_Cur(cur_p);//记录需要下移内容的开始位置
        int start_b=sec_p.the_b;
        int start_c=sec_p.the_c;

        enter_flag=1;
        while(cur_p.b_ptr!=NULL&&!(cur_p.b_ptr->Bhead[cur_p.the_c-1].isNull())){
            MiniRight();//光标后移至段尾
        }
        enter_flag=0;

        thi_p.copy_Cur(cur_p);//记录段尾位置
        mouse_flag=2;
        BCopy();//拷贝需要下移的所有内容
        mouse_flag=0;
        while(cur_p.the_b!=start_b||cur_p.the_c!=start_c){
            MiniBack();//删掉需要下移的内容
        }
        cur_p.enter();//回车处理，建立新的一段
        if(cur_p.the_y>max_h){//可能需要翻页
            DownLeft_top();
            mouse_x=min_w;
            mouse_y=max_h;
            LocCur_p();
        }
        start_b=cur_p.the_b;
        start_c=cur_p.the_c;
        BPast(copy_s);//把需要下移的内容粘贴到新的一行
        while(cur_p.the_b!=start_b||cur_p.the_c!=start_c){
            MiniLeft();//光标移动到新的一行的行首
        }
        copy_s=save_s;
    }
    else if(cur_p.the_y>max_h){//光标在段尾简单换行时，也可能处理翻页事件
        DownLeft_top();
        mouse_x=min_w;
        mouse_y=max_h;
        LocCur_p();
    }
}

void MiniWord::keyPressEvent(QKeyEvent *event)//处理非中文输入事件
{
    this->setFocus();

    long key = event->key();
    char ch=key;
    if(event->modifiers()==Qt::ControlModifier && event->key()!=Qt::Key_Control){//处理control+特殊键
        qDebug()<<"按住ctrl  "<<event->key()<<"  "<<ch;
        switch (key) {
        case Qt::Key_X:{//剪切块
            BCopy();//先拷贝
            BDelete();//再删除
            SAVED=false;
            mouse_flag=0;
        }
            break;
        case Qt::Key_C:{//块拷贝
            BCopy();
        }
            break;
        case Qt::Key_V:{//块粘贴
            if(mouse_flag==2)
                BDelete();//如果当前有选中块，先删除原有内容再粘贴
            BPast(copy_s);
            SAVED=false;
        }
            break;
        default:
            break;
        }
    }
    else if(event->key()!=Qt::Key_Control){//处理回删，回车，上下左右键，普通英文数字输入等
        KeyOperate(key,GetKeyState(VK_CAPITAL));
    }
}

void MiniWord::mousePressEvent(QMouseEvent *event)//鼠标按下事件
{
    mouse_flag=0;//取消块选中状态
    mouse_x=event->x();
    mouse_y=event->y();
    LocCur_p();//定位光标
    update();
}

void MiniWord::mouseReleaseEvent(QMouseEvent *event)//鼠标放开事件
{
    mouse_x=event->x();
    mouse_y=event->y();
    if(mouse_x>=max_w)
        mouse_x=max_w-1;
    else if(mouse_x<min_w)
        mouse_x=min_w;
    if(mouse_y>max_h)
        mouse_y=max_h;
    else if(mouse_y<min_h)
        mouse_y=min_h;
    //读取鼠标放开位置的坐标，不可超出编辑区
    int dx=mouse_x-cur_p.the_x;
    int dy=mouse_y-cur_p.the_y;//记录此时鼠标距离按下时的xy距离
    if(mouse_flag==1&&((dx>2||dx<-2)||(dy>2||dy<-2))){//鼠标移动距离超过一定值，认为创建了选中区域
        sec_p.copy_Cur(cur_p);//记录块首位置
        LocCur_p();//定位到块尾位置
        if(cur_p.the_x!=sec_p.the_x||cur_p.the_y!=sec_p.the_y){
            mouse_flag=2;//两个位置不一样，创建块
            int ex_flag=0;
            if(cur_p.the_y<sec_p.the_y){
                ex_flag=1;
            }
            else if(cur_p.the_y==sec_p.the_y&&cur_p.the_x<sec_p.the_x){
                ex_flag=1;
            }//判断是否需要交换块首块尾位置
            if(ex_flag==1){//交换块首块尾，保证cur_p和thi_p永远在右下方，sec_p在左上方
                Cursor p;
                p.copy_Cur(cur_p);
                cur_p.copy_Cur(sec_p);
                sec_p.copy_Cur(p);
            }
            thi_p.copy_Cur(cur_p);//记录块尾位置
        }
    }
    else mouse_flag=0;//鼠标移动距离过短，不生成选中区域
    update();
}

void MiniWord::mouseMoveEvent(QMouseEvent *event)//鼠标移动事件
{
    mouse_x=event->x();
    mouse_y=event->y();
    if(mouse_x>=max_w)//鼠标不可以移动到编辑区范围外
        mouse_x=max_w-1;
    else if(mouse_x<min_w)
        mouse_x=min_w;
    if(mouse_y>max_h)
        mouse_y=max_h;
    else if(mouse_y<min_h)
        mouse_y=min_h;
    mouse_flag=1;//切换到显示框选框状态
    update();
}

void MiniWord::inputMethodEvent(QInputMethodEvent *event)//处理中文输入
{
    if(event->commitString().length()!=0){//输入不为空时
        if(mouse_flag==2)
            BDelete();//如果有选中块，先删除块
        int len=event->commitString().length();
        QChar c;
        for(int i=0;i<len;i++){//一个一个插入中文字符
            c = event->commitString()[i];
            cur_p.l_ptr->LAddCh(cur_p.the_p,c);//插入字符
            MiniRight();//光标后移
        }
        SAVED=false;
    }
    mouse_flag=0;
    update();
}

void MiniWord::paintEvent(QPaintEvent *event)//画面输出
{
    QPainter painter(this);
    QChar c;
    ushort unicode;
    int i,the_size;
    MiniBlock* cur_b=left_top.b_ptr;
    MiniLine* cur_l=left_top.l_ptr;
    int x=left_top.the_x,y=left_top.the_y;
    i=left_top.the_c-1;

    painter.setRenderHint(QPainter::Antialiasing, true);//取消锯齿
    painter.setBackground(QColor(0, 230, 255,255));
    painter.setFont(QFont("楷体",fsize));

    painter.setPen(QPen(QColor(0, 230, 255,255), 4));// 设置画笔颜色、宽度（边框颜色）

    painter.setBrush(QColor(245, 255, 225,255));// 设置画刷颜色（矩形填充颜色）
    painter.drawRect(min_w-fspace*2, min_h-fHsize-fspace*2, max_w-min_w+fspace*4, max_h-min_h+fHsize+fspace*4);//画出编辑区

    if(mouse_flag==2){//选中状态时，标蓝所选字符串
        painter.setPen(QPen(QColor(50, 100, 155,0), 0));
        painter.setBrush(QColor(0, 255, 255,100));
        cur_b=sec_p.b_ptr;
        cur_l=sec_p.l_ptr;
        i=sec_p.the_c-1;
        MiniBlock* stop_b=thi_p.b_ptr;
        MiniLine* stop_l=thi_p.l_ptr;
        int stop_c=thi_p.the_c-1;
        int rear_flag=0;
        x=sec_p.the_x+fEsize/2;
        y=sec_p.the_y;
        while(i!=stop_c||cur_b!=stop_b||cur_l!=stop_l){//光标在所选区域内向后移动，在每个字处画出蓝色小方块
            if(cur_b==NULL){
                rear_flag=1;
            }
            else{
                c=cur_b->Bhead[i];
                if(c.isNull())
                    rear_flag=1;
            }
            if(rear_flag==0){
                unicode=c.unicode();
                if(unicode>0x1000&&unicode<0xffff){
                    the_size=fCsize;
                }
                else{
                    the_size=fEsize;
                }
                if(x+the_size<max_w){
                    painter.drawRect(x,y-fHsize-fspace,the_size,fHsize+fspace);
                    x+=the_size;
                }
                else{
                    y+=fHsize+fspace;
                    if(y<=max_h){
                        x=min_w;
                        painter.drawRect(x,y-fHsize-fspace,the_size,fHsize+fspace);
                        x+=the_size;
                    }
                }
                i++;
                if(i>=100){
                    i=0;
                    cur_b=cur_b->nextB;
                }
            }
            else if(rear_flag==1){
                cur_l=cur_l->nextL;
                if(cur_l!=NULL){
                    cur_b=cur_l->Lhead;
                    y+=fHsize+fspace;
                    x=min_w;
                    i=0;
                }
            }
            //qDebug()<<cur_l->Lnum<<cur_b->Bnum<<c;
            rear_flag=0;
        }
        cur_b=left_top.b_ptr;
        cur_l=left_top.l_ptr;
        x=left_top.the_x;
        y=left_top.the_y;
        i=left_top.the_c-1;
    }
    else if(mouse_flag==1){//左键按下且移动鼠标时，显示拖拽框
        painter.setPen(QPen(QColor(50, 100, 155,200), 2));
        painter.setBrush(QColor(0, 100, 155,120));
        painter.drawRect(cur_p.the_x+fEsize/2, cur_p.the_y-fHsize-fspace, mouse_x-cur_p.the_x-fEsize/2, mouse_y-cur_p.the_y+fHsize+fspace);
    }
    painter.setPen(QColor(0, 0, 0,255));//设置文字颜色为黑色
    if(cur_p.is_show==true)
        painter.drawText(cur_p.the_x,cur_p.the_y,"|");//光标显示（闪烁）
    while(cur_b!=NULL&&cur_l!=NULL&&y<=max_h){//在编辑区域内显示文本，left_top为记录编辑区最左上角的光标
        c=cur_b->Bhead[i];
        if(c.isNull()){//读到段尾则光标移到下一段
            i=0;
            cur_l=cur_l->nextL;
            if(cur_l!=NULL){
                cur_b=cur_l->Lhead;
                y+=fHsize+fspace;
                x=min_w;
            }

        }
        else{
            unicode=c.unicode();
            if(unicode>0x1000&&unicode<0xffff){
                the_size=fCsize;
            }
            else{
                the_size=fEsize;
            }//判断中英文，确定文字大小
            if(x+the_size<max_w){
                painter.drawText(x,y,c);//在xy位置画出字符c，xy为该字符的左下角
                x+=the_size;
            }
            else{
                y+=fHsize+fspace;
                if(y<=max_h){
                    x=min_w;
                    painter.drawText(x,y,c);
                    x+=the_size;
                }
            }
            i++;//光标后移
            if(i>=100){//跨块
                i=0;
                cur_b=cur_b->nextB;
                if(cur_b==NULL){
                    cur_l=cur_l->nextL;
                    if(cur_l!=NULL){
                        cur_b=cur_l->Lhead;
                        y+=fHsize+fspace;
                        x=min_w;
                    }
                }
            }
        }
    }
}

void MiniWord::setpaintersize(int minw, int maxw, int minh, int maxh)//设置编辑区边界
{
    min_w=minw;
    max_w=maxw;
    min_h=minh;
    max_h=maxh;
}

void MiniWord::Minit()
{
    the_weight=1024;//宽
    the_height=720;//高
    //fsize=24;//字体
    fspace=2;//行间距
    fCsize=fsize*2;//中文字宽
    fEsize=fsize;//英文字宽
    fHsize=fsize*1.5;//字高
    setFixedSize(the_weight,the_height);//设置主窗口固定大小
    setpaintersize(fspace*5,the_weight-fspace*5,26+fHsize+fspace*3,the_height-fspace*3);//设置编辑区大小
}

void MiniWord::initl_t()//初始化记录编辑区开始位置的光标left_top和cur_p
{
    left_top.l_ptr=wordfile->head;//从文章开始位置显示
    left_top.b_ptr=left_top.l_ptr->Lhead;
    left_top.the_l=1;
    left_top.the_b=1;
    left_top.the_c=1;
    left_top.the_p=1;
    left_top.the_x=min_w;
    left_top.the_y=min_h;
    cur_p.l_ptr=wordfile->head;
    cur_p.b_ptr=cur_p.l_ptr->Lhead;
    cur_p.the_l=1;
    cur_p.the_b=1;
    cur_p.the_c=1;
    cur_p.the_p=1;
    cur_p.the_x=min_w-fEsize/2;
    cur_p.the_y=min_h;
}

void MiniWord::initsec_thi()//初始化记录选中区域起始结束位置的光标
{
    sec_p.l_ptr=wordfile->head;
    sec_p.b_ptr=sec_p.l_ptr->Lhead;
    sec_p.the_l=1;
    sec_p.the_b=1;
    sec_p.the_c=1;
    sec_p.the_p=1;
    sec_p.the_x=min_w-fEsize/2;
    sec_p.the_y=min_h;
    thi_p.l_ptr=wordfile->head;
    thi_p.b_ptr=sec_p.l_ptr->Lhead;
    thi_p.the_l=1;
    thi_p.the_b=1;
    thi_p.the_c=1;
    thi_p.the_p=1;
    thi_p.the_x=min_w-fEsize/2;
    thi_p.the_y=min_h;
    mouse_flag=0;
}

void MiniWord::LocCur_p()//根据鼠标点击位置定位当前光标
{
    MiniLine* cur_l=left_top.l_ptr;
    MiniBlock* cur_b=left_top.b_ptr;
    QChar c;
    int i,x1=min_w,x2=min_w;
    ushort unicode;
    int x=min_w,y=min_h;
    int flag=0,the_size;
    c=cur_b->Bhead[left_top.the_c-1];
    i=left_top.the_c-1;//从编辑区最左上角开始遍历寻找，x,y为当前遍历位置，mouse_x,mouse_y为点击目标位置

    if(mouse_y>=min_h-fHsize&&mouse_y<=max_h&&mouse_x>=x&&mouse_x<max_w){//如果点击位置在编辑区内才会处理
        while(cur_b!=NULL&&cur_l!=NULL&&flag==0){
            c=cur_b->Bhead[i];
            if(y-mouse_y<0&&y<=max_h-fHsize-fspace){//y在点击位置之上时，不断向下寻找
                while(!c.isNull()&&x<max_w){//不需要换行时，在当前行向右寻找
                    unicode=c.unicode();
                    if(unicode>0x1000&&unicode<0xffff){
                        x+=fCsize;
                    }
                    else{
                        x+=fEsize;
                    }//确认中英文，字宽
                    if(x<max_w)
                        i++;//移到下一个字符
                    if(i>=100){//跨段
                        cur_b=cur_b->nextB;
                        i=0;
                        if(x<max_w){
                            if(cur_b==NULL)
                                c='\0';
                            else
                                c=cur_b->Bhead[i];
                        }
                    }
                    else if(x<max_w)
                        c=cur_b->Bhead[i];
                }
                if(c.isNull()){
                    if(cur_l->nextL!=NULL){
                        cur_l=cur_l->nextL;
                        cur_b=cur_l->Lhead;
                        i=0;
                    }
                    else flag=1;
                }
                if(flag!=1){
                    y+=fHsize+fspace;
                    x=min_w;
                }
            }
            else {//已经找到了所在行，则向右寻找
                unicode=c.unicode();
                if(c.isNull())
                    flag=1;
                else {
                    if(unicode>0x1000&&unicode<0xffff){
                        the_size=fCsize;
                    }
                    else{
                        the_size=fEsize;
                    }
                    x2+=the_size/2;
                    if(!(mouse_x>=x1&&mouse_x<=x2)&&x2+the_size/2<max_w){//x1为前一个字符的中间位置，x2为后一个字符的中间位置，若x在x1，x2之间则认为点击位置在此处
                        x1=x2;
                        x2+=the_size/2;
                        x=x2;
                        i++;
                        if(i>=100){
                            i=0;
                            cur_b=cur_b->nextB;
                        }
                    }
                    else {
                        flag=1;
                    }
                }

            }
        }
        cur_p.b_ptr=cur_b;//已经找到，更新光标所有信息
        cur_p.l_ptr=cur_l;
        cur_p.the_c=i+1;
        cur_p.the_l=cur_l->Lnum;
        if(cur_p.b_ptr!=NULL)
            cur_p.the_b=cur_p.b_ptr->Bnum;
        else
            cur_p.the_b=cur_l->Bcount+1;
        x=x-fEsize/2;
        cur_p.the_x=x;
        cur_p.the_y=y;
        cur_p.the_p=(cur_p.the_b-1)*100+cur_p.the_c;
    }
}

void MiniWord::DownLeft_top()
{
    MiniLine* l=left_top.l_ptr;

    int x=min_w;
    MiniBlock* b=left_top.b_ptr;
    int i=left_top.the_c-1;
    QChar c=b->Bhead[i];
    int unicode=0,the_size;
    int flag=0;
    while(flag==0){
        if(c.isNull()){
            if(l->nextL!=NULL){
                left_top.l_ptr=l->nextL;
                left_top.b_ptr=left_top.l_ptr->Lhead;
                left_top.the_l=left_top.l_ptr->Lnum;
                left_top.the_b=1;
                left_top.the_c=1;
                left_top.the_p=1;
            }
            flag=1;
        }
        else{
            unicode=c.unicode();
            if(unicode>0x1000&&unicode<0xffff){
                the_size=fCsize;
            }
            else{
                the_size=fEsize;
            }
            x+=the_size;
            if(x>=max_w){
                left_top.b_ptr=b;
                left_top.the_l=left_top.l_ptr->Lnum;
                left_top.the_b=b->Bnum;
                left_top.the_c=i+1;
                left_top.the_p=100*(left_top.the_b-1)+left_top.the_c;
                flag=1;
            }
            else{
                i++;
                if(i>=99){
                    i=0;
                    b=b->nextB;
                }
                if(b==NULL){
                    c='\0';
                }
                else
                    c=b->Bhead[i];
            }
        }
    }
}

void MiniWord::UpLeft_top()
{
    int flag=0;
    int x=min_w;
    MiniBlock* b;
    int i;
    QChar c;
    int unicode=0,the_size;
    MiniLine* cur_l=left_top.l_ptr;
    if(left_top.the_p==1){
        if(cur_l->preL!=NULL){
            cur_l=cur_l->preL;
            b=cur_l->Lhead;
            i=0;
            c=b->Bhead[i];
            left_top.l_ptr=cur_l;
            left_top.b_ptr=b;
            left_top.the_p=1;
            left_top.the_c=1;
            left_top.the_b=1;
            left_top.the_l=cur_l->Lnum;
            while(flag==0){
                if(c.isNull()){
                    flag=1;
                }
                else{
                    unicode=c.unicode();
                    if(unicode>0x1000&&unicode<0xffff){
                        the_size=fCsize;
                    }
                    else{
                        the_size=fEsize;
                    }
                    x+=the_size;
                    if(x>=max_w){
                        left_top.b_ptr=b;
                        left_top.the_l=cur_l->Lnum;
                        left_top.the_b=b->Bnum;
                        left_top.the_c=i+1;
                        left_top.the_p=100*(left_top.the_b-1)+left_top.the_c;
                        x=min_w+the_size;
                    }
                    i++;
                    if(i>=99){
                        i=0;
                        b=b->nextB;
                    }
                    if(b==NULL){
                        c='\0';
                    }
                    else
                        c=b->Bhead[i];

                }
            }
        }
    }
    else{
        int the_C=left_top.the_c;
        int the_B=left_top.the_b;
        b=cur_l->Lhead;
        int num_b=b->Bnum;
        i=0;
        c=b->Bhead[i];
        left_top.l_ptr=cur_l;
        left_top.b_ptr=b;
        left_top.the_p=1;
        left_top.the_c=1;
        left_top.the_b=1;
        left_top.the_l=cur_l->Lnum;
        while(flag==0){
            if(i+1==the_C&&num_b==the_B){
                flag=1;
            }
            else{
                unicode=c.unicode();
                if(unicode>0x1000&&unicode<0xffff){
                    the_size=fCsize;
                }
                else{
                    the_size=fEsize;
                }
                x+=the_size;
                if(x>=max_w){
                    left_top.b_ptr=b;
                    left_top.the_l=cur_l->Lnum;
                    left_top.the_b=b->Bnum;
                    left_top.the_c=i+1;
                    left_top.the_p=100*(left_top.the_b-1)+left_top.the_c;
                    x=min_w+the_size;
                }
                i++;
                if(i>=99){
                    i=0;
                    b=b->nextB;
                    num_b++;
                }
                if(b==NULL){
                    c='\0';
                }
                else
                    c=b->Bhead[i];
            }
        }
    }
}

void MiniWord::cur_p_show()
{
    cur_p.is_show=!cur_p.is_show;
    update();
}

void MiniWord::on_action_newFile_triggered()    //新建文件
{
    qDebug()<<"新建文件";
    if(wordfile!=NULL&&SAVED==false){  //编辑区有未保存内容
        int a=QMessageBox:: question(NULL, "新建",
                                     "编辑区有未保存内容，是否先保存文件再新建？",
                                     QMessageBox::Save, QMessageBox::No, QMessageBox::Cancel);
        if(a==QMessageBox::Cancel){
            qDebug()<<"取消新建";
            return;
        }

        else if(a==QMessageBox::No){ //放弃内容，新建
            bool a=QMessageBox::warning(NULL, "警告", "未保存的工作将丢失，是否继续？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(a==true){
                wordfile->~WordFile();
                wordfile=NULL;
                path="";
                SAVED=true;
                on_action_newFile_triggered();
            }
            else
                return;
        }
        else if(a==QMessageBox::Save){   //先保存文件再新建
            on_action_savefile_triggered();
            on_action_quit_triggered();
            wordfile=new WordFile();
            initl_t();
            SAVED=true;
        }

    }
    else if(wordfile!=NULL&&SAVED==true){   //编辑区有已未保存内容
        on_action_quit_triggered();
        wordfile=new WordFile();
        initl_t();
        initsec_thi();
    }
    else{                                   //编辑区无内容
        wordfile=new WordFile();
        initl_t();
        initsec_thi();
        SAVED=true;
    }
    update();
}

void MiniWord::on_action_openfile_triggered()   //打开文件
{
    qDebug()<<"打开文件";
    if(wordfile!=NULL&&SAVED==false){  //编辑区有未保存内容
        int a=QMessageBox:: question(NULL, "打开",
                                     "编辑区有未保存内容，是否先保存文件再打开？",
                                     QMessageBox::Save, QMessageBox::No, QMessageBox::Cancel);
        if(a==QMessageBox::Cancel){
            qDebug()<<"取消打开";
            return;
        }

        else if(a==QMessageBox::No){ //放弃内容
            bool a=QMessageBox::warning(NULL, "警告", "未保存的工作将丢失，是否继续？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(a==true){
                wordfile->~WordFile();
                wordfile=NULL;
                SAVED=true;
                goto doit;
            }
            else
                return;
        }
        else if(a==QMessageBox::Save){   //先保存文件再新建
            on_action_savefile_triggered();
            on_action_quit_triggered();
            goto doit;
        }
    }
    else if(wordfile!=NULL&&SAVED==true){   //编辑区有已保存内容
        on_action_quit_triggered();
        goto doit;
    }
    else{   //编辑区无内容，直接读取文件
doit:
        path="";
        path = QFileDialog::getOpenFileName(this);
        if(path.length()==0)
            return;
        QFile file(path);

        if (file.open(QIODevice ::ReadOnly | QIODevice ::Text)){
            QTextStream in(&file);

            QString s = in.readLine();

            wordfile = new WordFile();

            int lcount=1;
            wordfile->head = new MiniLine(s,lcount);
            MiniLine *curline=wordfile->head;
            curline->nextL=NULL;
            curline->preL=NULL;

            while (!in.atEnd())
            {
                lcount++;
                s = in.readLine();
                curline->nextL=new MiniLine(s,lcount);
                curline->nextL->preL=curline;
                curline=curline->nextL;
                curline->nextL=NULL;
            }
            wordfile->Lcount=lcount;
        }

        SAVED=true;
        initl_t();
        initsec_thi();
        qDebug()<<"打开成功";
    }
    update();
}

void MiniWord::on_action_savefile_triggered()   //保存文件
{
    if(wordfile==NULL)
        return;

    qDebug()<<"保存";
    if(path.length()==0){   //从未保存过，无路径，则要求用户输入保存位置，否则用原来的路径
        path = QFileDialog::getSaveFileName(this);
    }
    QFile file(path);
    if (file.open(QIODevice ::WriteOnly | QIODevice ::Text)){
        QTextStream out(&file);
        if(wordfile != NULL && wordfile->head!=NULL){
            MiniLine *curLine = wordfile->head;
            while(curLine!=NULL){
                MiniBlock *curBlock = curLine->Lhead;
                while(curBlock!=NULL){
                    for(int i=0;i<curBlock->length;i++){
                        out<<curBlock->Bhead[i];
                    }
                    curBlock=curBlock->nextB;
                }
                out<<endl;
                curLine=curLine->nextL;
            }
        }
        SAVED=true;
        qDebug()<<"保存成功";
    }
}

void MiniWord::on_action_save_as_triggered()    //另存为文件
{
    if(wordfile==NULL)
        return;

    qDebug()<<"另存为";
    QString new_path = QFileDialog::getSaveFileName(this);

    QFile file(new_path);
    if (file.open(QIODevice ::WriteOnly | QIODevice ::Text)){
        QTextStream out(&file);
        if(wordfile != NULL && wordfile->head!=NULL){
            MiniLine *curLine = wordfile->head;
            while(curLine!=NULL){
                MiniBlock *curBlock = curLine->Lhead;
                while(curBlock!=NULL){
                    for(int i=0;i<curBlock->length;i++){
                        out<<curBlock->Bhead[i];
                    }
                    curBlock=curBlock->nextB;
                }
                out<<endl;
                curLine=curLine->nextL;
            }
        }
        SAVED=true;
        qDebug()<<"另存为成功";
    }
}

void MiniWord::on_action_quit_triggered()   //关闭文件
{
    if(wordfile==NULL)
        return;

    if(SAVED==false){  //编辑区有未保存内容
        int a=QMessageBox:: question(NULL, "打开",
                                     "编辑区有未保存内容，是否先保存文件再关闭？",
                                     QMessageBox::Save, QMessageBox::No, QMessageBox::Cancel);
        if(a==QMessageBox::Cancel){
            qDebug()<<"取消关闭";
            return;
        }

        else if(a==QMessageBox::No){ //放弃内容
            bool a=QMessageBox::warning(NULL, "警告", "未保存的工作将丢失，是否继续？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(a==true){
                wordfile->~WordFile();
                wordfile=NULL;
                SAVED=true;
                qDebug()<<"已关闭";
                on_action_newFile_triggered();
            }
            else
                return;
        }
        else if(a==QMessageBox::Save){   //先保存文件再新建
            on_action_savefile_triggered();
            on_action_quit_triggered();
        }
    }
    else{//SAVED==true
        wordfile->~WordFile();
        wordfile=NULL;
        path="";
        qDebug()<<"已关闭";
        on_action_newFile_triggered();
    }
    update();
}

void MiniWord::on_action_search_triggered()     //点击查找弹出窗口
{
    SearchWindow *s =new SearchWindow(this);
    connect(s,SIGNAL(sendData(QString)),this,SLOT(receiveData_to_search(QString)));
    s->show();
    update();
}

void MiniWord::on_action_replace_triggered()       //点击替换弹出窗口
{
    ReplaceWindow *re =new ReplaceWindow(this);
    connect(re,SIGNAL(sendData_to_search(QString)),this,SLOT(receiveData_to_search(QString)));
    connect(re,SIGNAL(sendData_to_replace(QString,QString)),this,SLOT(receiveData_to_replace(QString,QString)));
    connect(re,SIGNAL(sendData_to_replace_all(QString,QString)),this,SLOT(receiveData_to_replace_all(QString,QString)));
    re->show();
    update();
}

void MiniWord::receiveData_to_search(QString s)       //查找
{
    if(wordfile==NULL||s.length()==0)
        return ;
    qDebug()<<"开始查找";
    mouse_flag=0;
    initsec_thi();
    int find=kmp(s);
    if(find==1){
        qDebug()<<"找到";
        thi_p.copy_Cur(cur_p);
        //光标现在位置是块的尾
        //复制一个新光标
        for(int i=0;i<s.length();i++){
            MiniLeft();
            //相当于键盘按向左
        }
        //光标现在位置是块的头
        sec_p.copy_Cur(cur_p);
        mouse_flag=2;

        for(int i=0;i<s.length();i++){
            MiniRight();
            //相当于键盘按向右
        }
    }

    else{
        QMessageBox::about(NULL, "提示", "未找到");
    }
    //system("pause");
    update();
}

void MiniWord::receiveData_to_replace(QString s1,QString s2)    //替换
{
    mouse_flag=0;
    if(wordfile==NULL)
        return ;

    int s1_len=s1.length();
    int s2_len=s2.length();
    mouse_flag=0;
    initsec_thi();
    if(s1_len==0)
        return;

    int find=kmp(s1);
    if(find==1){
        qDebug()<<"找到";
        thi_p.copy_Cur(cur_p);
        //光标现在位置是块的尾
        //复制一个新光标
        for(int i=0;i<s1_len;i++){
            MiniLeft();
            //相当于键盘按向左
        }
        //光标现在位置是块的头
        sec_p.copy_Cur(cur_p);
        mouse_flag=2;   //光标选中

        for(int i=0;i<s1_len;i++){
            MiniRight();
            //相当于键盘按向右
        }
        //system("pause");
        update();
        //system("pause");
        int a=QMessageBox:: question(NULL, "替换","已找到，是否替换？",QMessageBox::Yes, QMessageBox::No);
        if(a==QMessageBox::No)
            return;

        //开始替换
        BDelete();
        sec_p.copy_Cur(cur_p);  //块的头
        BPast(s2);
        thi_p.copy_Cur(cur_p);  //块的尾
        mouse_flag=2;

        SAVED=false;
    }

    else{
        QMessageBox::about(NULL, "提示", "未找到");
    }
    update();
}

void MiniWord::receiveData_to_replace_all(QString s1,QString s2)    //全部替换
{
    if(wordfile==NULL)
        return ;
    qDebug()<<"开始全部替换";
    int s1_len=s1.length();
    int s2_len=s2.length();

    if(s1_len==0)
        return;
    int find=kmp(s1);
    if(find==0){
        QMessageBox::about(NULL, "替换", "未找到");
        return ;
    }
    else{
        int a=QMessageBox:: question(NULL, "全部替换","已找到，是否全部替换？",QMessageBox::Yes, QMessageBox::No);
        if(a==QMessageBox::No)
            return ;
    }

    while(find==1){
        qDebug()<<"找到";
        for(int i=0;i<s1_len;i++){
            MiniBack();
        }
        for(int i=0;i<s2_len;i++){
            BPast(s2);
        }
        qDebug()<<"替换完毕";
        find=kmp(s1);
    }
    QMessageBox::about(NULL, "替换", "全部替换完毕");
    SAVED=false;
}

int MiniWord::kmp(QString s)    //改进的kmp模式匹配算法
{
    qDebug()<<"进入kmp";
    int s_len = s.length();
    int nextval[s_len] = {0};

    get_nextval( s, nextval );     //get_nextval[]
    int  j = 0;

    MiniLine *curLine=cur_p.l_ptr;
    MiniBlock *curBlock=NULL;
    while(curLine!=NULL){
        curBlock=cur_p.b_ptr;
        while(curBlock!=NULL){
            for(int i=cur_p.the_c;i<=curBlock->length;){    //遍历主串
                if(j<s_len) {
                    if( j == -1 || curBlock->Bhead[i-1] == s[j] ) {
                        i++;
                        MiniRight();
                        j++;
                    }
                    else {
                        j = nextval[j];
                    }
                }
                if(j>=s_len){
                    qDebug()<<cur_p.b_ptr->Bhead[i-1];
                    return 1;
                }
            }
            if(cur_p.b_ptr==NULL||cur_p.b_ptr->Bhead[cur_p.the_c-1].isNull())
               MiniRight();
            curBlock=curBlock->nextB;
        }
        j=0;
        curLine=curLine->nextL;
    }

    return 0;
}

void get_nextval(QString s, int *nextval)  //计算nextval数组
{
    int len = s.length();
    int i = 0, j = -1;

    nextval[0] = -1;

    while( i < len-1 ) {
        if( j == -1 || s[i] == s[j] ) {
            ++i;
            ++j;

            if( s[i] != s[j] ) {
                nextval[i] = j;
            } else {
                nextval[i] = nextval[j];
            }
        }
        else {
            j = nextval[j];
        }
    }
}

void MiniWord::closeEvent(QCloseEvent *event)
{
    if(wordfile==NULL||SAVED==true)
        event->accept();

    else{
        switch( QMessageBox:: question(NULL, "关闭","编辑区有未保存内容，是否先保存文件再关闭？",QMessageBox::Save, QMessageBox::No, QMessageBox::Cancel))
        {
        case QMessageBox::Save:{
            if(path.length()==0){   //从未保存过，无路径，则要求用户输入保存位置，否则用原来的路径
                path = QFileDialog::getSaveFileName(this);
            }
            QFile file(path);
            if (file.open(QIODevice ::WriteOnly | QIODevice ::Text)){
                QTextStream out(&file);
                if(wordfile != NULL && wordfile->head!=NULL){
                    MiniLine *curLine = wordfile->head;
                    while(curLine!=NULL){
                        MiniBlock *curBlock = curLine->Lhead;
                        while(curBlock!=NULL){
                            for(int i=0;i<curBlock->length;i++){
                                out<<curBlock->Bhead[i];
                            }
                            curBlock=curBlock->nextB;
                        }
                        out<<endl;
                        curLine=curLine->nextL;
                    }
                    event->accept();
                }
            }
            else{//实际上没有成功保存
                event->ignore();
            }
            break;
            //endcase1
        }

        case QMessageBox::No:
            SAVED=true;
            event->accept();
            break;
        default:
            event->ignore();
            break;
        }
    }
}

void MiniWord::on_action_addsize_triggered()
{
    if(fsize<36)
        fsize+=2;
    Minit();
    initl_t();
    initsec_thi();
}

void MiniWord::on_action_cutsize_triggered()
{
    if(fsize>6)
        fsize-=2;
    Minit();
    initl_t();
    initsec_thi();
}
