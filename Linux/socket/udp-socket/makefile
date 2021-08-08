all:test_client1 test_server test_client2

test_client1:client1.cpp
	g++ $^ -o $@ -g -std=c++11
test_server:server.cpp
	g++ $^ -o $@ -g -std=c++11
test_client2:client2.cpp
	g++ $^ -o $@ -g -std=c++11
