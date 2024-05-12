#  			**CMake使用**

## **一、什么是CMake（cross platform make）**

​	CMake 是一个项目构建工具，并且是==跨平台==的。关于项目构建有`Makefil`（通过 make 命令进行项目的构建），大多是IDE软件都集成了`make`，比如：VS 的 `nmake`、linux 下的 `GNU make`、Qt 的 `qmake`等，如果自己动手写` makefile`，会发现，`makefile `通常依赖于当前的编译平台，而且编写 `makefile` 的工作量比较大，解决依赖关系时也容易出错。

​	而 CMake 恰好能解决上述问题， 其允许开发者指定整个工程的编译流程，在根据编译平台，自动生成本地化的Makefile和工程文件，最后用户只需`make`编译即可，所以可以把CMake看成一款自动生成 `Makefile`的工具。

* 蓝色线是`makefile`构建项目的过程
* 红色线是`cmake`构建项目的过程

#### CMake应用场景

​	假如我们有一个深度学习框架的部分工程列表，里面有超过40个互相调用的工程共同组成，一些用于生成库文件，一些用于实现逻辑功能。他们之间的调用关系复杂而严格，如果我想在这样复杂的框架下==进行二次开发==，显然只拥有它的源码是远远不够的，还需要清楚的明白这几十个项目之间的复杂关系，在没有原作者的帮助下进行这项工作几乎是不可能的。

​	即使是原作者给出了相关的结构文档，对新手来说建立工程的过程依旧是漫长而艰辛的，因此CMake的作用就凸显出来了。原作者只需要生成一份`CMakeLists.txt`文档，框架的使用者们只需要在下载源码的同时下载作者提供的`CMakeLists.txt`，就可以利用CMake，在”原作者的帮助下“进行工程的搭建。

#### 优点

* 跨平台：在 Linux/Unix 平台，生成 `makefile`，在苹果平台，可以生成 `xcode`，在 Windows 平台，可以生成 MSVC 的工程文件。
* 能够管理大型项目。
* 简化编译构建过程和编译过程，Cmake 的工具链非常简单：`cmake 文件路径`+`make`。
* 可扩展：可以为CMake 编写特定功能的模块，扩充 CMake 功能。

## 二、如何使用CMake

#### 1.单目录，多文件

* add.c

  ```c
  #include <stdio.h>
  #include "head.h"
  
  int add(int a, int b)
  {
      return a+b;
  }
  ```

* sub.c

  ```c
  #include <stdio.h>
  #include "head.h"
  
  int subtract(int a, int b)
  {
      return a-b;
  }
  ```

* mult.c

  ```c
  #include <stdio.h>
  #include "head.h"
  
  int multiply(int a, int b)
  {
      return a*b;
  }
  ```

* div.c

  ```c
  #include <stdio.h>
  #include "head.h"
  
  double divide(int a, int b)
  {
      return (double)a/b;
  }
  ```

* head.h

  ```c
  #ifndef _HEAD_H
  #define _HEAD_H
  // 加法
  int add(int a, int b);
  // 减法
  int subtract(int a, int b);
  // 乘法
  int multiply(int a, int b);
  // 除法
  double divide(int a, int b);
  #endif
  ```

* main.c

  ```c
  #include <stdio.h>
  #include "head.h"
  
  int main()
  {
  
  	printf("这是一个简易的计算器")；
      int a = 932;
      int b = 343;
      printf("a = %d, b = %d\n", a, b);
      printf("a + b = %d\n", add(a, b));
      printf("a - b = %d\n", subtract(a, b));
      printf("a * b = %d\n", multiply(a, b));
      printf("a / b = %f\n", divide(a, b));
      return 0;
  }
  ```

**添加`CMakeLists.txt`文件**

在上述源文件所在目录下添加一个新文件 ``CMakeLists.txt``，文件内容如下：

```cmake
cmake_minimum_required(VERSION 3.0) # 指定使用的 cmake 的最低版本
project(CALC) # 定义工程名称
add_executable(app add.cpp div.cpp main.cpp mult.cpp sub.cpp) # 生成一个可执行程序，其中app是可执行程序名
```

* `add_executable(可执行程序名 源文件名称)`

==这里的可执行程序名和`project`中的项目名没有任何关系==；源文件名可以是一个也可以是多个，如有多个可用空格或`;`间隔。

**执行`CMake`命令**

