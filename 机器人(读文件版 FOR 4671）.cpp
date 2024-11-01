#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

//����һЩ����
int hand=-2147483648;//���������еĻ�ľ
int t;//�������ָ������Ϊ������ʱ��t��ʾ���ָ������
int conducted_instruction;//�ܹ�ִ�е�ָ�����
int outputnum;//�������ܹ�����Ĵ�������
int outcome;//��������ʾ�� 0�ɹ� -1ʧ�� 
int ordernumber;// �������ָ���������Ӧ����һ�������ҳ�
char code[1000][19];//������������ָ��
int already_inboxed,already_outboxed;

struct levelsave//level 1 2 3�ȹؿ���Ϣ�Ĵ���
{
char name[40],instruction[300];//�ؿ����ƺ͹ؿ�˵��
int inputn,inputsave[100],outputn,outputsave[100],validfloor,allowedcommands[8];//�ؿ���ľ�������ؿ����л�ľ���ؿ������ľ�������������ʱ�ؿ����������ľ
int commandlimit,steplimit;//�ɾ�ϵͳ
}levelsaves[100];


struct level_status//������ÿһ������Ϣ�ļ�ʱ���棬������������
{
int inputsave[100],outputsave[100],holdingblock=-2147483648,floor[25];//��һ����ʣ�µĻ�ľ��Ϣ����һ��������Ļ�ľ����Ϣ����һ�����еĻ�ľ��Ϣ����һ����ռ�õĿյ���Ϣ
string order_name;//��һ��ִ�е�ָ������
int executenumber_save;//����û���������������������洢������վ����һ���յ��ϣ���copyto��copyfrom��p->executenumber��
int theorderoforder;//�����Դ�һ��ÿһ��ָ���ڵڼ���
int alreadyinbox,alreadyoutbox;
}levelstatus[9999];







//ָ�����벿��
struct order//����һ��order�ṹ
{
    char ordername[20];
    int executenumber;
    int counter;
    order *next;
};

order *head;
order *headoforder;
order *temporary;

order *create(int order_number)//����һ���������������ָ�������
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
            p->ordername[m]=code[i+1][m];//���û���������ԭԭ�����ش��͵�code������(��code��1����ָ��ȡ���ʼ)
        }
        p->counter=i+1;
        if(code[i+1][1]=='a'&&code[i+1][2]=='d'&&code[i+1][3]=='d')
        {
            int m=0;
            int q=100;
            for(int t=5;t<8;t++)
            {
                if(code[i+1][t]>=48&&code[i+1][t]<=57)// ���������ǲ�������
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





//�ؿ��Ļ�ľ����

int output[10];

int output1()//��һ�ص���������
{   
   
    output[0]=1;
    output[1]=2;
    return 2;//��������ľ
}
int output2()//�ڶ��ص���������
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
int output3()//�����ص���������
{
    
    output[0]=7;
    output[1]=-3;
    
    return 2;
}
int output4()//���Ĺص���������
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





//���ʹ�����
struct conveyerbelt//����һ����Ϊ�����ʹ����Ľṹ
{
    int number;
    conveyerbelt *next;
};

conveyerbelt *firstnumleft;
conveyerbelt *firstnumright;
conveyerbelt *initialleft;
conveyerbelt *initialright;
conveyerbelt *stationary;

conveyerbelt *left(int levelnumber)//������ߵĴ��ʹ�
{
    conveyerbelt *p=NULL;
    conveyerbelt *q=NULL;
    firstnumleft=NULL;
    initialleft=NULL;   
    for (int i=0;i<levelsaves[levelnumber].inputn;i++)//inputn��ͨ�����ļ���ʱ���Զ����ɵ��ܻ�ľ��
    {
    p = new conveyerbelt;
    p->number=levelsaves[levelnumber].inputsave[i];//�����ļ��е�����
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

conveyerbelt *right(int levelnumber)//�����ұߵĴ��ʹ�
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





//�ؿ��յز���
int floor_base[3]={-2147483648,-2147483648,-2147483648};

int floor_num(int levelnumber)//���ɶ�Ӧ�ؿ��յص���Ŀ
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



void robot(order *head,int levelnumber)//��ļ�����
{  
    already_outboxed=0;//�����������ľ��Ϊ0
    already_inboxed=0;//�����������ľ��Ϊ0
    outputnum=0;//�����������������Ϊ0
    conducted_instruction=0;
//��һ�� 
if(levelnumber==1)
{
    while(head!=NULL)
    {
        initializer(conducted_instruction+1);//��ʼ����̳�,������СΪ1
    //inbox����
    if(0==strcmp("inbox",head->ordername))//else if��ǧ���ܻ���if������
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
    if(firstnumleft!=NULL)//�����if�滻��while�������break������û��ʲô��Ҫ
    {

        if(already_inboxed!=levelsaves[levelnumber].inputn)
        {
            for(int i=0;i<levelsaves[levelnumber].inputn-already_inboxed;i++)
        {
            levelstatus[conducted_instruction].inputsave[i]=levelsaves[levelnumber].inputsave[already_inboxed+i];//����������һ��ڴ��ʹ��ϵķ���Ϊinputsave����0��ʼ������
            
        }
        }
    
    }
    }

//outbox����
    else if(0==strcmp("outbox",head->ordername))
    {
        
    // head=head->next;
    if(hand!=-2147483648&&firstnumright!=NULL)//����������������
    {
    cout<<hand<<endl;
    outputnum++;//���һ�ξͼ�һ
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
    levelstatus[conducted_instruction].holdingblock=hand;//������������

        levelstatus[conducted_instruction].outputsave[already_outboxed]=hand;
    
    //�����Ѿ�����Ķ���
   levelstatus[conducted_instruction].order_name="outbox";
    }

//�Ƿ�����
    else
    {
        cout<<"Error on instruction"<<' '<<head->counter<<endl;
        outcome=head->counter;
        head=head->next;
        break;
    }
    
    
    
}
}

//�ڶ���������
else{
robot:
    while(head!=NULL)
    {

         initializer(conducted_instruction+1);//��ʼ����̳�
    //inbox����
    if(0==strcmp("inbox",head->ordername))//else if��ǧ���ܻ���if������
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
    if(firstnumleft!=NULL)//�����if�滻��while�������break������û��ʲô��Ҫ
    {

        if(already_inboxed!=levelsaves[levelnumber].inputn)
        {
            for(int i=0;i<levelsaves[levelnumber].inputn-already_inboxed;i++)
        {
            levelstatus[conducted_instruction].inputsave[i]=levelsaves[levelnumber].inputsave[already_inboxed+i];//����������һ��ڴ��ʹ��ϵķ���Ϊinputsave����0��ʼ������
            
        }
        }
    
    }
    }

//outbox����
    else if(0==strcmp("outbox",head->ordername))
    {
        
    // head=head->next;
    if(hand!=-2147483648&&firstnumright!=NULL)//����������������
    {
    cout<<hand<<endl;
    outputnum++;//���һ�ξͼ�һ
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
    levelstatus[conducted_instruction].holdingblock=hand;//������������

        levelstatus[conducted_instruction].outputsave[already_outboxed]=hand;
    
    //�����Ѿ�����Ķ���
   levelstatus[conducted_instruction].order_name="outbox";
    }



//add ����
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
    }//floor_num��levelnumber��Ӧ��floor����

//sub����
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



//copyto����
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


//copyfrom����
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



//jump����
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

    //jumpifzero����
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






//�Ƿ����벿��
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





int comparision(int levelnumber)//����Ƚ���
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










void levelinfo(int levelnumber)//�ؿ���Ϣ����������������
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




void prepare(int levelnumber)//�ؿ�׼����

{
    
    levelinfo(levelnumber);
    for(int i=0;i<levelsaves[levelnumber].validfloor;i++)
    {
        levelstatus[levelnumber].floor[i]=-2147483648;
    }
}


void save(int levelnumber)//�ؿ�������
{

    levelsaves[levelnumber].outputn=0;

    if(initialright!=NULL)//����Ҫ�����while�ж�����ſ��Է�������
        {for(int i=0;i<outputnum;i++)
        {
        levelsaves[levelnumber].outputsave[i]=initialright->number;
        initialright=initialright->next;
        levelsaves[levelnumber].outputn++;
        }
        }
    initialright=stationary;

}

int level(int levelnumber,int ordernumber)//�ؿ�ִ����

{
    
    left(levelnumber);
    right(levelnumber);
    robot(create(ordernumber),levelnumber);
    int m = comparision(levelnumber);
    save(levelnumber);//��������
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
    prepare(i+1);//׼���ؿ�
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
    outcome=0;//�ɹ���
    continue;
}
else
{
    i-=1;
outcome=-1;//ʧ����
}
}
  //��������߽ṹ�崢��ؿ���Ϣ

} 