���벽�裺
$qmake -project
$qmake
$make

ע������ʱ���ܳ��ֵ����⣺
�١�
can/socketcan.cpp: In member function 'void SocketCAN::slotOnBtnConnectClicked()':
can/socketcan.cpp:141: error: 'PF_CAN' was not declared in this scope
can/socketcan.cpp:153: error: 'AF_CAN' was not declared in this scope
make: *** [socketcan.o] ���� 1

����취��
��Makfile��INCPATH����������������ݣ�-I/usr/include

�ڡ�
change.o: In function `Change::rewrite()':
change.cpp:(.text+0x7d8): undefined reference to `sqlite3_exec'
deletestu.o: In function `Deletestu::deldt()':
deletestu.cpp:(.text+0x70): undefined reference to `sqlite3_get_table'
...
...
make: *** [qtdemo1] ���� 1

����취��
��Makfile��LIBS����������������ݣ�-lsqlite3
ע�⣺ǰ����ʹ�õĽ������������sqlite3�����ͷ�ļ��Ϳ⡣��sqlite3�Ľ��������ο��������ϣ�
