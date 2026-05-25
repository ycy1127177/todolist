#include "Todolist.h"

#include<iostream>
#include <algorithm>
/*algorithm> 提供了很多常用算法函数，比如：
std::min(a, b) / std::max(a, b) ✅
std::sort(container.begin(), container.end())
std::find(container.begin(), container.end(), value)
std::reverse(container.begin(), container.end())*/

//5.默认构造函数
Todolist::Todolist() :filename("todo_list.txt") {
	//在实现里设置默认相对路径及文件名
	loadFromFile();//创建Todolist的对象的时候就会加载文件中的任务到tasks里，这样就能实现每次打开程序都能看到之前保存的任务了。
}
//6.考虑到可能还存在了别的名字的文件里，所以还要提供一个带文件路径参数的构造函数，允许用户指定文件路径和名字,在头文件里补上声明7
Todolist::Todolist(const std::string& file) :filename(file) {
	//8.这里是用你指定的文件名初始化文件名，注意初始化列表里是Todolist的成员。
	loadFromFile();
}

//9.添加任务的实现,作用目标是task，你输入的任务，不是tasks容器，输入进来的不能更改，用const,头文件里补上参数声明10
//11.不想在这个类里添加任何的人机交互，把返回值改成bool ,头文件里也改
bool Todolist::addTask(const std::string& task) {
	if (!task.empty()) {
		tasks.push_back(task);
		return true;//添加成功，Manager类只需if(todoList.addTask(input){std::cout << "任务添加成功！" << std::endl;}else {std::cout << "任务内容不能为空！" << std::endl;}
	}
	else {
		return false;//添加失败
	}
}

//13 .查看任务的实现,因为只查看不改变tasks,加const,同理返回值也改回bool,
/*viewTasks() 只是查看任务：
它不修改 tasks 或 filename
它只是读取数据，输出到屏幕
所以标记 const 可以：
明确告诉别人：“调用这个函数不会改变对象状态”
编译器会帮你检查，防止函数内部误修改成员变量*/
bool Todolist::viewTasks() const {
	if (tasks.empty()) {
		//如果放任务的vector是空的，就返回false，Manager类就可以根据这个返回值来判断是显示任务还是显示没有任务的提示了。
		return false;
	}

	displayTasksInternal();
	//14.这个外部不需要知道怎么展示，只需要知道展示了，所以在类里补个私有函数。见头文件15.
	//调用一个内部的显示函数，这个函数不对外暴露，专门负责显示任务列表的内容，这样就把显示任务的逻辑和viewTasks的逻辑分开了，viewTasks只负责判断有没有任务，显示任务的逻辑都放在displayTasksInternal里了，这样代码更清晰了。
	return true;//如果有任务，显示完了就返回true
}

bool Todolist::deleteTask(int taskNum) {
	//17.继续写删除任务 注意，现在写的是类，tasks是私有成员变量，成员函数都能访问到，所以不需要传tasks了，直接用就行了，参数是要删除的任务编号
	if (tasks.empty()) {
		return false;//没有任务，删除失败
	}
	if (!isValidIndex(taskNum)) {
		//18.要看输入的编号是否合法，这要再补一个私有函数isValidIndex(int index)来判断，见头文件19
		return false;
	}

	//21.如果编号合法，就删除对应的任务，注意vector的索引是从0开始的，所以要把taskNum转换成索引
	tasks.erase(tasks.begin() + taskNum - 1);//记得-1
	return true;

	/*为什么这里不用 else if
因为前面的 if 都有 return，一旦条件成立，函数就结束了
所以后面的代码只会在前面条件不成立时执行
不需要再嵌套 else，逻辑已经自动隔开了*/
}

//22.清空任务的实现，直接调用vector的clear()函数就行了
bool Todolist::clearAllTasks() {
	tasks.clear();
	return true;//清空成功，返回true
}

//23.存文件的实现，读的时候有默认有指定，存的时候一样 
bool Todolist::saveToFile() const {
	return saveToFile(filename);//调用24带文件名参数的重载函数，传入默认的文件名
	//因为你的函数是const的，所以你的filename会被当成const std::string，所以24的参数也要是const std::string&,别忘了头文件也要改

}

