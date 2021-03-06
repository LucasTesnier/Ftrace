##
## EPITECH PROJECT, 2022
## ftrace
## File description:
## Makefile
##

CC 		= 	gcc

MAIN	=	src/main.c

FILES	=	src/ftrace_start.c 				\
			src/ftrace_error_handling.c		\
			src/utils.c						\
			src/ftrace_trace_command.c 		\
			src/ftrace_prepare_command.c 	\
			src/ftrace_prepare_path.c 		\
			src/ftrace_signals.c 			\
			src/ftrace_process_rip.c		\
			src/ftrace_received_signals.c 	\

ELFLIB	=	src/elf_lib/elf_open.c			\
			src/elf_lib/elf_adress.c

FUNC	=	src/function/function_init.c	\
			src/function/function_stack.c

SRC 	=	$(MAIN)		\
			$(FILES)	\
			$(ELFLIB)	\
			$(FUNC)

RM 		= 	rm -f

NAME 	= 	ftrace

CFLAGS 	= 	-Wall -Werror -I include/ -lelf

OBJ		=	$(SRC:.c=.o)

T_FILES	=	tests/ftrace_tests.c			\

SRC_T	=	$(FILES)	\
			$(ELFLIB)	\
			$(FUNC)		\
			$(T_FILES)

TFLAGS	=	-lcriterion --coverage

TEST_NAME	=	unit_tests

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)
	find . -name '*~' -delete -o -name '#*#' -delete -o -name '*.gcno' \
		-delete -o -name -'*.gcdo' -delete -o -name '*.gcda' -delete

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TEST_NAME)

re: fclean all

tests_run: CFLAGS += $(TFLAGS)
tests_run:
	gcc -o $(TEST_NAME) $(SRC_T) $(CFLAGS)
	./$(TEST_NAME)
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

dbg: CFLAGS = -g -I include/ -lelf
dbg: re

.PHONY: all clean fclean re dbg tests_run
