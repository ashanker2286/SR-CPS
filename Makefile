CC = gcc
CFLAGS = -Wall -g -O0
CFLAGS += -I. -I/usr/include/
LDFLAGS = -L/usr/lib/x86_64-linux-gnu/ -lsonic_object_library

#targets
all: cps

cps: intf.o vlan.o cps.o
	$(CC) -o cps cps.o vlan.o intf.o $(LDFLAGS)

cps.o: cps.c
	$(CC) $(CFLAGS) -c cps.c

intf.o: intf.c
	$(CC) $(CFLAGS) -c intf.c

vlan.o: vlan.c
	$(CC) $(CFLAGS) -c vlan.c

clean:
	rm -rf *.o cps