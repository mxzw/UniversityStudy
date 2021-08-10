all: test_server test_client1
test_server:server.cpp 
	g++ $^ -o $@ -g -std=c++11 -L . -ludp_static
test_client1:client1.cpp 
	g++ $^ -o $@ -g -std=c++11 -L . -ludp_static
