#pragma once   //防止头文件重复包含
#include <iostream>
#include <string>  
using namespace std;
#include "worker.h"          //职工类 
#include "employee.h"        //普通员工类
#include "manager.h"         //经理类
#include "boss.h"            //老板类

#include "workerManager.h"   //管理类

//头文件引用一般遇到自己的头文件就不会再往下引用了
//比如经理类遇到manager.h就不会再引用boss.h
//把using namespace std;写在所有类的头文件前面就不会出错了，这样每个头文件都能引用到标准库