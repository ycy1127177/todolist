#1.公司要求最低什么版本CMake你就什么版本 
cmake_minimum_required(VERSION 3.10)
#2.项目名
project(02_todolist VERSION 1.0.0 LANGUAGES CXX)
#3.#公司统一用的C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)#强制这个版本

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 使用线条字生成：https://www.toolnb.com/tools/xiantiaozi.html
message(STATUS " ▄▄▄▄▄▄▄▄▄▄▄  ▄▄        ▄  ▄▄▄▄▄▄▄▄▄▄▄       ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄  ▄▄▄▄▄▄▄▄▄▄▄ ") 
message(STATUS "▐░░░░░░░░░░░▌▐░░▌      ▐░▌▐░░░░░░░░░░░▌     ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌") 
message(STATUS "▐░█▀▀▀▀▀▀▀█░▌▐░▌░▌     ▐░▌▐░█▀▀▀▀▀▀▀▀▀      ▐░█▀▀▀▀▀▀▀█░▌ ▀▀▀▀█░█▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ▐░█▀▀▀▀▀▀▀▀▀ ") 
message(STATUS "▐░▌       ▐░▌▐░▌▐░▌    ▐░▌▐░▌               ▐░▌       ▐░▌     ▐░▌     ▐░▌          ▐░▌          ▐░▌          ") 
message(STATUS "▐░▌       ▐░▌▐░▌ ▐░▌   ▐░▌▐░█▄▄▄▄▄▄▄▄▄      ▐░█▄▄▄▄▄▄▄█░▌     ▐░▌     ▐░█▄▄▄▄▄▄▄▄▄ ▐░▌          ▐░█▄▄▄▄▄▄▄▄▄ ") 
message(STATUS "▐░▌       ▐░▌▐░▌  ▐░▌  ▐░▌▐░░░░░░░░░░░▌     ▐░░░░░░░░░░░▌     ▐░▌     ▐░░░░░░░░░░░▌▐░▌          ▐░░░░░░░░░░░▌") 
message(STATUS "▐░▌       ▐░▌▐░▌   ▐░▌ ▐░▌▐░█▀▀▀▀▀▀▀▀▀      ▐░█▀▀▀▀▀▀▀▀▀      ▐░▌     ▐░█▀▀▀▀▀▀▀▀▀ ▐░▌          ▐░█▀▀▀▀▀▀▀▀▀ ") 
message(STATUS "▐░▌       ▐░▌▐░▌    ▐░▌▐░▌▐░▌               ▐░▌               ▐░▌     ▐░▌          ▐░▌          ▐░▌          ") 
message(STATUS "▐░█▄▄▄▄▄▄▄█░▌▐░▌     ▐░▐░▌▐░█▄▄▄▄▄▄▄▄▄      ▐░▌           ▄▄▄▄█░█▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ▐░█▄▄▄▄▄▄▄▄▄ ") 
message(STATUS "▐░░░░░░░░░░░▌▐░▌      ▐░░▌▐░░░░░░░░░░░▌     ▐░▌          ▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌▐░░░░░░░░░░░▌") 
message(STATUS " ▀▀▀▀▀▀▀▀▀▀▀  ▀        ▀▀  ▀▀▀▀▀▀▀▀▀▀▀       ▀            ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀  ▀▀▀▀▀▀▀▀▀▀▀ ") 

#4.管理源文件：创建一个包含所有源文件的变量
set(_SOURCES1
    todolist_1/todolist_1.cpp
	todolist_1/todolist_1.h
	
	#TodoManager.cpp
	#TodoManager.h
)

add_executable(todolist_1 ${_SOURCES1})

set(_SOURCES2
    todolist_2/todolist_2.cpp
	todolist_2/todolist_2.h
	
	#TodoManager.cpp
	#TodoManager.h
)




add_executable(todolist_2 ${_SOURCES2})


set(_SOURCES3
    todolist_3/Todolist.cpp
	todolist_3/Todolist.h
	
	todolist_3/TodoManager.cpp
	todolist_3/TodoManager.h
	
	todolist_3/main.cpp
)




add_executable(todolist_3 ${_SOURCES3})

#单个exe的时候这么写
#windows vs 编译器
#if(MSVC)
		
	#设置要放到创建了exe以后
	# Windows/MSVC
	# UTF-8源码解析+#警告等级+#E-开启异常，H-异常展开，s-标准C++异常，c-extern"C"默认不抛异常
	#用 target_compile_options() 替代 add_compile_options()
	#add_compile_options() 是全局生效，可能被 VS 生成的项目默认覆盖。
	#target_compile_options() 直接作用于指定的 exe 或 lib，保证 /W4 真正生效。
	
	#target_compile_options(todolist_1 PRIVATE
	#		/utf-8  # UTF-8解析源码
	#		/W4     # 警告等级4
	#		/EHsc   # 异常处理标准C++
	#)

	# Unicode字符集
	#target_compile_definitions(todolist_1 PRIVATE
	#		UNICODE
	#		_UNICODE
	#)
	
#linux GCC
#GCC / Clang
#GCC / Clang 通常直接识别 UTF-8 源码
#-Wall -Wextra → 打开大部分警告
#-pedantic → GCC 特有，要求标准严格
#-Weverything → Clang 特有，打开所有警告
#-fexceptions → 保证异常可用
#elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    message(STATUS "Using GCC compiler")

    # GCC 警告等级
    #target_compile_options(todolist_1 PRIVATE
    #    -Wall
    #    -Wextra
    #    -pedantic
    #    -fexceptions
    #)

#linux Clang
#elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    #message(STATUS "Using Clang compiler")

    # Clang 警告等级
    #target_compile_options(todolist_1 PRIVATE
    #    -Wall
    #    -Wextra
    #    -Weverything
    #    -fexceptions
    #)
#endif()
#多个exe这么设置
# Windows VS
if(MSVC)#compile调试
    set(COMPILE_OPTS /utf-8 /W4 /EHsc)#可以直接替换的东西在这
    set(DEFINES UNICODE _UNICODE)#可以直接替换的东西在这
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILE_OPTS -Wall -Wextra -pedantic -fexceptions)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILE_OPTS -Wall -Wextra -Weverything -fexceptions)
endif()

# 可执行文件1
target_compile_options(todolist_1 PRIVATE ${COMPILE_OPTS})
if(MSVC)
    target_compile_definitions(todolist_1 PRIVATE ${DEFINES})
endif()

# 可执行文件2
target_compile_options(todolist_2 PRIVATE ${COMPILE_OPTS})
if(MSVC)
    target_compile_definitions(todolist_2 PRIVATE ${DEFINES})
endif()

# 可执行文件3
target_compile_options(todolist_3 PRIVATE ${COMPILE_OPTS})
if(MSVC)
    target_compile_definitions(todolist_3 PRIVATE ${DEFINES})
endif()



#5.打印日志_配置成功
message(STATUS "todolist_1 and todolist_2 and todolist_3 project configured sucessfully.")