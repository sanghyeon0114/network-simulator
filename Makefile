CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

all: first second

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp

first: first.o echo_service_installer.o message_service_installer.o echo_service.o message_service.o manual_router.o host.o node.o link.o router.o link_installer.o service_installer.o
	$(CC) $(CFLAGS) -o first first.o echo_service_installer.o message_service_installer.o echo_service.o message_service.o manual_router.o host.o node.o link.o router.o link_installer.o service_installer.o

second: second.o echo_service_installer.o message_service_installer.o echo_service.o message_service.o manual_router.o host.o node.o link.o router.o link_installer.o service_installer.o
	$(CC) $(CFLAGS) -o second second.o echo_service_installer.o message_service_installer.o echo_service.o message_service.o manual_router.o host.o node.o link.o router.o link_installer.o service_installer.o

echo_service_installer.o: echo_service_installer.cpp echo_service_installer.h
	$(CC) $(CFLAGS) -c -o echo_service_installer.o echo_service_installer.cpp

message_service_installer.o: message_service_installer.cpp message_service_installer.h
	$(CC) $(CFLAGS) -c -o message_service_installer.o message_service_installer.cpp

echo_service.o: echo_service.cpp echo_service.h
	$(CC) $(CFLAGS) -c -o echo_service.o echo_service.cpp

message_service.o: message_service.cpp message_service.h
	$(CC) $(CFLAGS) -c -o message_service.o message_service.cpp

manual_router.o: manual_router.cpp manual_router.h
	$(CC) $(CFLAGS) -c -o manual_router.o manual_router.cpp

host.o: host.cpp host.h
	$(CC) $(CFLAGS) -c -o host.o host.cpp

node.o: node.cpp node.h
	$(CC) $(CFLAGS) -c -o node.o node.cpp

link.o: link.cpp link.h
	$(CC) $(CFLAGS) -c -o link.o link.cpp

router.o: router.cpp router.h
	$(CC) $(CFLAGS) -c -o router.o router.cpp

link_installer.o: link_installer.cpp link_installer.h
	$(CC) $(CFLAGS) -c -o link_installer.o link_installer.cpp

service_installer.o: service_installer.cpp service_installer.h
	$(CC) $(CFLAGS) -c -o service_installer.o service_installer.cpp

clean:
	rm -f *.o first second