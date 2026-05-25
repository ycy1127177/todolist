#include "TodoManager.h"
#include<iostream>
#include<limits>//缓冲问题

//29.默认构造函数
TodoManager::TodoManager() :todoList(std::make_unique<Todolist>()){}

//30.run()功能：启动程序，显示主菜单，处理用户输入，直到用户选择退出为止
void TodoManager::run() {
	//我们注意到todolist的构造函数涉及读的文件，那么我要给客户一个展示，告诉他读的是什么，那么todolist里边加一个Public的getfilename（）;
	std::cout << "欢迎使用Todolist程序,当前文件->" << todoList->getFilename() << std::endl;
	
	//运行主循环-即整个程序
	handleMainMenu();
}

//33 主菜单具体内容
void TodoManager::printMainMenu() const {
	std::cout << "\n--- 主菜单 ---" << std::endl;
	std::cout << "1. 添加任务" << std::endl;
	std::cout << "2. 查看所有任务" << std::endl;
	std::cout << "3. 删除任务" << std::endl;
	std::cout << "4. 文件操作" << std::endl;
	std::cout << "5. 统计信息" << std::endl;
	std::cout << "6. 清空所有任务" << std::endl;
	std::cout << "7. 退出程序" << std::endl;
	std::cout << "请选择操作 (1-7): ";
}


//32.主循环
void TodoManager::handleMainMenu() {
	int mainChoice = 0;
	do {
		printMainMenu();
		
		//客户输入
		std::cin >> mainChoice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (mainChoice) {
		case 1:
			handleAddTask();
			break;
		case 2:
			todoList->viewTasks();
			break;
		case 3:
			handleDeleteTask();
			break;
		case 4:
			handleFileMenu();
			break;
		case 5:
			todoList->displayStatistics();//37.补一个tasks的统计信息
			break;
		case 6:
			todoList->clearAllTasks();
			break;
		case 7:
			std::cout << "感谢使用待办事项列表，再见！" << std::endl;
			break;
		default:
			std::cout << "无效选择，请重试。" << std::endl;
		}

	} while (mainChoice != 7);
}




//34.添加任务
void TodoManager::handleAddTask() {
	//局部存储用户添加的任务
	std::string task;

	std::cout << "请输入您要添加的任务" << std::endl;
	std::getline(std::cin, task);//文件读出来的存task

	//然后再存进todolist类的tasks里
	if (todoList->addTask(task)) {
		std::cout << "任务已添加成功！" << std::endl;
	}
	else {
		std::cout << "任务不能为空！" << std::endl;
	}
	// 询问是否立即保存
	if (!task.empty()) {
		char autoSave;
		std::cout << "是否立即保存到文件？(y/n): ";
		std::cin >> autoSave;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (autoSave == 'y' || autoSave == 'Y') {
			todoList->saveToFile();
		}
	}
}


//35.删除任务
void TodoManager::handleDeleteTask() {
	todoList->viewTasks();
	if (!todoList->isEmpty()) {
		int taskNumber;
		std::cout << "请输入要删除的任务编号: ";
		std::cin >> taskNumber;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "请输入有效的数字！" << std::endl;
			return;
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		bool isok=todoList->deleteTask(taskNumber);
		if (isok) {
			std::cout << "任务" << taskNumber << "已经删除！" << std::endl;
		}
	}
}

// 37.文件操作菜单
void TodoManager::printFileMenu() const {
	std::cout << "\n--- 文件操作 ---" << std::endl;
	std::cout << "1. 保存任务到文件" << std::endl;
	std::cout << "2. 从文件加载任务" << std::endl;
	std::cout << "3. 查看文件内容" << std::endl;
	std::cout << "4. 更改文件名" << std::endl;
	std::cout << "5. 返回主菜单" << std::endl;
	std::cout << "请选择操作 (1-5): ";
}

//41.进入文件操作菜单的子循环
void TodoManager::handleFileMenu() {
	int fileChoice = 0;
	do {
		printFileMenu();
		std::cin >> fileChoice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (fileChoice) {
		case 1:
			handleSaveToFile();
			break;
		case 2:
			handleLoadFromFile();
			break;
		case 3:
			handleViewFileContent();
			break;
		case 4:
		{
			std::string newFilename;
			std::cout << "请输入新的文件名: ";
			std::getline(std::cin, newFilename);
			todoList->setFilename(newFilename);
		}
		break;
		case 5:
			std::cout << "返回主菜单..." << std::endl;
			break;
		default:
			std::cout << "无效选择，请重试。" << std::endl;
		}
	} while (fileChoice != 5);
}

//43.子菜单存文件：存默认or新建文件存
void TodoManager::handleSaveToFile() {
	char choice;
	std::cout << "保存到默认文件 " << todoList->getFilename() << "？(y/n): ";
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (choice == 'y' || choice == 'Y') {
		todoList->saveToFile();
	}
	else {
		//输入别的就创建一个新文件保存
		std::string customFilename;
		std::cout << "请输入自定义文件名: ";
		std::getline(std::cin, customFilename);
		todoList->saveToFile(customFilename);
	}
}

//44.子菜单加载文件：取默认or指定文件加载
void TodoManager::handleLoadFromFile() {
	char choice;
	std::cout << "从默认文件 " << todoList->getFilename() << " 加载？(y/n): ";
	std::cin >> choice;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (choice == 'y' || choice == 'Y') {
		todoList->loadFromFile();
	}
	else {
		std::string customFilename;
		std::cout << "请输入要加载的文件名: ";
		std::getline(std::cin, customFilename);
		todoList->loadFromFile(customFilename);//设置最新的默认文件
	}
	//理论上还要判断一下有没有这个文件，先不弄了，实在搞太久了，有空在研究
}

//45.看文件内容
void TodoManager::handleViewFileContent() const {
	std::string filename = todoList->getFilename();
	std::ifstream file(filename);//读最新的默认文件

	if (file.is_open()) {
		std::cout << "\n--- 文件内容 (" << filename << ") ---" << std::endl;
		std::string line;
		int lineNum = 1;
		while (std::getline(file, line)) {
			std::cout << lineNum << ". " << line << std::endl;
			lineNum++;
		}
		file.close();
	}
	else {
		std::cout << "文件不存在或无法打开！" << std::endl;
	}
}


