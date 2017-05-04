##
## Makefile :D
##
## Made by David Zeng
## Login   <zeng_d@epitech.net>
##
## Started on  Mon Oct 12 13:31:18 2015 David Zeng
## Last update Sat Jul  2 21:56:26 2016 David Zeng
##

NAME :=		ftrace
SRCDIR :=	src/
INCLUDE :=	include/

SRC :=		main.c \
		fork_process.c \
		get_syscall_name.c \
		get_function_name.c \
		function_binary.c \
		function_dynamic.c \
		trace_process.c \
		trace_syscall.c \
		trace_function.c \
		trace_ret.c \
		get_indirect_address.c \
		stack_address.c \
		wait_signals.c \

CC :=		gcc
CFLAGS :=	-W -Wall -Wextra -g -l elf
SRC :=		$(addprefix $(SRCDIR), $(SRC))
OBJ :=		$(SRC:.c=.o)
RM :=		rm -f

DEFAULT :=	"\033[00;0m"
GREEN :=	"\033[0;32;1m"
RED :=		"\033[0;31;1m"
CYAN :=		"\033[0;36;1m"

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) && \
		echo -e $(GREEN)"[BIN]"$(CYAN) $(NAME)$(DEFAULT) || \
		echo -e $(RED)"[XX]"$(DEFAULT) $(NAME)
	for file in $(shell find . | cut -c 3- | grep -P ".*\.(cpp|hpp|c|h)"); \
		do fgrep -niH -e TODO -e FIXME $$file --color=auto; done; true
	[ -e /bin/deep ] && deep . || echo -n

clean:
	echo -e $(CYAN)"Cleaning $(NAME) tmp files..." $(DEFAULT)
	$(RM) $(OBJ)

fclean:	clean
	echo -e $(CYAN)"Cleaning $(NAME) executable..." $(DEFAULT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: all $(NAME) clean fclean re

%.o: %.c
	@$(CC) -c $< -o $@ $(CFLAGS) $(foreach dir, $(INCLUDE), -I$(dir)) && \
		echo -e $(GREEN)"[OK]"$(DEFAULT) $< || \
		echo -e $(RED)"[KO]"$(DEFAULT) $<
