CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
OBJECTS = simulator.o object.o echo_service_installer.o message_service_installer.o echo_service.o message_service.o manual_router.o host.o node.o link.o router.o link_installer.o service_installer.o bulk_send_service_installer.o bulk_send_service.o packet_sink_service_installer.o packet_sink_service.o

all: first second third forth

first: first.o $(OBJECTS)
	$(CC) $(CFLAGS) -o first first.o $(OBJECTS)

second: second.o $(OBJECTS)
	$(CC) $(CFLAGS) -o second second.o $(OBJECTS)

third: third.o $(OBJECTS)
	$(CC) $(CFLAGS) -o third third.o $(OBJECTS)

forth: forth.o $(OBJECTS)
	$(CC) $(CFLAGS) -o forth forth.o $(OBJECTS)

first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp

third.o: scenarios/third.cpp
	$(CC) $(CFLAGS) -c scenarios/third.cpp

forth.o: scenarios/forth.cpp
	$(CC) $(CFLAGS) -c scenarios/forth.cpp

simulator.o: simulator.cpp
	$(CC) $(CFLAGS) -c simulator.cpp

object.o: object.cpp
	$(CC) $(CFLAGS) -c object.cpp

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

bulk_send_service_installer.o: bulk_send_service_installer.cpp bulk_send_service_installer.h
	$(CC) $(CFLAGS) -c -o bulk_send_service_installer.o bulk_send_service_installer.cpp

bulk_send_service.o: bulk_send_service.cpp bulk_send_service.h
	$(CC) $(CFLAGS) -c -o bulk_send_service.o bulk_send_service.cpp

packet_sink_service_installer.o: packet_sink_service_installer.cpp packet_sink_service_installer.h
	$(CC) $(CFLAGS) -c -o packet_sink_service_installer.o packet_sink_service_installer.cpp

packet_sink_service.o: packet_sink_service.cpp packet_sink_service.h
	$(CC) $(CFLAGS) -c -o packet_sink_service.o packet_sink_service.cpp

clean:
	rm -f *.o *.exe first second third forth