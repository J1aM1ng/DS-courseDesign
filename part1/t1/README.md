* 源码分为三个项目（模块），分别是：
  * skipList：跳表 ADT 实现及正确性验证模块
  * rand：随机数及随机操作生成模块
  * expeSl：跳表维护动态数据效率实验模块
* 三个项目所含文件及功能：
  * skipList:
    * skiplist.h：跳表ADT的声明与实现（由于类模板的限制，跳表ADT的声明与实现无法分别分管在skiplist.h与skiplist.cpp文件中，故声明与实现均写在skiplist.h文件中）
    * main.cpp：用于验证跳表结构的正确性，导入示例数据集和自己生成的数据，将结果输出到文本文件中
  * rand：
    * main.cpp：生成随机数用于初始化跳表，生成随机操作用于对跳表进行大量操作，方便实验测时
  * expeSl：
    * skiplist.h：与skiplist项目中对应内容一致
    * main.cpp：根据rand项目生成的随机数初始化跳表，测定初态各种操作用时，再将rand项目生成的随机操作用于跳表，最后测定末态各种操作用时