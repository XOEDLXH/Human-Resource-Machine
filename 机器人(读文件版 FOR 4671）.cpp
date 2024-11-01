#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

//生成一些数据
int hand=-2147483648;//鸡器人手中的积木
int t;//当输入的指令总数为正整数时，t表示这个指令总数
int conducted_instruction;//总共执行的指令次数
int outputnum;//用来给总共输出的次数计数
int outcome;//游玩结果表示数 0成功 -1失败 
int ordernumber;// 玩家输入指令的总数，应该由一个程序找出
char code[1000][19];//储存玩家输入的指令
int already_inboxed,already_outboxed;

struct levelsave//level 1 2 3等关卡信息的储存
{
char name[40],instruction[300];//关卡名称和关卡说明
int inputn,inputsave[100],outputn,outputsave[100],validfloor,allowedcommands[8];//关卡积木总数，关卡所有积木，关卡输出积木总数，玩家游玩时关卡所有输出积木
int commandlimit,steplimit;//成就系统
}levelsaves[100];


struct level_status//机器人每一步的信息的即时储存，用于制作动画
{
int inputsave[100],outputsave[100],holdingblock=-2147483648,floor[25];//这一步还剩下的积木信息，这一步已输出的积木的信息，这一步手中的积木信息，这一步已占用的空地信息
string order_name;//这一步执行的指令名称
int executenumber_save;//（还没做！！！！）这是用来存储机器人站在哪一个空地上（即copyto和copyfrom的p->executenumber）
int theorderoforder;//还可以存一下每一个指令在第几行
int alreadyinbox,alreadyoutbox;
}levelstatus[9999];







//指令输入部分
struct order//创造一个order结构
{
    char ordername[20];
    int executenumber;
    int counter;
    order *next;
};

order *head;
order *headoforder;
order *temporary;

order *create(int order_number)//创造一个储存玩家所输入指令的容器
{   
    order *p=NULL;
    order *q=NULL;
    head=NULL;
     headoforder=NULL;
     temporary=NULL;
    for(int i=0;i<order_number;i++)
    {
        p = new order;
        for(int m=0;m<19;m++)
        {
            p->ordername[m]=code[i+1][m];//把用户的输入再原原本本地传送到code数组中(从code【1】【指令长度】开始)
        }
        p->counter=i+1;
        if(code[i+1][1]=='a'&&code[i+1][2]=='d'&&code[i+1][3]=='d')
        {
            int m=0;
            int q=100;
            for(int t=5;t<8;t++)
            {
                if(code[i+1][t]>=48&&code[i+1][t]<=57)// 检查输入的是不是数字
                {   
                m+=(int(code[i+1][t])-'0')*q;
                q/=10;
                }
                else 
                {
                    cout<<"Wrong Execute Number"<<endl;
                    outcome=1000+p->counter;
                    m=-1;
                    break;
                }

            }
            if(m!=-1)
            p->executenumber=m;
            else break;
        }
        else if(code[i+1][1]=='s'&&code[i+1][2]=='u'&&code[i+1][3]=='b')
        {
            int m=0;
            int q=100;
            for(int t=5;t<8;t++)
            {
             if(code[i+1][t]>=48&&code[i+1][t]<=57)
                {   
                m+=(int(code[i+1][t])-'0')*q;
                q/=10;
                }
                else 
                {
                    cout<<"Wrong Execute Number"<<endl;
                    outcome=1000+p->counter;
                    m=-1;
                    break;
                }

            }
            if(m!=-1)
            p->executenumber=m;
            else break;
        }
        else if(code[i+1][1]=='c'&&code[i+1][2]=='o'&&code[i+1][3]=='p'&&code[i+1][4]=='y'&&code[i+1][5]=='t'&&code[i+1][6]=='o')
        {
           int m=0;
            int q=100;
            for(int t=8;t<11;t++)
            {
             if(code[i+1][t]>=48&&code[i+1][t]<=57)
                {   
                m+=(int(code[i+1][t])-'0')*q;
                q/=10;
                }
                else 
                {
                    cout<<"Wrong Execute Number"<<endl;
                    outcome=1000+p->counter;
                    m=-1;
                    break;
                }

            }
            if(m!=-1)
            p->executenumber=m;
            else break;
        }
        else if(code[i+1][1]=='c'&&code[i+1][2]=='o'&&code[i+1][3]=='p'&&code[i+1][4]=='y'&&code[i+1][5]=='f'&&code[i+1][6]=='r'&&code[i+1][7]=='o'&&code[i+1][8]=='m')
        {
            int m=0;
            int q=100;
            for(int t=10;t<13;t++)
            {
             if(code[i+1][t]>=48&&code[i+1][t]<=57)
                {   
                m+=(int(code[i+1][t])-'0')*q;
                q/=10;
                }
                else 
                {
                    cout<<"Wrong Execute Number"<<endl;
                    outcome=1000+p->counter;
                    m=-1;
                    break;
                }

            }
            if(m!=-1)
            p->executenumber=m;
            else break;
        }
        else if(code[i+1][1]=='j'&&code[i+1][2]=='u'&&code[i+1][3]=='m'&&code[i+1][4]=='p')
        {
             int m=0;
            int q=100;
            for(int t=6;t<9;t++)
            {
            if(code[i+1][t]>=48&&code[i+1][t]<=57)
                {   
                m+=(int(code[i+1][t])-'0')*q;
                q/=10;
                }
                else 
                {
                    cout<<"Wrong Execute Number"<<endl;
                    outcome=1000+p->counter;
                    m=-1;
                    break;
                }

            }
            if(m!=-1)
            p->executenumber=m;
            else break;
        }
        else if(code[i+1][1]=='j'&&code[i+1][2]=='u'&&code[i+1][3]=='m'&&code[i+1][4]=='p'&&code[i+1][5]=='i'&&code[i+1][6]=='f'&&code[i+1][7]=='z'&&code[i+1][8]=='e'&&code[i+1][9]=='r'&&code[i+1][10]=='o')
        {
             int m=0;
            int q=100;
            for(int t=12;t<15;t++)
            {
             if(code[i+1][t]>=48&&code[i+1][t]<=57)
                {   
                m+=(int(code[i+1][t])-'0')*q;
                q/=10;
                }
                else 
                {
                    cout<<"Wrong Execute Number"<<endl;
                    outcome=1000+p->counter;
                    m=-1;
                    break;
                }

            }
            if(m!=-1)
            p->executenumber=m;
            else break;
        }
        
        if(head==NULL)
        {
            head=p;
            headoforder=p;
            temporary=p;
        }
        else 
        {
            q->next=p;
        }
        q=p;
        

    }
    if(head!=NULL)
    {
        q->next=NULL;
    }
    return head;
}





//关卡的积木生成

int output[10];

int output1()//第一关的输入数字
{   
   
    output[0]=1;
    output[1]=2;
    return 2;//有两个积木
}
int output2()//第二关的输入数字
{
   
    output[0]=-6;
    output[1]=6;
    output[2]=4;
    output[3]=-4;
    output[4]=0;
    output[5]=0;
    output[6]=18;
    output[7]=-18;
    return 8;
}
int output3()//第三关的输入数字
{
    
    output[0]=7;
    output[1]=-3;
    
    return 2;
}
int output4()//第四关的输入数字
{
    return 0;
}


int output_all(int levelnumber)
{
    if(levelnumber==1)
    { 
    return output1();
    }
    else if(levelnumber==2)
    return output2();
    else if(levelnumber==3)
    return output3();
    else if (levelnumber==4)
    return output4();
   return 0;
}





//传送带部分
struct conveyerbelt//创造一个名为”传送带“的结构
{
    int number;
    conveyerbelt *next;
};

conveyerbelt *firstnumleft;
conveyerbelt *firstnumright;
conveyerbelt *initialleft;
conveyerbelt *initialright;
conveyerbelt *stationary;

conveyerbelt *left(int levelnumber)//生成左边的传送带
{
    conveyerbelt *p=NULL;
    conveyerbelt *q=NULL;
    firstnumleft=NULL;
    initialleft=NULL;   
    for (int i=0;i<levelsaves[levelnumber].inputn;i++)//inputn是通过读文件的时候自动生成的总积木数
    {
    p = new conveyerbelt;
    p->number=levelsaves[levelnumber].inputsave[i];//这是文件中的数据
        if(firstnumleft==NULL)
        {
            firstnumleft=p;
            initialleft=p;
        }
        else
        {
        q->next=p;
        }
        q=p;
    }
    if(firstnumleft!=NULL)
    {
        q->next=NULL;
    }
   return firstnumleft;
}

conveyerbelt *right(int levelnumber)//生成右边的传送带
{
    conveyerbelt *p=NULL;
    conveyerbelt *q=NULL;
    firstnumright=NULL;
    initialright=NULL;
    stationary=NULL;
    for (int i=0;i<levelsaves[levelnumber].outputn;i++)
    {
    p = new conveyerbelt;
        if(firstnumright==NULL)
        {
            firstnumright=p;
            initialright=p;
            stationary=p;
        }
        else
        {
        q->next=p;
        }
        q=p;
    }
    if(firstnumright!=NULL)
    {
        q->next=NULL;
    }
   return firstnumright;
}





//关卡空地部分
int floor_base[3]={-2147483648,-2147483648,-2147483648};

int floor_num(int levelnumber)//生成对应关卡空地的数目
{
    if (levelnumber==1)
    return 0;
    else if (levelnumber==2)
    return 3;
    else if (levelnumber==3)
    return 3;
    return 0;

}

void initializer(int conducted_instruction)
{
    if(conducted_instruction!=1)
        {
            levelstatus[conducted_instruction].holdingblock=levelstatus[conducted_instruction-1].holdingblock;
            for(int i=0;i<25;i++)
            {
                levelstatus[conducted_instruction].floor[i]=levelstatus[conducted_instruction-1].floor[i];
            }
            for(int i=0;i<100;i++)
            {
                 levelstatus[conducted_instruction].inputsave[i]=  levelstatus[conducted_instruction-1].inputsave[i];
            }
            for(int i=0;i<100;i++)
            {
                 levelstatus[conducted_instruction].outputsave[i]=  levelstatus[conducted_instruction-1].outputsave[i];
            }
            levelstatus[conducted_instruction].executenumber_save= levelstatus[conducted_instruction-1].executenumber_save;
            levelstatus[conducted_instruction].theorderoforder-2147483648;
             levelstatus[conducted_instruction].alreadyinbox = levelstatus[conducted_instruction-1].alreadyinbox;
             levelstatus[conducted_instruction].alreadyoutbox = levelstatus[conducted_instruction-1].alreadyoutbox;
        }
        else
        {   
            
            levelstatus[conducted_instruction].holdingblock=-2147483648;
            for(int i=0;i<25;i++)
            {
                levelstatus[conducted_instruction].floor[i]=-2147483648;
            for(int i=0;i<100;i++)
            {
                 levelstatus[conducted_instruction].inputsave[i]=-2147483648;
            }
            for(int i=0;i<100;i++)
            {
                 levelstatus[conducted_instruction].outputsave[i]=-2147483648;
            }
            levelstatus[conducted_instruction].executenumber_save=-2147483648;
            levelstatus[conducted_instruction].theorderoforder-2147483648;
            levelstatus[conducted_instruction].alreadyinbox = 0;
             levelstatus[conducted_instruction].alreadyoutbox = 0;
        }
        }   
}



void robot(order *head,int levelnumber)//你的鸡器人
{  
    already_outboxed=0;//重置已输出积木数为0
    already_inboxed=0;//重置已输出积木数为0
    outputnum=0;//重置总输出次数计数为0
    conducted_instruction=0;
//第一关 
if(levelnumber==1)
{
    while(head!=NULL)
    {
        initializer(conducted_instruction+1);//初始化或继承,参数最小为1
    //inbox部分
    if(0==strcmp("inbox",head->ordername))//else if里千万不能混有if！！！
    {
    {
        
    if(firstnumleft==NULL)
    {
        break;
    }
   else
   {
  
    hand=firstnumleft->number;
    firstnumleft=firstnumleft->next;
    }
    
    }


    conducted_instruction++;
    levelstatus[conducted_instruction].theorderoforder=head->counter;
    head=head->next;
    already_inboxed++;
    levelstatus[conducted_instruction].alreadyinbox=already_inboxed;
    levelstatus[conducted_instruction].holdingblock=hand;
    levelstatus[conducted_instruction].order_name="inbox";
    if(firstnumleft!=NULL)//如果把if替换成while，必须加break，但是没有什么必要
    {

        if(already_inboxed!=levelsaves[levelnumber].inputn)
        {
            for(int i=0;i<levelsaves[levelnumber].inputn-already_inboxed;i++)
        {
            levelstatus[conducted_instruction].inputsave[i]=levelsaves[levelnumber].inputsave[already_inboxed+i];//这里存下尚且还在传送带上的方块为inputsave（从0开始计数）
            
        }
        }
    
    }
    }

//outbox部分
    else if(0==strcmp("outbox",head->ordername))
    {
        
    // head=head->next;
    if(hand!=-2147483648&&firstnumright!=NULL)//解决无限输出的问题
    {
    cout<<hand<<endl;
    outputnum++;//输出一次就加一
    firstnumright->number=hand;
    firstnumright=firstnumright->next;
    }
    else if (hand==-2147483648||firstnumright==NULL)
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
    }
    hand=-2147483648;
    conducted_instruction++;
    levelstatus[conducted_instruction].theorderoforder=head->counter;
    head=head->next;
    already_outboxed++;
    levelstatus[conducted_instruction].alreadyoutbox=already_outboxed;
    levelstatus[conducted_instruction].holdingblock=hand;//存下手中数字

        levelstatus[conducted_instruction].outputsave[already_outboxed]=hand;
    
    //存下已经输出的东西
   levelstatus[conducted_instruction].order_name="outbox";
    }

//非法输入
    else
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=head->counter;
        head=head->next;
        break;
    }
    
    
    
}
}

