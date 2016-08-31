SRCSDIR=	./src/
SRCS=	$(wildcard $(SRCSDIR)*.c) $(wildcard $(SRCSDIR)*.h)
OBJS=	$(SRCS:.c=.o)
BINDIR=	./bin/
TARGET=	minGC
CC=	gcc
CFLAGS=	-O3 

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $(BINDIR)$(TARGET) $(wildcard $(BINDIR)*.o) $(LDFLAGS) $(CFLAGS)

.c.o:
	$(CC) -c -w $< -o $(BINDIR)$(notdir $*).o

debug:
	$(CC) -o $(BINDIR)$(TARGET)  -g $(SRCS) $(LDFLAGS) -O0

drun:
	lldb $(BINDIR)$(TARGET)

run:
	$(BINDIR)$(TARGET)

clean:
	rm -rf $(wildcard $(BINDIR)*.o) $(BINDIR)$(TARGET) $(BINDIR)*.o *.d *.dSYM
