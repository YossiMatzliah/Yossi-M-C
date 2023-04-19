CC=gcc -ansi -pedantic-errors -Wall -Wextra $(INCLUDE_PATH)
INCLUDE_PATH=-I./include/
SRC_PATH=$(CURDIR)/src/
TEST_PATH=$(CURDIR)/test/
BIN_PATH=$(CURDIR)/bin/

#DS_SRC_PATH=../../ds/src/

WSNAME=sched
MORESRC=$(SRC_PATH)task
MORESRC1=$(SRC_PATH)uid
MORESRC2=$(SRC_PATH)pq_by_heap
MORESRC3=$(SRC_PATH)heap
MORESRC4=$(SRC_PATH)dynamic_vector
OBJS=$(TEST_PATH)$(WSNAME)_test.o $(SRC_PATH)$(WSNAME).o $(MORESRC).o $(MORESRC1).o $(MORESRC2).o $(MORESRC3).o $(MORESRC4).o
SRCS=$(TEST_PATH)$(WSNAME)_test.c $(SRC_PATH)$(WSNAME).c $(MORESRC).c $(MORESRC1).c $(MORESRC2).c $(MORESRC3).c $(MORESRC4).c

TARGET = $(WSNAME)

$(TARGET): $(SRCS)  
	$(CC) -g $(SRCS) -o $(BIN_PATH)$(TARGET) $(INCLUDE_PATH) 
debug: $(OBJS) 
	$(CC) -g $(SRCS) -o $(BIN_PATH)$(TARGET) $(INCLUDE_PATH)
release: $(SRCS)	
	$(CC) -DNDEBUG $(SRCS) -o $(BIN_PATH)$(TARGET) $(INCLUDE_PATH)
	rm $(OBJS)	
obj: $(SRCS) 
	$(CC) -g $(SRCS) -o $(BIN_PATH)$(TARGET) $(INCLUDE_PATH) 	 
.PHONY: run
run:
	$(BIN_PATH)./$(TARGET) 
.PHONY : clean
clean:
	rm $(BIN_PATH)$(TARGET) $(OBJS) 
all: $(TARGET) run clean		

vlg: 
	valgrind --leak-check=yes --track-origins=yes -s $(BIN_PATH)./$(TARGET)
