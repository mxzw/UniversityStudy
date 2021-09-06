all:test_server test_client 

test_server:server-t.cpp
	g++ $^ -o $@ -g -std=c++11 -lpthread
test_client:client-t.cpp
	g++ $^ -o $@ -g -std=c++11

