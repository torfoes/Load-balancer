CC = g++
CFLAGS = -Wall -std=c++11

SRCS = LoadBalancer.cpp Request.cpp RequestQueue.cpp WebServer.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = server

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