```shell
# cmake 命令原型
$ cmake CMakeLists.txt文件所在路径
```

当执行`cmake`命令之后，`CMakeLists.txt `中的命令就会被执行，所以一定要注意给`cmake` ==命令指定路径==的时候一定不能出错。

执行命令之后，源文件所在目录中就会多一些文件，比如`makefile`文件，不用理会它们，这时再执行`make`命令，就可以对项目进行构建得到所需的可执行程序了。

**但是**

在上面的例子中一共提供了5个源文件，有些工程会包括更多甚至几十个，假设这些文件需要反复被使用，每次都直接将它们的名字写出来确实是在麻烦，此时我们就需要定义一个变量，将文件名对应的字符串存储起来，在`cmake`里定义变量需要使用`set`。

```cmake
# 方式1: 各个源文件之间使用空格间隔
# set(SRC_LIST add.cpp  div.cpp main.cpp mult.cpp sub.cpp)

# 方式2: 各个源文件之间使用分号 ; 间隔
set(SRC_LIST add.cpp;div.cpp;main.cpp;mult.cpp;sub.cpp)
add_executable(app ${SRC_LIST})
```

**内部构建和外部构建**

* **内部构建**就是在项目内部,有`CMakeList.txt`的地方,直接`cmake .`,比如前面讲的简单案例就是内部构建. 结果就是在项目下面生成了很多的临时文件。如果再基于`makefile`文件执行`make`命令，程序在编译过程中还会生成一些中间文件和一个可执行文件，这样会导致整个项目目录看起来很混乱，不太容易管理和维护,这时我们就可以把生成的这些与项目源码无关的文件统一放到一个对应的目录里边（`build`），也就是下面要提到的外部构建。

* **外部构建**就是不直接在项目下面运行`cmake`, 而是自己建立一个接受cmake之后的临时文件的文件夹,然后再该文件夹下面调用`cmake <CMakeList_path>` 来构建。

  ```cmake
  $ mkdir build
  $ cd build
  $ cmake ..
  ```

  现在`cmake`命令是在`build`目录中执行的，但是`CMakeLists.txt`文件在`build`目录的上一级目录中，所以`cmake `命令后指定的路径为`..`，即当前目录的上一级目录。

**指定使用的`C++`标准**

在编写`C++`程序的时候，可能会用到`C++11`、`C++14`、`C++17`、`C++20`等新特性，那么就需要在编译的时候在编译命令中制定出要使用哪个标准：

```shell
$ g++ *.cpp -std=c++11 -o app
//通过参数 -std=c++11 指定出要使用c++11标准编译程序
```

而在CMake中想要指定C++标准有两种方式：

在此之前要了解一个宏：``DCMAKE_CXX_STANDARD``

* 在 `CMakeLists.txt `中通过 `set `命令指定

```cmake
# 增加-std=c++11
set(CMAKE_CXX_STANDARD 11)
# 增加-std=c++14
set(CMAKE_CXX_STANDARD 14)
# 增加-std=c++17
set(CMAKE_CXX_STANDARD 17)
```

* 在执行 `cmake `命令的时候指定出这个宏的值

```cmake
# 增加-std=c++11
cmake CMakeLists.txt文件路径 -DCMAKE_CXX_STANDARD=11
# 增加-std=c++14
cmake CMakeLists.txt文件路径 -DCMAKE_CXX_STANDARD=14
# 增加-std=c++17
cmake CMakeLists.txt文件路径 -DCMAKE_CXX_STANDARD=17
```

**指定输出的路径**

在`CMake`中指定可执行程序输出的路径，也对应一宏:`EXECUTABLE_OUTPUT_PATH`，它的值也是通过`set`命令进行设置:

```cmake
set(HOME /home/lin/Share_CMake) # 定义一个变量用于存储一个绝对路径
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
# 将拼接好的路径值设置给宏,如果这个路径中的子目录不存在，会自动生成，无需自己手动创建
```

**搜索文件**

项目源文件很多的情况下，在编写`CMakeLists.txt`文件的时候不可能一一罗列出来，所以`CMake`为我们提供了搜索文件的命令，可以使用`aux_source_directory`命令或者`file`命令。

