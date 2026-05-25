#ifndef TODOLIST_H
#define TODOLIST_H

#include<vector>
#include<string>
#include<fstream>

//本头文件是实现数据存储功能。
//分析：我们这个小程序的功能是添加任务删除任务查看任务，存储任务，读取任务，查看存任务的文件
//1.先看最简单最没有关联的，文件，存东西的文件你得要路径把，所以Todolisty

class Todolist {
public:
	Todolist();//2.默认构造函数，不知道怎么写先放这
	explicit Todolist(const std::string& file);//7.根据分析需要添加新的构造函数。8见cpp,explicit是为了防止隐式转换string转Todolist
	/*explicit 只对“构造函数”有意义，构造函数才存在“隐式转换生成对象”的问题*/

	//3.任务的添加查看删除清空功能
	bool addTask(const std::string& task );//根据需要写参数，11见cpp //12.不想在这个类里添加任何的人机交互，把返回值改成bool ,头文件里也改，13见cpp
	bool viewTasks() const;
	bool deleteTask(int TaskNum);
	bool clearAllTasks();

	//4.存文件看文件读文件，不知道返回什么都先统统写viod，后续想到输出存好没删除没都是TodolistManager管，就传一个状态就好，用bool，5见cpp
	bool saveToFile() const;
	bool saveToFile(const std::string& customFilename) const;//custom Filename 自定义文件名
	bool loadFromFile ();
	bool loadFromFile(std::string& customFilename);//要更改文件名，所以不用const了。

	//40.其他工具声明
	int getTaskCount() const;
	std::string getTask(int index) const;
	//36 tasks是否是空的
	bool isEmpty() const;


	//30.用再Todomanager里交互展示的-获得文件名
	std::string getFilename() const;
	//42.设置新的文件名
	void setFilename(const std::string& newFilename);

	//39.统计信息
	void displayStatistics() const;

private:
	void displayTasksInternal() const;//15.这个外部不需要知道怎么展示，只需要知道展示了，所以在类里补个私有函数。实现见cpp16.
	bool isValidIndex(int index) const;//19.只判断不改变

private:
	//1.私有的一般放后边，且成员和函数是分开写的
	std::vector<std::string> tasks;//存任务
	std::string filename;//文件路径
};

#endif
