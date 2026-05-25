#include <iostream>
#include "TodoManager.h"

#define NOMINMAX
#include<windows.h>

int main() {
    //控制台编译码设置为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    try {
        TodoManager manager;
        manager.run();
    }
    catch (const std::exception& e) {
        std::cerr << "程序发生异常: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}