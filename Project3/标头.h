#pragma once

#ifndef BANKALGORITHM_H
#define BANKALGORITHM_H

int const processNum = 5;
int const resourceNum = 3;

class bankAlgorithm {
public:
	bankAlgorithm();//���캯��
	void sendRequest();	//��Դ���뺯��
	bool safetyCheck();	//��ȫ��麯��
	void disp();
private:

	int available[resourceNum] = { 3,3,2 };	//��������Դ����
	int max[processNum][resourceNum] = { {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };	//����������
	int allocation[processNum][resourceNum] = { {0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2} };	//�������
	int need[processNum][resourceNum] = { {7,4,3},{1,2,2},{6,0,0},{0,1,1},{4,3,1} };	//�������
	int request[resourceNum + 1] = { 0 };	//��������
	int work[resourceNum] = { 0 };	//��������
	bool finish[processNum] = { false };	//�Ƿ���ɲ�������
	int show[resourceNum * 4] = { 0 };	//	�������������

};
#endif // !BANKALGORITHM_H







