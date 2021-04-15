#pragma once   //防止头文件重复包含
#include <iostream>
#include <string>  
#include "worker.h"
using namespace std;
class Manager :public Worker {
public:
	//构造函数
	Manager(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();
};