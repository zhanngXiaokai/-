#最终的目标名
TARGET := ../BIN/main

#指定一个编译器
CC := arm-linux-g++

#找到我们的源文件夹 .c文件
#在当前路径下面找所有的.c文件
#CFILES := $(wildcard ../CODE/SRC/*.c ./*.c)
#CFILES := $(wildcard ../CODE/SRC/*.c)
CFILES += $(wildcard ../CODE/SRC/*.cpp)
#CFILES += $(wildcard ./*.c)
CFILES += $(wildcard ./*.cpp)

#去掉路径
CFILES := $(notdir $(CFILES))


#中间文件的名字  做模式替换
#将所有的.c模式替换为.o
#到这里为止 没有.o文件生成
#OBJS := $(patsubst %.c,../OBJ/%.o,$(CFILES))
OBJS := $(patsubst %.cpp,../OBJ/%.o,$(CFILES))

#头文件搜索路径
INCPATH := -I../CODE/INC
INCPATH += -I./
INCPATH += -I../LIB/inc

#库的搜索路径
LIBPATH := -L../LIB/lib

#库的名字
LIBFILES :=  -std=c++11
LIBFILES +=  -ljpeg
LIBFILES +=  -lpthread
#LIBFILES += -lLinkedListStack

#tftp 路径
TFTPPATH := ~/tftpboot


#最终的可执行文件依赖.o文件
#将所有的.o文件进行链接
$(TARGET) : $(OBJS)	
	$(CC)  $^ -o $@ $(INCPATH) $(LIBPATH) $(LIBFILES)
#	cp $(TARGET) $(TFTPPATH) 


#上面的OBJS只有名字没有文件  是不是要生成
#../OBJ/%.o : ../CODE/SRC/%.c
#	$(CC)  $< -o $@ $(INCPATH)

../OBJ/%.o : ../CODE/SRC/%.cpp
	$(CC) -c $< -o $@ $(INCPATH) $(LIBPATH) $(LIBFILES)

#../OBJ/%.o : ./%.c
#	$(CC) -g -Wall -c $< -o $@ $(INCPATH)

../OBJ/%.o : ./%.cpp
	$(CC) -c $< -o $@ $(INCPATH) $(LIBPATH) $(LIBFILES)

print:
	@echo $(CFILES)
	@echo $(OBJS)


#加标记 你make clean就来这里执行
clean:
	rm -rf $(OBJS) $(TARGET)






