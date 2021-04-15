#pragma once   //防止头文件重复包含
#include <iostream>
#include <string>  
#include "worker.h"
using namespace std;

//************************************************************************//
//普通员工头文件
//普通员工类继承职工抽象类，并重写父类中纯虚函数
//************************************************************************//

class Employee :public Worker {
public:
	//构造函数
	Employee(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();
};