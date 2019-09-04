.PHONY:all

all:dict_client dict_server

dict_client:dict_client.cc
	g++ dict_client.cc -o dict_client -std=c++11

dict_server:dict_server.cc
	g++ dict_server.cc -o dict_server -std=c++11

.PHONY:clean

clean:
	rm dict_client dict_server