//第二、第三关
else{
robot:
    while(head!=NULL)
    {

         initializer(conducted_instruction+1);//初始化或继承
    //inbox部分
    if(0==strcmp("inbox",head->ordername))//else if里千万不能混有if！！！
    {
    {
        
    if(firstnumleft==NULL)
    {
        break;
    }
   else
   {
  
    hand=firstnumleft->number;
    firstnumleft=firstnumleft->next;
    }
    
    }


    conducted_instruction++;
    levelstatus[conducted_instruction].theorderoforder=head->counter;
    head=head->next;
    already_inboxed++;
    levelstatus[conducted_instruction].alreadyinbox=already_inboxed;
    levelstatus[conducted_instruction].holdingblock=hand;
    levelstatus[conducted_instruction].order_name="inbox";
    if(firstnumleft!=NULL)//如果把if替换成while，必须加break，但是没有什么必要
    {

        if(already_inboxed!=levelsaves[levelnumber].inputn)
        {
            for(int i=0;i<levelsaves[levelnumber].inputn-already_inboxed;i++)
        {
            levelstatus[conducted_instruction].inputsave[i]=levelsaves[levelnumber].inputsave[already_inboxed+i];//这里存下尚且还在传送带上的方块为inputsave（从0开始计数）
            
        }
        }
    
    }
    }

//outbox部分
    else if(0==strcmp("outbox",head->ordername))
    {
        
    // head=head->next;
    if(hand!=-2147483648&&firstnumright!=NULL)//解决无限输出的问题
    {
    cout<<hand<<endl;
    outputnum++;//输出一次就加一
    firstnumright->number=hand;
    firstnumright=firstnumright->next;
    }
    else if (hand==-2147483648||firstnumright==NULL)
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
    }
    hand=-2147483648;
    conducted_instruction++;
    levelstatus[conducted_instruction].theorderoforder=head->counter;
    head=head->next;
    already_outboxed++;
    levelstatus[conducted_instruction].alreadyoutbox=already_outboxed;
    levelstatus[conducted_instruction].holdingblock=hand;//存下手中数字

        levelstatus[conducted_instruction].outputsave[already_outboxed]=hand;
    
    //存下已经输出的东西
   levelstatus[conducted_instruction].order_name="outbox";
    }



//add 部分
    else if(0==strcmp("add",head->ordername))
    {
    
    if (head->executenumber>levelsaves[levelnumber].validfloor||levelsaves[levelnumber].validfloor==-2147483648||hand==-2147483648)
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
    }
    else
    {
        conducted_instruction++;
        hand=hand+levelstatus[conducted_instruction].floor[head->counter];
        levelstatus[conducted_instruction].holdingblock=hand;
    }
    
    levelstatus[conducted_instruction].theorderoforder=head->counter;
     head=head->next;
    levelstatus[conducted_instruction].order_name="add";
    }//floor_num把levelnumber对应到floor数字

