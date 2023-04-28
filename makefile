CC = g++

all: analysis

analysis: main.cpp function.cpp
	@echo "\033[1;33mCompiling...\033[0m"  
	@$(CC) -o $@ $< 
	@echo "\033[1;32mDone. \033[0m "
	@echo "\033[1;32mEnter the prompt \033[0m\033[1;36m./$<\033[0m\033[1;32m or \033[0m\033[1;36mmake run\033[0m\033[1;32m to execute the program. \033[0m"

run: 
	@./analysis

clean: 
	@rm -rf analysis
	@echo "\033[1;31m$ analysis is deleted. \033[0m"

again:
	@rm -rf analysis
	@$(CC) -o analysis main.cpp functions.cpp interface.cpp

	
	




