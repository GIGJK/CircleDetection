all: compile

compile: circle.cpp
	@g++ circle.cpp -o circle `pkg-config --cflags --libs opencv`
	@echo "\033[1;33mCompile\033[0m -  \033[0;32msuccess\033[0m"
