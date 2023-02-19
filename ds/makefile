CC=gcc -ansi -pedantic-errors -Wall -Wextra
INCLUDE_PATH=-I /home/yossi/git/ds/include/
SRC_PATH=/home/yossi/git/ds/src/
TEST_PATH=/home/yossi/git/ds/test/

WSNAME=dll
#MORESRC=$(SRC_PATH)dll
OBJS=$(TEST_PATH)$(WSNAME)_test.o $(SRC_PATH)$(WSNAME).o #$(MORESRC).o
SRCS=$(TEST_PATH)$(WSNAME)_test.c $(SRC_PATH)$(WSNAME).c #$(MORESRC).c

obj_test =  $(WSNAME)_test.o 
obj_src = $(WSNAME).o
TARGET = $(WSNAME)

$(TARGET): $(OBJS)  
	$(CC) $(SRCS) -g -o $(TARGET) $(INCLUDE_PATH) 
	rm $(OBJS) 
debug: $(OBJS) 
	$(CC) -g -O3 $(SRCS) -o $(TARGET) $(INCLUDE_PATH)		
obj: $(OBJS) 
	$(CC) -g $(SRCS) -o $(TARGET) $(INCLUDE_PATH)  	 
.PHONY: run
run:
	./$(TARGET) 
.PHONY : clean
clean:
	rm $(TARGET) $(OBJS) 
all: $(TARGET) run clean		

vlg: 
	valgrind --leak-check=yes --track-origins=yes -s ./$(TARGET)
