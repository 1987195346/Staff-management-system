#pragma once   //��ֹͷ�ļ��ظ�����
#include <iostream>
#include <string>  
#include "worker.h"
using namespace std;

//************************************************************************//
//��ͨԱ��ͷ�ļ�
//��ͨԱ����̳�ְ�������࣬����д�����д��麯��
//************************************************************************//

class Employee :public Worker {
public:
	//���캯��
	Employee(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡ��λ����
	virtual string getDeptName();
};