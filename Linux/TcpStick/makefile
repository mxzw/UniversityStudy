all:test_server test_client 

test_server:server.cpp
	g++ $^ -o $@ -g -std=c++11 -lpthread
test_client:client.cpp
	g++ $^ -o $@ -g -std=c++11