//sub部分
    else if(0==strcmp("sub",head->ordername))
    {
    
    if (head->executenumber>levelsaves[levelnumber].validfloor||levelsaves[levelnumber].validfloor==-2147483648||hand==-2147483648)
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
    }
    else
    {
        conducted_instruction++;
        hand=hand-levelstatus[conducted_instruction].floor[head->counter];
        levelstatus[conducted_instruction].holdingblock=hand;
    }
    levelstatus[conducted_instruction].theorderoforder=head->counter;
    head=head->next;
    levelstatus[conducted_instruction].order_name="sub";
    }



//copyto部分
    else if(0==strcmp("copyto",head->ordername))
    {
        
        if (head->executenumber>levelsaves[levelnumber].validfloor||hand==-2147483648)
        {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
        }
        else
        {
           conducted_instruction++;
            levelstatus[conducted_instruction].floor[head->executenumber]=hand;
        }
       
        levelstatus[conducted_instruction].executenumber_save=head->executenumber;
        levelstatus[conducted_instruction].theorderoforder=head->counter;
        head=head->next;
        
        levelstatus[conducted_instruction].order_name="copyto";
         
    }


//copyfrom部分
    else if(0==strcmp("copyfrom",head->ordername))
    {
        
        if (head->executenumber>levelsaves[levelnumber].validfloor||floor_base[head->executenumber]==-2147483648)
        {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
        }
        else
        {
            conducted_instruction++;
            hand=levelstatus[conducted_instruction].floor[head->counter];
            levelstatus[conducted_instruction].holdingblock=hand;
        }
       levelstatus[conducted_instruction].executenumber_save=head->executenumber;
    levelstatus[conducted_instruction].theorderoforder=head->counter;
        head=head->next;
        levelstatus[conducted_instruction].order_name="copyfrom";
    }