* 使用`aux_source_directory `命令可以查找某个路径下的所有源文件

  ```cmake
  aux_source_directory(< dir > < variable >)
  # dir：要搜索的目录
  # variable：将从dir目录下搜索到的源文件列表存储到该变量中
  ```

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
# 指定源文件对应的头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 搜索 src 目录下的源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_executable(app  ${SRC_LIST})
```

==PROJECT_SOURCE_DIR宏对应的值,就是我们在使用cmake命令时后面紧跟的目录，一般是工程的根目录。==

* 使用`file`命令搜索目录下所有的源文件，并存储到变量中

  ```cmake
  file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)
  # GLOB: 将指定目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中。
  # GLOB_RECURSE：递归搜索指定目录，将搜索到的满足条件的文件名生成一个列表，并将其存储到变量中。
  ```

```cmake
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
# 关于要搜索的文件路径和类型可加双引号，也可不加:
# file(GLOB MAIN_HEAD "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
```

==CMAKE_CURRENT_SOURCE_DIR 宏表示当前访问的 CMakeLists.txt 文件所在的路径。==

**总结**

```cmake
# 一个比较基础的CMakeLists.txt文件
cmake_minimum_required(VERSION 3.0)
project(CALC)
set(CMAKE_CXX_STANDARD 11)
set(HOME /home/lin/Share_CMake)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin/)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(app ${SRC_LIST})
```

**制作、链接动态库或静态库**

有些时候我们编写的源代码并不需要将他们编译生成可执行程序，而是生成一些静态库或动态库提供给第三方使用，在`cmake`中就可以实现库的制作和链接。

* 静态库

<u>制作静态库</u>：

```cmake
add_library(库名称 STATIC 源文件1 [源文件2] ...) 
# 在Linux中，静态库名字分为三部分：lib+库名字+.a，此处只需要指定出库的名字就可以，另外两部分在生成该文件的时候会自动填充。
```

将`src`目录中的源文件编译成静态库，然后再使用:

```shell
.
├── build
├── CMakeLists.txt
├── include           # 头文件目录
│   └── head.h
├── main.cpp          # 用于测试的源文件
└── src               # 源文件目录
    ├── add.cpp
    ├── div.cpp
    ├── mult.cpp
    └── sub.cpp
```

`CMakeLists.txt`文件这样编写：

```shell
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(calc STATIC ${SRC_LIST})
# 最终生成静态库文件libcalc.a
```

<u>链接静态库：</u>

```cmake
link_libraries(<static lib> [<static lib>...])
# 参数就是要链接的静态库的名字，可以是全名libxxx.a，也可以是掐头（lib）去尾（.a）之后的名字 xxx
```

如果该静态库不是系统提供的（自己制作或者使用第三方提供的静态库）可能出现静态库找不到的情况，这是需要将静态库的路径也指定出来：`link_directories(<lib path>)`

最终的`CMakeLists.txt`文件就是这样的:

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
# 搜索指定目录下源文件
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# 包含头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 包含静态库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
# 链接静态库
link_libraries(calc)
add_executable(app ${SRC_LIST})
```

* 动态库

<u>制作动态库</u>：

和制作静态库类似，只需要修改一个命令参数：

```cmake
add_library(库名称 SHARED 源文件1 [源文件2] ...) 
# 在Linux中，动态库名字分为三部分：lib+库名字+.so，此处只需要指定出库的名字就可以了，另外两部分在生成该文件的时候会自动填充。
```

==静态库是STATIC，动态库是SHARED==

