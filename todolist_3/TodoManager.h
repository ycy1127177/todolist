#ifndef TODOMANAGER_H
#define TODOMANAGER_H

#include "Todolist.h" 
#include <memory>//主要提供智能指针、内存分配工具、RAII 内存管理。

//27.管理类的功能：展示添加任务删除任务查看任务清除所有任务退出菜单的主菜单，展示保存任务到文件，加载文件任务的功能

class TodoManager {
public:
    //客户只需要知道用了这个run()就能管理任务了
    TodoManager();//默认构造函数
    void run();

private:
	//28.和Todolist要链接起来,用unique智能指针
	std::unique_ptr<Todolist> todoList;

	//以上如何实现功能的函数都不需要再让客户知道了，
    void printMainMenu() const;
    void printFileMenu() const;
    void handleMainMenu();
    void handleFileMenu();
    void handleAddTask();
    void handleDeleteTask();
    void handleSaveToFile();
    void handleLoadFromFile();
    void handleViewFileContent() const;
};

#endif