//jump部分
    else if(0==strcmp("jump",head->ordername))
    {
    
    while(headoforder!=NULL&&conducted_instruction<1000)
    {
        if(headoforder->counter==head->executenumber)
        {
            head=headoforder;
            break;
        }
        else
        {
            headoforder=headoforder->next;
        }
    }
    if (headoforder==NULL||conducted_instruction>=1000)
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
    }
    headoforder=temporary;
    conducted_instruction++;
        goto robot;
    } 

    //jumpifzero部分
    else if(0==strcmp("jumpifzero",head->ordername))
    {
        if(hand==0)
    {
        while(headoforder!=NULL&&conducted_instruction<1000)
    {
        if(headoforder->counter==head->executenumber)
        {
            head=headoforder;
            break;
        }
        
        else
        {
            headoforder=headoforder->next;
        }
    }
    if (headoforder==NULL||conducted_instruction>=1000||hand==-2147483648)
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=1000+head->counter;
        break;
    }
    }
  
    headoforder=temporary;
    conducted_instruction++;
        goto robot;
    }






//非法输入部分
    else
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=head->counter;
        break;
        head=head->next;
    }
}
}
}





int comparision(int levelnumber)//结果比较器
{
 int m=0;
    initialright=stationary;
    while(initialright!=NULL)
        {for(int i=0;i<output_all(levelnumber);i++)
        {
            if(initialright->number!=output[i])
            {
                m++;
            }
            initialright=initialright->next;
        }
   initialright=stationary;
    if(m==0)
    {
        cout<<"Success"<<endl<<endl;
        return 1;
    }
    else{
        cout<<"Fail"<<endl<<endl;
        return 0;
    }
}
}