根据之前的那个目录结构，编写`CMakeLists.txt`文件

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(calc SHARED ${SRC_LIST})
```

<u>链接系统动态库:</u>

```cmake
target_link_libraries(
    <target> 
    <PRIVATE|PUBLIC|INTERFACE> <item>... 
    [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
# target：指定要加载动态库的文件的名字,该文件可能是一个源文件/动态库文件/可执行文件
# PRIVATE|PUBLIC|INTERFACE：动态库的访问权限，默认为PUBLIC
```

动态库的链接和静态库是完全不同的：

​	静态库会在生成可执行程序的链接阶段**被打包**到可执行程序中，所以可执行程序启动，静态库就被加载到内存中了。
​	动态库在生成可执行程序的链接阶段**不会被打包**到可执行程序中，当可执行程序被启动并且**调用了动态库中的函数**的时候，动态库才会被加载到内存。

​	所以，在`cmake`中指定要链接的动态库的时候，应该==将命令写到生成了可执行文件之后==：

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 添加并指定最终生成的可执行程序名
add_executable(app ${SRC_LIST})
# 指定可执行程序要链接的动态库名字
target_link_libraries(app pthread)

# app: 对应的是最终生成的可执行程序的名字
# pthread：这是可执行程序要加载的动态库，这个库是系统提供的线程库，全名为libpthread.so，在指定的时候一般会掐头（lib）去尾（.so）。
```

<u>链接第三方动态库：</u>

假设在测试文件`main.cpp`中既使用了自己制作的动态库`libcalc.so`又使用了系统提供的线程库，此时`CMakeLists.txt`文件可以这样写：

````cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 指定源文件或者动态库对应的头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 指定要链接的动态库的路径,否则可执行程序启动之后会加载失败，因为找不到库的位置
link_directories(${PROJECT_SOURCE_DIR}/lib)
# 添加并生成一个可执行程序
add_executable(app ${SRC_LIST})
# 指定要链接的动态库
target_link_libraries(app pthread calc)
````

**指定库文件的输出路径**

* 适用于动态库

由于在Linux下**生成的动态库默认是有执行权限的**，所以可以按照生成可执行程序的方式去指定它生成的目录：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# 设置动态库生成路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 简单来说就是通过set命令给EXECUTABLE_OUTPUT_PATH宏设置了一个路径，这个路径就是可执行文件生成的路径。
add_library(calc SHARED ${SRC_LIST})
```

* 静态库和动态库都适用

在Linux下**生成的静态库默认不具有可执行权限**，所以在指定静态库生成的路径的时候就不能使用`EXECUTABLE_OUTPUT_PATH`宏了，而应该使用`LIBRARY_OUTPUT_PATH`，这个宏对应静态库文件和动态库文件都适用。

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 生成动态库
#add_library(calc SHARED ${SRC_LIST})
# 生成静态库
add_library(calc STATIC ${SRC_LIST})
```

**日志**

在`CMake`中可以用用户显示一条消息，该命令的名字为`message`。

```cmake
message([STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR] "message to display" ...)
```

(无) ：重要消息
`STATUS` ：非重要消息
`WARNING`：CMake 警告, 会继续执行
`AUTHOR_WARNING`：CMake 警告 (dev), 会继续执行
`SEND_ERROR`：CMake 错误, 继续执行，但是会跳过生成的步骤
`FATAL_ERROR`：CMake 错误, 终止所有处理过程

CMake的命令行工具会在stdout上显示`STATUS`消息，在stderr上显示其他所有消息。

```cmake
# 输出一般日志信息
message(STATUS "source path: ${PROJECT_SOURCE_DIR}")
# 输出警告信息
message(WARNING "source path: ${PROJECT_SOURCE_DIR}")
# 输出错误信息
message(FATAL_ERROR "source path: ${PROJECT_SOURCE_DIR}")
```

#### 2.多目录，多文件

如果项目很大，或者项目中有很多的源码目录，在通过CMake管理项目的时候如果只使用一个`CMakeLists.txt`，那么这个文件相对会比较复杂，有一种化繁为简的方式就是给每个源码目录都添加一个`CMakeLists.txt`文件（头文件目录不需要），这样每个文件都不会太复杂，而且更灵活，更容易维护。

```shell
$ tree
.
├── calc
│   ├── add.cpp
│   ├── CMakeLists.txt
│   ├── div.cpp
│   ├── mult.cpp
│   └── sub.cpp
├── CMakeLists.txt
├── include
│   ├── calc.h
│   └── sort.h
├── sort
│   ├── CMakeLists.txt
│   ├── insert.cpp
│   └── select.cpp
├── test1
│   ├── calc.cpp
│   └── CMakeLists.txt
└── test2
    ├── CMakeLists.txt
    └── sort.cpp
```

Linux的目录是树状结构，所以嵌套的 CMake 也是一个树状结构，最顶层的 `CMakeLists.txt `是根节点，其次都是子节点。以下是一些关于 `CMakeLists.txt` 文件变量作用域的信息：

* 根节点CMakeLists.txt中的变量全局有效
* 父节点CMakeLists.txt中的变量可以在子节点中使用
* 子节点CMakeLists.txt中的变量只能在当前节点中使用

**添加子目录**

```cmake
add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])
# source_dir：指定了CMakeLists.txt源文件和代码文件的位置，其实就是指定子目录
# binary_dir：指定了输出文件的路径，一般不需要指定，忽略即可。
# EXCLUDE_FROM_ALL：在子路径下的目标默认不会被包含到父路径的ALL目标里，并且也会被排除在IDE工程文件之外。用户必须显式构建在子路径下的目标。
```

**根目录**

```cmake
cmake_minimum_required(VERSION 3.0)
project(test)
# 定义变量
# 静态库生成的路径
set(LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 测试程序生成的路径
set(EXEC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 头文件目录
set(HEAD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
# 静态库的名字
set(CALC_LIB calc)
set(SORT_LIB sort)
# 可执行程序的名字
set(APP_NAME_1 test1)
set(APP_NAME_2 test2)
# 添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)
```

在根目录的 `CMakeLists.txt`文件中主要做了两件事情：**定义全局变量**和**添加子目录**。

* 定义的全局变量主要是给子节点使用，目的是为了提高子节点中的`CMakeLists.txt`文件的可读性和可维护性，避免冗余并降低出差的概率。
* 一共添加了四个子目录，每个子目录中都有一个`CMakeLists.txt`文件，这样它们的父子关系就被确定下来了。

**子目录**

* calc 目录、sort 目录

```cmake
# calc 目录中的 CMakeLists.txt文件
cmake_minimum_required(VERSION 3.0) 
project(CALCLIB)
aux_source_directory(./ SRC) # 搜索当前目录（calc目录）下的所有源文件
include_directories(${HEAD_PATH}) # 包含头文件路径，HEAD_PATH已在根节点文件中定义
set(LIBRARY_OUTPUT_PATH ${LIB_PATH}) # 设置库的生成的路径，LIB_PATH已在根节点文件中定义
add_library(${CALC_LIB} STATIC ${SRC}) # 生成静态库，静态库名字CALC_LIB已在根节点文件中定义

# sort 目录中的 CMakeLists.txt文件只需将第六行的改为
add_library(${SORT_LIB} SHARED ${SRC}) # 生成动态库
```

* test1 目录

```cmake
# test1 目录中的 CMakeLists.txt文件
cmake_minimum_required(VERSION 3.0)
project(CALCTEST)
aux_source_directory(./ SRC)
include_directories(${HEAD_PATH}) # 指定头文件路径
link_directories(${LIB_PATH}) # 指定静态库生成路径
link_libraries(${CALC_LIB}) # 指定可执行程序要链接的静态库，CALC_LIB变量已在根节点文件中定义
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH}) # 指定可执行程序生成的路径，EXEC_PATH变量已在根节点文件中定义
add_executable(${APP_NAME_1} ${SRC}) # 生成可执行程序，APP_NAME_1变量已在根节点文件中定义
```

* test2 目录

```cmake
# test2 目录中的 CMakeLists.txt文件
cmake_minimum_required(VERSION 3.0)
project(SORTTEST)
aux_source_directory(./ SRC)
include_directories(${HEAD_PATH}) # 指定头文件路径
set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH}) # 指定可执行程序生成的路径，EXEC_PATH变量已在根节点文件中定义
link_directories(${LIB_PATH}) # 指定可执行程序要链接的动态库的路径
add_executable(${APP_NAME_2} ${SRC}) # 生成可执行程序
target_link_libraries(${APP_NAME_2} ${SORT_LIB}) # 指定可执行程序要链接的动态库的名字
```

**TIP：**在生成可执行程序的时候，动态库不会被打包到可执行程序内部。当可执行程序启动之后动态库也不会被加载到内存，==只有可执行程序调用了动态库中的函数的时候，动态库才会被加载到内存中，且多个进程可以共用内存中的同一个动态库==，所以动态库又叫**共享库**。

## 三、为什么要用CMake

最大一个原因就是**方便**，最开始的提到的一个有几十个文件的大工程，如果不用CMake工具，运行调试会变的十分麻烦，也不方便管理和维护。

* GCC编译多文件

  ```shell
  $ gcc -o main src/*.cpp -I ./include
  ```

源文件较多而且不在同一目录，并且头文件较多的情况下，一一罗列毫无疑问是非常麻烦的，要是不小心敲错再修改也很头大，这就充分体现出CMake的优势。

* CMake编译多文件

  ```shell
  $ cmake CMakeLists.txt文件所在路径
  $ make
  $ ./可执行程序名
  ```

  

  