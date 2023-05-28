
CC=gcc
CFLAGS=-pedantic-errors -Wall -Wextra -g -pthread -shared -fPIC
FLAGS=-pedantic-errors -Wall -Wextra -g -pthread
OFLAGS=-Wall -c
DEBUG_FLAGS=-g
RELEASE=-DNDEBUG -O3
SRC_PATH = ../scheduler_by_heap/src/*.c src/libwd.c
LIB_PATH = $(CURDIR)/lib/
OBJS = ../scheduler_by_heap/src/*.o src/libwd.o
BIN_PATH = $(CURDIR)/bin/
CLIENT_PATH = $(CURDIR)/test/wd_client.c
WD_PATH = $(CURDIR)/src/wd.c
INCLUDES =-I./include/ -I../scheduler_by_heap/include/


TARGET= libwd.so
TARGET2 = client.out
TARGET3 = wd.out

all: $(TARGET) $(TARGET2) $(TARGET3)

release: CFLAGS+=$(RELEASE)
release: FLAGS+=$(RELEASE)
release: $(TARGET) $(TARGET2) $(TARGET3)
	

$(TARGET): $(SRC_PATH)
	$(CC) $(CFLAGS) $(SRC_PATH) -o $(LIB_PATH)$(TARGET) $(INCLUDES)

$(TARGET2): $(LIB_PATH)libwd.so $(CLIENT_PATH)
	$(CC) $(FLAGS) $(CLIENT_PATH) $(INCLUDES) -L./lib/ -lwd -o $(BIN_PATH)$(TARGET2) -Wl,-rpath=./lib

$(TARGET3): $(LIB_PATH)libwd.so $(WD_PATH)
	$(CC) $(FLAGS) $(WD_PATH) $(INCLUDES) -L$(LIB_PATH) -lwd -o $(BIN_PATH)$(TARGET3) -Wl,-rpath=./lib

run: 
	$(BIN_PATH)$(TARGET2)

vlg: 
	valgrind --leak-check=yes --track-origins=yes -s $(BIN_PATH)./$(TARGET2)

hel:
	valgrind --tool=helgrind -s $(BIN_PATH)./$(TARGET2)	
	
#debug: $(OBJS)
#	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJS) -o $(BIN_PATH)$(TARGET) $(INCLUDES)


	
clean:
	rm -f $(BIN_PATH)$(TARGET) *.o

