#pragma once   //防止头文件重复包含
#include "headline.h"
//************************************************************************//
//管理类负责的内容如下：
//1.与用户的沟通菜单界面
//2.对职工增删改查的操作
//3.与文件的读写交互
//************************************************************************//

class WorkerManager{
public:
	//构造函数
	WorkerManager();
	
	//展示菜单
	void Show_Menu();

	//退出功能
	void ExitSystem();

	//添加职工
	void Add_Emp();

	//析构函数
	~WorkerManager();

	//保存文件
	void save();

	//标志文件是否为空
	bool m_FileIsEmpty;

	//统计人数
	int get_EmpNum();
	
	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//排序职工
	void Sort_Emp();
	
	//清空文件
	void Clean_File();

	//按照职工编号判断职工是否存在，若存在返回职工在数组中位置，不在返回-1
	int IsExist(int id);

	//记录职工人数
	int m_EmpNum;
	//员工数组的指针
	Worker ** m_EmpArray;
};