//24.带文件名参数的存文件实现
bool Todolist::saveToFile(const std::string& customFilename) const {
	//输出文件流
	std::ofstream outFile(customFilename);
	if (!outFile.is_open()) {
		return false;
	}
	//遍历vector，一个个存
	for (auto& task : tasks) {
		outFile << task << std::endl;//写入文件，一个任务占一行，endl是换行符
	}

	outFile.close();//记得关闭文件，不然会卡死在前边的is_open，打不开
	return true;
}

//25.读文件的实现，读的时候有默认有指定，存的时候一样
bool Todolist::loadFromFile() {
	return loadFromFile(filename);//调用26带文件名参数的重载函数，传入默认的文件名
}

//26.带文件名参数的读文件实现
bool Todolist::loadFromFile(std::string& customFilename) {
	std::ifstream inputFile(customFilename);
	if (!inputFile.is_open()) {
		return false;
	}
	/*先验证文件,成功后再替换原数据,就是一种temp临时数据的思想*/
	std::vector<std::string> loadTasks;//临时存储加载的任务
	std::string line;//存每行读的内容,写string& line会要你初始化，这是因为string line是创建一个字符串对象，会默认构造空字符串，但是string& line是一个引用，引用的本质是起了个别名，必须引用一个已经存在的对象，所以你必须先创建一个string对象，然后再用这个对象来初始化string& line，这样line就引用了这个对象了

	while (std::getline(inputFile, line)) {
		//读取文件的一行到line里，getline会自动处理换行符，成功了会返回true，失败了会返回false，所以可以用while循环来读取文件的每一行
		if (!line.empty()) {
			//如果不是空行，就存
			loadTasks.push_back(line);
		}
	}
	inputFile.close();

	if (loadTasks.size() > 0){
		//说明确实加载成功任务了，替换原来的tasks
		tasks = std::move(loadTasks);//如果后边不用了，就用move语义把loadTasks的内容移动到tasks里，避免不必要的复制，提高效率
		filename = customFilename;//把默认文件名换成新设置的文件名。
		return true;

	}//见TodoManager.h开始写管理
}

//39.其他要补的工具-获取任务数量
int Todolist::getTaskCount() const {
	return tasks.size();
}
// 获取特定任务
std::string Todolist::getTask(int index) const {
	if (isValidIndex(index)) {
		return tasks[index - 1];
	}
	return "无效的任务索引";
}

//37.补TodoManager用的工具-看tasks是不是空的
bool Todolist::isEmpty() const {
	return tasks.empty();
}



//38.补TodoManager用的工具-统计信息
void Todolist::displayStatistics() const {
	std::cout << "\n--- 统计信息 ---" << std::endl;
	std::cout << "任务总数: " << getTaskCount() << std::endl;
	std::cout << "存储文件: " << getFilename() << std::endl;
	std::cout << "是否为空: " << (isEmpty() ? "是" : "否") << std::endl;

	if (!isEmpty()) {
		std::cout << "前3个任务:" << std::endl;
		int displayCount = std::min(3, getTaskCount());
		for (int i = 1; i <= displayCount; ++i) {
			std::cout << "  " << i << ". " << getTask(i) << std::endl;
		}
	}
}

//31.补TodoManager用的工具-获取文件名
std::string Todolist::getFilename() const {
	return filename;
}

//42.设置文件名
void Todolist::setFilename(const std::string& newFilename) {
	filename = newFilename;
	std::cout << "文件名已更新为: " << filename << std::endl;
}

//16.补工具displayTasksInternal()的实现，注意也是个不改变任何成员变量的函数，所以也要加const
void Todolist::displayTasksInternal() const {
	//展示任务原理，遍历vector
	for (size_t i = 0;i < tasks.size();++i) {
		std::cout << i + 1 << "." << tasks[i] << std::endl;//先用cout把，ai说的返回tasks我觉得不行，人家私密
	}
}

//20.补工具isValidIndex(int index)的实现
bool Todolist::isValidIndex(int index) const {
	if (index >= 1 && index <= static_cast<int>(tasks.size())) {
		//task.size()返回的是size_t类型，是无符号的，所以要和int类型的index比较，先把tasks.size()转换成int类型，避免编译器警告
		return true;
	}
	else {
		return false;
	}
}