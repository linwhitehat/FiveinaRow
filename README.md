# FiveinaRow
C++实现终端五子棋-中国科学院大学C++选修课（杨力祥）

## 声明

这是一份C++选修课的测评作业，可供借鉴思路和实现方法，不希望直接copy-paste。适合C++入门学习，尤其对类的思想进行充分理解具有一定帮助。

*这份代码是研一时期耗时一周完善的，比较粗糙，如有问题，欢迎交流。*

## 类的设计

1、棋盘类

棋盘类中的构造函数需要使用，棋盘一开始就要初始化

根据定义好的构建棋盘的样式，对数组类中定义的棋盘数组进行赋值，然后后续下棋的棋子变更都会在棋盘数组上做对应位子的内容修改

2、博弈类
当前步骤下的棋子为三角形或正方形，已下棋子为圆形
下棋的调用，需要刷新博弈情况

3、棋子类

棋子类包含棋子的样式，当前棋子样式和之前棋子样式，通过棋手调用时进行赋值当前下的位置，然后更新棋盘信息。

白方正常子：○    

白方刚落下之子：△

黑方正常字：●

黑方刚落下字：▲

4、裁判类

裁判类需要对限制规则进行判定还有进行胜负情况判定
在落子前进行审核和落子后进行审核

输入非法判定：
1、是否输入超出棋盘范围
2、是否输入为当前已落子位置

5、棋手类

对人人对战和人机对战模式的选择

6、IO（前端显示）类

进行界面显示和输入输出等调用，如博弈过程的调用

7、数据类

存储棋盘数组和棋子数据，以及棋谱数据

8、游戏类

作为基类的存在，统领其他类

## 使用

Five_in_a_Row.cpp为主函数所在程序文件，由此开始执行程序。

一共17份文件代码，包含头文件8份和9份cpp文件。

所在编译环境为VS下，无报错，直接运行exe文件，稍等一会便显示主界面，按照提示要求进行博弈即可。
