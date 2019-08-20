编译步骤：
$qmake -project
$qmake
$make

注，编译时可能出现的问题：
①、
can/socketcan.cpp: In member function 'void SocketCAN::slotOnBtnConnectClicked()':
can/socketcan.cpp:141: error: 'PF_CAN' was not declared in this scope
can/socketcan.cpp:153: error: 'AF_CAN' was not declared in this scope
make: *** [socketcan.o] 错误 1

解决办法：
在Makfile的INCPATH参数中添加以下内容：-I/usr/include

②、
change.o: In function `Change::rewrite()':
change.cpp:(.text+0x7d8): undefined reference to `sqlite3_exec'
deletestu.o: In function `Deletestu::deldt()':
deletestu.cpp:(.text+0x70): undefined reference to `sqlite3_get_table'
...
...
make: *** [qtdemo1] 错误 1

解决办法：
在Makfile的LIBS参数中添加以下内容：-lsqlite3
注意：前提是使用的交叉编译器中有sqlite3的相关头文件和库。（sqlite3的交叉编译请参考网络资料）
