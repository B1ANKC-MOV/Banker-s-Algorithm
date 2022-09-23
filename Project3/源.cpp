#include <iostream>
#include<iomanip>
#include <malloc.h> 
#include <stdio.h> 
#include <string.h> 
#include <windows.h>
#include <iomanip>
using namespace std;
//ȫ�ֱ��� Type_num�����м�����Դ��Process_num���������
#define Type_num 3 
#define Process_num 5
//��Դ���������
int Process[Type_num];//���ÿ���������ݵ�����
int Max[Process_num][Type_num];//ÿ����������ÿ����Դ�������
int Allocation[Process_num][Type_num];//ÿ�������ѷ������Դ��Ŀ
//ϵͳ״̬������
int Need[Process_num][Type_num];//Ŀǰ����������Ҫ�ĸ�����Դ����Ŀ
int Available[Type_num];//Ŀǰ������Դ�Ŀ�����Ŀ
//��ȫ���в�����
int Work[Type_num];//��ǰ�ͷŵĸ�����Դ��Ŀ
int Finish[Process_num];//�����̵����״̬
//��Ű�ȫ���е��±����� :
int SafeList[Process_num];

void Init()//��ʼ������
{
    cout << "----------------------------���м��㷨------------------------------" << endl;
    cout << "[���̳�ʼ��]������" << Type_num << "����Դ���Ե�������:";
    int i, j;
    for (i = 0; i < Type_num; i++){
        cin >> Process[i];
        Available[i] = Process[i];
    }
    cout << endl;

    cout << "[���̳�ʼ��]������" << Process_num << "�����̸��Զ�" << Type_num << "����Դ������������Max��:"<<endl;
    for (i = 0; i < Process_num; i++) {
        for (j = 0; j < Type_num; j++) {
            cin >> Max[i][j];
        }
    }
    cout << endl;

    cout << "[���̳�ʼ��]������" << Process_num << "�����̸��Ի�õ�" << Type_num << "����Դ��������Allocation��:"<<endl;
    for (i = 0; i < Process_num; i++) {
        for (j = 0; j < Type_num; j++) {
            cin >> Allocation[i][j];
        }
    }
    cout << "-------------------------[���̳�ʼ�����]---------------------------" << endl;
   

    for (i = 0; i < Process_num; i++) {
        for (j = 0; j < Type_num; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
            //����ÿ����������ÿ����Դ���������Max����ÿ�������ѷ������Դ��Ŀ��Allocation�������Ŀǰ����������Ҫ�ĸ�����Դ����Ŀ��Need��
        }
    }
    for (i = 0; i < Type_num; i++)
        for (j = 0; j < Process_num; j++) {
            Available[i] = Available[i] - Allocation[j][i];
            //������֪�ĸ�����Դ���������͸������ѷ������Դ��Ŀ��Allocation�����Ŀǰ������Դ�Ŀ�����Ŀ��Available��
        }
}

void Display()
{
    cout << "                       Tʱ��ϵͳ��״̬��" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "|����        |                   ��Դ���                        |" << endl;
    cout << "|            |---------------------------------------------------|" << endl;
    cout << "|            |Max         |Allocation  |Need        |Available   |" << endl;
    cout << "|----------------------------------------------------------------|" << endl;
    int i;
    for (i = 0; i < Process_num; i++)
    {
        if (i == 0) {
            cout << "|P" << i << "          |" << setw(4) << setfill(' ') << Max[i][0] << setw(4) << setfill(' ') << Max[i][1] << setw(4) << setfill(' ') << Max[i][2];
            cout << "|" << setw(4) << setfill(' ') << Allocation[i][0] << setw(4) << setfill(' ') << Allocation[i][1] << setw(4) << setfill(' ') << Allocation[i][2];
            cout << "|" << setw(4) << setfill(' ') << Need[i][0] << setw(4) << setfill(' ') << Need[i][1] << setw(4) << setfill(' ') << Need[i][2];
            cout << "|" << setw(4) << setfill(' ') << Available[0] << setw(4) << setfill(' ') << Available[1] << setw(4) << setfill(' ') << Available[2];
            cout << "|" << endl;
        }
        else {
            cout << "|P" << i << "          |" << setw(4) << setfill(' ') << Max[i][0] << setw(4) << setfill(' ') << Max[i][1] << setw(4) << setfill(' ') << Max[i][2];
            cout << "|" << setw(4) << setfill(' ') << Allocation[i][0] << setw(4) << setfill(' ') << Allocation[i][1] << setw(4) << setfill(' ') << Allocation[i][2];
            cout << "|" << setw(4) << setfill(' ') << Need[i][0] << setw(4) << setfill(' ') << Need[i][1] << setw(4) << setfill(' ') << Need[i][2];
            cout << "|            |" << endl;          
        }
    }
    cout << "------------------------------------------------------------------" << endl;
}

int Bool_Finish() 
{
    int i, j, count;
    for (i = 0; i < Process_num; i++)//���̴��ϣ�0�����£�Process_num)����
    {
        for (j = 0, count = 0; j < Type_num; j++)
            if (Finish[i] == 0 && Need[i][j] <= Work[j])//����˽���״̬δ��ɣ��ҵ�ǰ�ͷŵĴ�����Դ��Ŀ������˽��̵�ǰ����
                count++;

        if (count == Type_num)//��������Դ��Ŀ������������;ps��Type_num=3
        {
            for (j = 0; j < Type_num; j++)
                Work[j] += Allocation[i][j];//����i�������ѷ�����˽��̵ĸ�����Դ�ͷ�

            Finish[i] = 1;//��ǽ���״̬����
            return i;//���ؽ���ID
        }
    }
    return -1;//����ǰ�޽�����ɣ��򷵻�-1
}

