#include <iostream>
#include<iomanip>
#include <malloc.h> 
#include <stdio.h> 
#include <string.h> 
#include <windows.h>
#include <iomanip>
using namespace std;
//全局变量 Type_num代表有几类资源，Process_num代表进程数
#define Type_num 3 
#define Process_num 5
//资源分配参数：
int Process[Type_num];//存放每个进程数据的数组
int Max[Process_num][Type_num];//每个进程所需每种资源的最大数
int Allocation[Process_num][Type_num];//每个进程已分配的资源数目
//系统状态参数：
int Need[Process_num][Type_num];//目前各个进程需要的各种资源的数目
int Available[Type_num];//目前各类资源的可用数目
//安全序列参数：
int Work[Type_num];//当前释放的各种资源数目
int Finish[Process_num];//各进程的完成状态
//存放安全序列的下标序列 :
int SafeList[Process_num];

void Init()//初始化进程
{
    cout << "----------------------------银行家算法------------------------------" << endl;
    cout << "[进程初始化]请输入" << Type_num << "种资源各自的总数量:";
    int i, j;
    for (i = 0; i < Type_num; i++){
        cin >> Process[i];
        Available[i] = Process[i];
    }
    cout << endl;

    cout << "[进程初始化]请输入" << Process_num << "个进程各自对" << Type_num << "种资源的总需求量【Max】:"<<endl;
    for (i = 0; i < Process_num; i++) {
        for (j = 0; j < Type_num; j++) {
            cin >> Max[i][j];
        }
    }
    cout << endl;

    cout << "[进程初始化]请输入" << Process_num << "个进程各自获得的" << Type_num << "种资源的数量【Allocation】:"<<endl;
    for (i = 0; i < Process_num; i++) {
        for (j = 0; j < Type_num; j++) {
            cin >> Allocation[i][j];
        }
    }
    cout << "-------------------------[进程初始化完毕]---------------------------" << endl;
   

    for (i = 0; i < Process_num; i++) {
        for (j = 0; j < Type_num; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
            //根据每个进程所需每种资源的最大数【Max】和每个进程已分配的资源数目【Allocation】计算出目前各个进程需要的各种资源的数目【Need】
        }
    }
    for (i = 0; i < Type_num; i++)
        for (j = 0; j < Process_num; j++) {
            Available[i] = Available[i] - Allocation[j][i];
            //根据已知的各种资源的总数量和各进程已分配的资源数目【Allocation】算出目前各类资源的可用数目【Available】
        }
}

void Display()
{
    cout << "                       T时刻系统的状态表" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "|进程        |                   资源情况                        |" << endl;
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
    for (i = 0; i < Process_num; i++)//进程从上（0）往下（Process_num)遍历
    {
        for (j = 0, count = 0; j < Type_num; j++)
            if (Finish[i] == 0 && Need[i][j] <= Work[j])//如果此进程状态未完成，且当前释放的此种资源数目能满足此进程当前所需
                count++;

        if (count == Type_num)//若三种资源数目都能满足所需;ps：Type_num=3
        {
            for (j = 0; j < Type_num; j++)
                Work[j] += Allocation[i][j];//进程i结束，已分配给此进程的各种资源释放

            Finish[i] = 1;//标记进程状态结束
            return i;//返回进程ID
        }
    }
    return -1;//若当前无进程完成，则返回-1
}

int Bool_Safe()
{
    int i, s, count = 0;
    for (i = 0; i < Type_num; i++)
        Work[i] = Available[i];//初始时，当前释放资源等于当前可用资源
    for (i = 0; i < Process_num; i++)
        Finish[i] = 0;//刚开始进程完成状态都为0（未完成）
    for (i = 0; i < Process_num; i++)
    {
        s = Bool_Finish();
        if (s != -1)//当出现已完成进程s时，记录下ID
        {
            SafeList[i] = s;
            count++;
        }
    }//把安全序列的下标【s】放入安全序列数组【SafeList】。 
    if (count == Process_num)//如果全部进程都已完成（即当前状态为安全状态）;ps：Process_num=5
        return 1;//返回True
    else
        return 0;
}

void Display_SafeList()
{
    int i, j;
    cout << "                       T时刻的安全序列表" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "|进程        |                   资源情况                           |Finish      |" << endl;
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
    cout << "[完成]当前安全序列为：";
    for (i = 0; i< Process_num; i++)
    {
        cout << " P" << SafeList[i];
    }
    cout << endl;
}

void Request(int i, int Request[Type_num])//ID为i的进程对资源进行请求
{//进程提出请求，系统若能够分配资源，需要满足以下三个条件：
//①Request[j]≤Need[i][j]
//②Request[j]≤Available[j]
//③预分配:
//   Available[j] = Available[j] - Request[j];
//   Allocation[i][j] = Allocation[i][j] + Request[j];
//   Need[i][j] = Need[i][j] - Request[j];
//   随后判断是否处于安全状态，若成功，系统方可分配资源
    int  require1, require2, j;

    for (j = 0, require1 = 0; j < Type_num; j++) {
        if (Request[j] <= Need[i][j])//判断条件①
            require1++;
    }

    for (j = 0, require2 = 0; j < Type_num; j++) {
        if (Request[j] <= Available[j])//判断条件②
            require2++;
    }

    if (require2 != Type_num)//若条件②不满足，则说明资源不足
        cout << endl << "[报错]资源不足;[原因]进程" << i << "堵塞！" << endl;
 
    if (require2 == Type_num && require1 == Type_num){//判断条件③
        for (j = 0; j < Type_num; j++){
            Available[j] = Available[j] - Request[j];
            Allocation[i][j] = Allocation[i][j] + Request[j];
            Need[i][j] = Need[i][j] - Request[j];
        }
        if (Bool_Safe() == 0){
            cout << endl << "[报错]本进程没有处于安全状态;[原因]不存在安全序列。" << endl;
            for (j = 0; j < Type_num; j++){//恢复数据
                Available[j] = Available[j] + Request[j];
                Allocation[i][j] = Allocation[i][j] - Request[j];
                Need[i][j] = Need[i][j] + Request[j];
            }
        }else{
            cout << endl<< "[成功]存在安全序列，成功分配资源！" << endl;
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
        cout << "[警告]进程处于非安全状态！" << endl;
    }else{
        cout << "进程处于安全状态。" << endl;
        Display_SafeList();
        cout << "----------------------------【Request】输入----------------------------------";
        cout <<endl<< "请输入提出请求【Request】的进程ID:";
        cin >> Request_ProcessID;
        while (Request_ProcessID >= 0 && Request_ProcessID < Process_num){
            cout << "请输入提出的请求【Request】:";
            for (j = 0; j < Type_num; j++){cin >> request[j];}
            cout << "----------------------------【Request】结果----------------------------------";
            Request(Request_ProcessID, request);
            Display();
            cout << "----------------------------【Request】输入----------------------------------";
            cout << endl << "请输入提出请求【Request】的进程ID:";
            cin >> Request_ProcessID;
        }
    }
}
