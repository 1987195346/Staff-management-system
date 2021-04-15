#pragma once   //防止头文件重复包含
#include <iostream>
#include <string>  
#include <fstream>
#include "worker.h"
using namespace std;
class Boss :public Worker {
public:
	//构造函数
	Boss(int id, string name, int dId);

	//显示个人信息
	virtual void showInfo();

	//获取岗位名称
	virtual string getDeptName();
};