int Bool_Safe()
{
    int i, s, count = 0;
    for (i = 0; i < Type_num; i++)
        Work[i] = Available[i];//��ʼʱ����ǰ�ͷ���Դ���ڵ�ǰ������Դ
    for (i = 0; i < Process_num; i++)
        Finish[i] = 0;//�տ�ʼ�������״̬��Ϊ0��δ��ɣ�
    for (i = 0; i < Process_num; i++)
    {
        s = Bool_Finish();
        if (s != -1)//����������ɽ���sʱ����¼��ID
        {
            SafeList[i] = s;
            count++;
        }
    }//�Ѱ�ȫ���е��±꡾s�����밲ȫ�������顾SafeList���� 
    if (count == Process_num)//���ȫ�����̶�����ɣ�����ǰ״̬Ϊ��ȫ״̬��;ps��Process_num=5
        return 1;//����True
    else
        return 0;
}

void Display_SafeList()
{
    int i, j;
    cout << "                       Tʱ�̵İ�ȫ���б�" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "|����        |                   ��Դ���                           |Finish      |" << endl;
    cout << "|            |------------------------------------------------------|            |" << endl;
    cout << "|            |Work        |Max         |Allocation  |Work+Allocation|            |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (j = 0; j < Type_num; j++)
    {
        Work[j] = Available[j];
    }
    for (i = 0; i < Process_num; i++)
    {
        cout << "|P" << SafeList[i] << "          |" << setw(4) << setfill(' ')<< Work[0] << setw(4) << setfill(' ') << Work[1] << setw(4) << setfill(' ') << Work[2];
        cout << "|" << setw(4) << setfill(' ')<< Need[SafeList[i]][0] << setw(4) << setfill(' ') << Need[SafeList[i]][1] << setw(4) << setfill(' ') << Need[SafeList[i]][2];
        cout << "|" << setw(4) << setfill(' ')<<Allocation[SafeList[i]][0] << setw(4) << setfill(' ') << Allocation[SafeList[i]][1] << setw(4) << setfill(' ') << Allocation[SafeList[i]][2];
        cout << "|" << setw(4) << setfill(' ')<<Work[0] + Allocation[SafeList[i]][0] << setw(4) << setfill(' ') << Work[1] + Allocation[SafeList[i]][1] << setw(4) << setfill(' ') << Work[2] + Allocation[SafeList[i]][2];
        cout << "   |True        |" << endl;
    
        for (j = 0; j < Type_num; j++)
            Work[j] += Allocation[SafeList[i]][j];
    }
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "[���]��ǰ��ȫ����Ϊ��";
    for (i = 0; i< Process_num; i++)
    {
        cout << " P" << SafeList[i];
    }
    cout << endl;
}

void Request(int i, int Request[Type_num])//IDΪi�Ľ��̶���Դ��������
{//�����������ϵͳ���ܹ�������Դ����Ҫ������������������
//��Request[j]��Need[i][j]
//��Request[j]��Available[j]
//��Ԥ����:
//   Available[j] = Available[j] - Request[j];
//   Allocation[i][j] = Allocation[i][j] + Request[j];
//   Need[i][j] = Need[i][j] - Request[j];
//   ����ж��Ƿ��ڰ�ȫ״̬�����ɹ���ϵͳ���ɷ�����Դ
    int  require1, require2, j;

    for (j = 0, require1 = 0; j < Type_num; j++) {
        if (Request[j] <= Need[i][j])//�ж�������
            require1++;
    }

    for (j = 0, require2 = 0; j < Type_num; j++) {
        if (Request[j] <= Available[j])//�ж�������
            require2++;
    }

    if (require2 != Type_num)//�������ڲ����㣬��˵����Դ����
        cout << endl << "[����]��Դ����;[ԭ��]����" << i << "������" << endl;
 
    if (require2 == Type_num && require1 == Type_num){//�ж�������
        for (j = 0; j < Type_num; j++){
            Available[j] = Available[j] - Request[j];
            Allocation[i][j] = Allocation[i][j] + Request[j];
            Need[i][j] = Need[i][j] - Request[j];
        }
        if (Bool_Safe() == 0){
            cout << endl << "[����]������û�д��ڰ�ȫ״̬;[ԭ��]�����ڰ�ȫ���С�" << endl;
            for (j = 0; j < Type_num; j++){//�ָ�����
                Available[j] = Available[j] + Request[j];
                Allocation[i][j] = Allocation[i][j] - Request[j];
                Need[i][j] = Need[i][j] + Request[j];
            }
        }else{
            cout << endl<< "[�ɹ�]���ڰ�ȫ���У��ɹ�������Դ��" << endl;
            Display_SafeList();
        }
    }
}
void main()
{
    int Request_ProcessID = -1, request[Type_num],j;
    Init();
    Display();
    if (Bool_Safe() == 0){
        cout << "[����]���̴��ڷǰ�ȫ״̬��" << endl;
    }else{
        cout << "���̴��ڰ�ȫ״̬��" << endl;
        Display_SafeList();
        cout << "----------------------------��Request������----------------------------------";
        cout <<endl<< "�������������Request���Ľ���ID:";
        cin >> Request_ProcessID;
        while (Request_ProcessID >= 0 && Request_ProcessID < Process_num){
            cout << "���������������Request��:";
            for (j = 0; j < Type_num; j++){cin >> request[j];}
            cout << "----------------------------��Request�����----------------------------------";
            Request(Request_ProcessID, request);
            Display();
            cout << "----------------------------��Request������----------------------------------";
            cout << endl << "�������������Request���Ľ���ID:";
            cin >> Request_ProcessID;
        }
    }
}
