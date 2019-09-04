.PHONY:all

all:server client

server:dict_server.cc
	g++ dict_server.cc -o server -std=c++11 -lpthread

client:dict_client.cc
	g++ dict_client.cc -o client -std=c++11

.PHONY:clean

clean:
	rm server client
