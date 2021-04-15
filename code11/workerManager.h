#pragma once   //��ֹͷ�ļ��ظ�����
#include "headline.h"
//************************************************************************//
//�����ฺ����������£�
//1.���û��Ĺ�ͨ�˵�����
//2.��ְ����ɾ�Ĳ�Ĳ���
//3.���ļ��Ķ�д����
//************************************************************************//

class WorkerManager{
public:
	//���캯��
	WorkerManager();
	
	//չʾ�˵�
	void Show_Menu();

	//�˳�����
	void ExitSystem();

	//���ְ��
	void Add_Emp();

	//��������
	~WorkerManager();

	//�����ļ�
	void save();

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ������
	int get_EmpNum();
	
	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();
	
	//����ļ�
	void Clean_File();

	//����ְ������ж�ְ���Ƿ���ڣ������ڷ���ְ����������λ�ã����ڷ���-1
	int IsExist(int id);

	//��¼ְ������
	int m_EmpNum;
	//Ա�������ָ��
	Worker ** m_EmpArray;
};