void levelinfo(int levelnumber)//关卡信息！！！！！！！！
{
        cout<<"Present Blocks:"<<' ';
        for(int i=0;i<output_all(levelnumber);i++)
        {
            cout<<levelsaves[levelnumber].inputsave[i]<<' ';
        }
        cout<<endl;
        cout<<"The Valid Floor You Got:"<<' ';
        cout<<levelsaves[levelnumber].validfloor<<endl;//
        cout<<"instructions available:"<<' ';
        if(levelnumber==1)
        {
            
            cout<<"inbox"<<' '<<"outbox"<<endl;
        }
        else
        {
            cout<<"inbox"<<' '<<"outbox"<<' '<<"add"<<' '<<"sub"<<' '<<"copyto"<<' '<<"copyfrom"<<' '<<"jump"<<' '<<"jumpifzero"<<endl;
        }
        cout<<"You Are Expected To Output:"<<' ';
        for(int i=0;i<output_all(levelnumber);i++)
        {
            cout<<levelsaves[levelnumber].outputsave[i]<<' ';
        }
        cout<<endl<<"in the given order as above"<<endl;

    }




void prepare(int levelnumber)//关卡准备器

{
    
    levelinfo(levelnumber);
    for(int i=0;i<levelsaves[levelnumber].validfloor;i++)
    {
        levelstatus[levelnumber].floor[i]=-2147483648;
    }
}


