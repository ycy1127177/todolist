#include <iostream>
#include <vector>
#include <string>
#include <limits>//用于处理缓冲

#define NOMINMAX//windows.h中有个宏定义叫做min和max，这个宏定义会和std::min和std::max冲突，导致编译错误，所以我们需要定义NOMINMAX来禁止windows.h定义min和max这个宏。
#include <windows.h>

//客户需求：我想有个代办事项列表记录一些我容易忘记的事情
//产品需求：我们要做一个简易的代办事项列表，包括可以添加任务、查看任务列表、删除任务、完成任务。
//开发需求：开发一个代办事项列表程序，程序运行时会先打印所有任务列表给用户查看，用户可以通过交互添加任务、删除任务、完成任务。

//自己悟一下，完成任务什么意思，至少要看到自己现在总共添加了多少任务，完成了才好删除

//1.打印列表函数
void printMenu();
void addTasks(std::vector<std::string>& tasks);
void viewTasks(const std::vector<std::string>& tasks);
void deleteTasks(std::vector<std::string>& tasks);

int main() {
	//控制台编译码设置为UTF-8
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	int mainChoice = 0;//记得初始化，这种变量都在栈里，不初始化就会，0xCCCCCCCC	未初始化栈内存。
	std::vector<std::string> tasks; //9.添加删除任务都需要一个放任务的容器，选择vector，当然也可以选择list等其他容器，这个不重要。//不过vector用的多。


	std::cout << "欢迎使用代办事项列表程序" << std::endl;
	do {
		//1.展示主页菜单
		printMenu();
		//2.让用户选择操作
		std::cin >> mainChoice; //准备一个标志位，作为判断分支的标志

		// 清除输入缓冲区，防止后续getline读取到换行符
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//3.根据用户选择执行操作
		switch (mainChoice) {
		case 1:

		//加强版添加任务
		{//用{}来限定case1的作用域，因为case1里有变量定义，如果不限定作用域，变量定义会和其他case冲突
				//4.添加任务 
			int continueChoice = 1;//继续该子菜单的选择标志位 
			while (continueChoice == 1) {
				addTasks(tasks);
				std::cout << "是否还需要继续添加任务？输入1继续，其他键返回主菜单" << std::endl;
				std::cin >> continueChoice; //依旧是输入隐患 
				if (std::cin.fail()) {
					std::cout << "无效输入，返回添加任务子菜单" << std::endl; //清理错误输入cin和错误缓冲区 
					std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continueChoice = 1;
					continue;//回到while循环的开头，进行下一个循环，继续添加任务 
				}
				else {
					//清理正确输入缓冲区 
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}	
			}
			break;
		}
		case 2:
			//5.查看任务
			viewTasks(tasks);
			break;
		case 3:
			//6.删除任务
			deleteTasks(tasks);
			break;
		case 4:
			//7.退出程序
			std::cout << "感些您的使用，再见！" << std::endl;
			break;
		default:
			//8.其他输入无效
			std::cout << "无效的选择，请重新输入" << std::endl;
			//没有break
		}
	} while (mainChoice != 4);//4也是你初始列表的退出按键
		return 0;
}
	

	

//9.菜单的实现
void printMenu() {
	std::cout << "请选择操作：" << std::endl;
	std::cout << "1.添加任务" << std::endl;
	std::cout << "2.查看已添加任务" << std::endl;
	std::cout << "3.删除任务" << std::endl;
	std::cout << "4.退出程序" << std::endl;
}

//10.添加任务的实现
//分析：添加任务需要用户输入任务内容，输入完成后将任务内容添加到任务列表中。主要作用对象是任务列表这个容器，所以要传出还要返回更改的容器，用引用
void addTasks(std::vector<std::string>& tasks) {
	//那么首先要定义用户输入的变量
	std::string inputTask;

	//提醒客户可以输入了
	std::cout << "请输入您要输入的任务:" << std::endl;
	std::getline(std::cin, inputTask);
	//	这句是从控制台读取“一整行”文本 
	// 为什么不用cin>>task,因为cin>>task只能读取一个单词，遇到空格就结束了，而我们输入的任务可能包含空格，所以要用getline来读取整行文本

	//防止客户误输入
	if (!inputTask.empty()) {
		tasks.push_back(inputTask);
		std::cout << "任务添加成功" << std::endl;
	}
	else {
		std::cout << "输入不能为空" << std::endl;
	}
	//扩展的话可以考虑加入询问是否还要继续输入，加个while循环和客户选择标志位判断
}

//11 查看任务的实现,因为只查看不改变tasks,加const
void viewTasks(const std::vector<std::string>& tasks) {
	//分两种情况，有和没有任务
	if (tasks.empty()) {
		std::cout << "没有待办任务" << std::endl;
		return;//退出函数
	}

	std::cout << "当前待办任务如下：" << std::endl;
	//遍历vector
	for (size_t i = 0;i < tasks.size();++i) {
		//size_t无符号整数，vector.size()返回值也是size_t类型，使用size_t可以避免比较时的类型不匹配问题。
		std::cout << i + 1 << "." << tasks[i] << std::endl;
	}
}

//12 删除人物的实现 传入同添加
void deleteTasks(std::vector<std::string>& tasks){
	//两种情况有没有任务
	if (tasks.empty()) {
		std::cout << "当前没有任务" << std::endl;
		return;
	}

	//用户打算删除任务几呢？搞个变量存
	int deleteNum = 0;
	std::cout << "请输入你要删除的任务编号" << std::endl;
	//因为这里没有空格的可能性，直接cin
	std::cin >> deleteNum;

	//要看看用户输对了没有
	if (std::cin.fail()) {
		//你定义了一个int变量，如果你cin的不是int类型的比如abc,cin.fail()就会返回true，说明输入解析失败了，这时候我们就要清除错误状态和输入缓冲区，防止后续输入受到影响
		//不是数字好用这个判断，是数字也还要判断有没有超出tasks的边界
		std::cin.clear();//清楚错误状态
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//清除错误输入状态的输入缓冲区
		std::cout << "请输入有效数字" << std::endl;

		return;//返回主循环，主循环会返回while，重新进入switch进入主菜单
	}
	//清楚正确输入状态的输入缓冲区
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (deleteNum >= 1 && deleteNum <= static_cast<int>(tasks.size())) {
		//int是有符号整数，size_t是无符号整数，所以要用static_cast<int>来转换一下，避免比较时的类型不匹配问题，这是C++的新转换类型写法。
		//std::string deleteTask = tasks[deleteNum - 1];//记得你显示任务的时候序列号是vector里的序列号+1，先把要删除的任务内容保存一下，方便后面输出删除成功的提示

		//erase(iterator position)
		tasks.erase(tasks.begin() + deleteNum - 1);//iterator position=begin+i i=012345,第几个对应i+1=Num
		std::cout << "任务" << deleteNum << "删除成功" << std::endl;
		//若要显示内容也可以把上面deletetask的语句恢复，然后写
		//std::cout << "任务 \"" << removedTask << "\" 已删除！" << std::endl;
	}
	else {
		std::cout << "请输入有效的任务编号" << std::endl;
	}
}
