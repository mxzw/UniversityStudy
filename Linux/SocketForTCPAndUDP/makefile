all:server TcpClient1 TcpClient2 UdpClient1 UdpClient2
server:server.cpp
	g++ $^ -o $@ -g -lpthread
TcpClient1:TcpClient1.cpp
	g++ $^ -o $@ -g 
TcpClient2:TcpClient2.cpp
	g++ $^ -o $@ -g
UdpClient1:UdpClient1.cpp
	g++ $^ -o $@ -g 
UdpClient2:UdpClient2.cpp
	g++ $^ -o $@ -g 
