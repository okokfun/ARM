本实验为新建工程实验，仅供大家新建工程时参考。

Email: linguangyuan88@icloud.com
	   2643989637@qq.com
QQ:	   2643989637

1. Boot放置汇编启动文件
2. Doc项目说明文档
3. Hardware存放硬件驱动
4. Interrupt放置包含中断处理程序，主要中断服务程序。
5. Lib外设驱动库
6. List汇编文件
7. Obj中间文件和目标文件
8. Project项目启动文件夹
9. Core放置内核和系统及时钟初始化文件
10. User放置开发者写的源文件

keilkilll.bat为删除编译的中间代码批处理脚本文件

各种芯片宏定义：
	USE_STDPERIPH_DRIVER,STM32F40XX
						,STM32F40_41xxx
						,STM32F427_437xx
						,STM32F429_439xx
						,STM32F401xx
						,STM32F410xx
						,STM32F411xE
						,STM32F412xG
						,STM32F413_423xx
						,STM32F446xx
						,STM32F469_479xx
						其中 USE_STDPERIPH_DRIVER 为必添加，芯片组按照实物添加，中间间隔为英文逗号-> ,