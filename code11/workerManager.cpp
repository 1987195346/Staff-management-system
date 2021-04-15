#pragma once
#include "headline.h"
WorkerManager::WorkerManager() {
	//读文件
	//1.文件不存在
	ifstream ifs;
	ifs.open("empFile.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "文件不存在" << endl;  //测试输出
		this->m_EmpNum = 0;//初始化人数
		this->m_FileIsEmpty = true;//初始化文件为空
		this->m_EmpArray = NULL;//初始化数组
		ifs.close();//关闭文件
		return;
	}

	//2.文件存在，但是数据被用户清空
	char ch;
	//读一个字符
	ifs >> ch;
	//eof()函数判断文件是否为空，如果为空，返回true
	if (ifs.eof()) {
		cout << "文件为空!" << endl;
		this->m_EmpNum = 0;//初始化人数
		this->m_FileIsEmpty = true;//初始化文件为空
		this->m_EmpArray = NULL;//初始化数组
		ifs.close();//关闭文件
		return;
	}

	//3.文件存在，并且保存职工的所有数据
	int num = this->get_EmpNum();
//	cout << "职工个数为：" << num << endl; //测试代码
	this->m_EmpNum = num;//更新成员属性
	
	//根据职工数创建数组
	this->m_EmpArray = new Worker *[this->m_EmpNum];
	//初始化职工
	init_Emp();

	////测试代码
	//for (int i = 0; i < m_EmpNum; i++) {
	//	cout << "职工号：" << this->m_EmpArray[i]->m_Id
	//		<< "职工姓名：" << this->m_EmpArray[i]->m_Name
	//		<< "岗位：" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}

//释放m_EmpArray堆区数据
WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

//展示菜单
void WorkerManager::Show_Menu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出功能
void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
};

//添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量:";
	int addNum = 0;  //保存用户的输入数量
	cin >> addNum;

	if (addNum > 0) {

		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间大小=原来记录人数+新增人数


		
		//开辟新空间       
		//每个数据都是Worker*类型，用Worker**接受，相当于把员工指针放到一个数组中（因为要将所有  不同种类  的员工都放入到一个数组中）
		Worker ** newSpace = new Worker*[newSize];   //将所有员工的指针维护到一个数组里

		//将原来空间下的数据拷贝到新空间下
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++) {

			int id;  //职工编号
			string name; //职工姓名
			int dSelect; //职工岗位

			cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
			cin >> name;

			cout << "请选择改职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;  //职工指针

			switch (dSelect) {
			case 1:  //普通员工
				worker = new Employee(id, name, 1);
				break;
			case 2:  //经理
				worker = new Manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工指针worker  保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		//成功添加后保存到文件中
		this->save();

		//提示信息
		cout << "成功添加" << addNum << "名新员工！" << endl;
	}
	else {
		cout << "输入数据有误!" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save() {
	ofstream ofs;
	ofs.open("empFile.txt", ios::out);
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//统计人数
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open("empFile.txt", ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	//读一行数据，读到空格自动结束
	while (ifs >> id && ifs >> name && ifs >> dId) {
		//记录人数
		num++;
	}
	ifs.close();
	return num;
}

//初始化员工
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open("empFile.txt", ios::in);
	
	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker *worker = NULL;

		//根据不同的部门id创建不同对象
		//1.普通员工
		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		//2.经理
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		//3.老板
		else{
			worker = new Boss(id, name, dId);
		}

		//存放在数组中
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}

//显示职工
void WorkerManager::Show_Emp() {
	//判断是否为空
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}


//按照职工编号判断职工是否存在，若存在返回职工在数组中位置，不在返回-1
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}

//删除职工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空！" << endl;
	}
	else {
		//按职工编号删除
		cout << "请输入想要删除的职工号：";
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		//职工存在
		if (index != -1) {
			for (int i = index; i < this->m_EmpNum - 1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i + 1]; 
			}
			this->m_EmpNum--;
			this->save();//删除后数据同步到文件中
			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到该职工" << endl;
		}
		system("pause");
		system("cls");
	}
}

//修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空" << endl;
	}
	else {
		cout << "请输入修改职工的编号：" << endl;

		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			//查找到编号的职工
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = " ";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;
			cout << "请输入岗位：" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "1.老板" << endl;
			cin >> dSelect;
			Worker * worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更改数据 到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else {
			cout << "修改失败，查无此人" << endl;
		}
	}
	
	//按任意键 清屏
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按姓名查找" << endl;
		int select = 0;
		cin >> select;

		//按职工编号查找
		if (select == 1) {
			int id;
			cout << "请输入查找的职工编号：";
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1) {
				cout << "查找成功!该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入查找的姓名：";
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++) {
				if (m_EmpArray[i]->m_Name == name) {
					cout << "查找成功，职工编号为："
						<< m_EmpArray[i]->m_Id
						<< "号的信息如下：" << endl;
					flag = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false) {
				cout << "查找失败，查无此人" << endl;
			}	
		}
		else {
			cout << "输入选项有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

//排序职工
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "选择排序方式：" << endl;
		cout << "1.按职工号进行升序排序" << endl;
		cout << "2.按职工号进行降序排序" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < m_EmpNum; i++) {
			int minOrmax = i;
			for (int j = i + 1; j < m_EmpNum; j++) {
				//升序
				if (select == 1) {
					if (m_EmpArray[minOrmax]->m_Id > m_EmpArray[j]->m_Id) {
						minOrmax = j;
					}
				}
				//降序
				else {
					if (m_EmpArray[minOrmax]->m_Id < m_EmpArray[j]->m_Id) {
						minOrmax = j;
					}
				}
			}
			if (i != minOrmax) {
				Worker * temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrmax];
				m_EmpArray[minOrmax] = temp;
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->save();
		this->Show_Emp(); //显示职工后面有清屏操作了，所以不需要再清屏了
	}
}

//清空文件
void WorkerManager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		//打开模式 ios::trunc 如果存在 删除文件并重新创建
		ofstream ofs("empFile.txt", ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i] != NULL) {
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}