void save(int levelnumber)//关卡储存器
{

    levelsaves[levelnumber].outputn=0;

    if(initialright!=NULL)//总是要加这个while判定代码才可以反复运行
        {for(int i=0;i<outputnum;i++)
        {
        levelsaves[levelnumber].outputsave[i]=initialright->number;
        initialright=initialright->next;
        levelsaves[levelnumber].outputn++;
        }
        }
    initialright=stationary;

}

int level(int levelnumber,int ordernumber)//关卡执行器

{
    
    left(levelnumber);
    right(levelnumber);
    robot(create(ordernumber),levelnumber);
    int m = comparision(levelnumber);
    save(levelnumber);//出问题了
    cout<<"The Robot Has Done The Instructions For"<<' '<<conducted_instruction<<' '<<"Times"<<endl<<" AND ITS SO DAMN TIRED OF YOUR MANIPULATION!!!"<<endl<<endl<<endl;
    cout<<endl;
    return m;
}



int main()
{
int p;
for(int i=0;i<3;i++)
{


    cout<<"Welcome To Level"<<' '<<i+1<<endl;
    prepare(i+1);//准备关卡
    // int check=violent_input_check(); 



// if(!check)
// {
//     cout<<"Wrong Order Number!!!"<<endl;
// }
// else{
    // cout<<"GOOD!"<<endl;
    p = level(i+1,ordernumber);
// }



if(p==1)
{
    conducted_instruction=0;
    outcome=0;//成功了
    continue;
}
else
{
    i-=1;
outcome=-1;//失败了
}
}
  //用数组或者结构体储存关卡信息

} 