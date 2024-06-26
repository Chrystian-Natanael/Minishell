#! ******************************************************************************#
#                                   NAME                                         #
#! ******************************************************************************#

NAME = minishell
.DEFAULT_GOAL := all
.PHONY: all clean fclean re rebonus help
.SILENT:

#! ******************************************************************************#
#                                   COLORS                                       #
#! ******************************************************************************#

DEFAULT=\033[39m
BLACK=\033[30m
DARK_RED=\033[31m
DARK_GREEN=\033[32m
DARK_YELLOW=\033[33m
DARK_BLUE=\033[34m
DARK_MAGENTA=\033[35m
DARK_CYAN=\033[36m
LIGHT_GRAY=\033[37m
DARK_GRAY=\033[90m
RED=\033[91m
GREEN=\033[92m
ORANGE=\033[93m
BLUE=\033[94m
MAGENTA=\033[95m
CYAN=\033[96m
WHITE=\033[97m
YELLOW = \033[33m
RESET = \033[0m

#! ******************************************************************************#
#                                   PATH                                         #
#! ******************************************************************************#

SRCS_PATH = src/
INCS_PATH := includes/ libs/libft/include/ libs/garbage_collector/include/ tests/
BUILD_DIR := build/
BUILD_DIR_TEST := build/
BUILD_DIR_TEST_B := build/
LIBFT_DIR := libs/libft/
GARB_DIR := libs/garbage_collector/
TEST_DIR := tests/
TEST_B_DIR := tests/builtin/

#! ******************************************************************************#
#                                   FILES                                        #
#! ******************************************************************************#

SRCS =	$(addprefix $(SRCS_PATH),\
		1.init/main.c \
		1.init/envp.c \
		1.init/signals.c \
		2.parsing/syntax.c \
		2.parsing/cmd.c \
		2.parsing/lexer.c \
		2.parsing/expander.c \
		2.parsing/create_tokens.c \
		3.builtin/builtin.c \
		3.builtin/pwd.c \
		3.builtin/echo.c \
		3.builtin/env.c \
		3.builtin/exit.c \
		3.builtin/export.c \
		3.builtin/unset.c \
		3.builtin/cd.c \
		4.executor/binary_tree.c \
		4.executor/executor.c \
		4.executor/exec_and.c \
		4.executor/exec_or.c \
		4.executor/exec_pipe.c \
		4.executor/exec_sub_shell.c \
		4.executor/exec_redir.c \
		4.executor/exec_heredoc.c \
		5.utils/aux_utils.c \
		5.utils/export_utils.c \
		5.utils/lexer_utils.c \
		5.utils/main_utils.c \
		5.utils/path_envp_utils.c \
		5.utils/signal_utils.c \
		5.utils/executor_utils.c \
		5.utils/struct_utils.c \
		5.utils/cmd_utils.c \
		5.utils/is_utils.c \
		5.utils/lst_utils.c \
		5.utils/expand_utils.c)
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
GARB = $(addprefix $(GARB_DIR), garbage_collector.a)
LIBS := $(LIBFT_DIR)libft.a $(GARB_DIR)garbage_collector.a
OBJS = $(SRCS:%.c=$(BUILD_DIR)%.o)
OBJS_TEST = $(TEST:%.c=$(BUILD_DIR)%.o)
OBJS_TEST_B = $(TEST_B:%.c=$(BUILD_DIR)%.o)
DEPS = $(OBJS:.o=.d)
# DEPS = $(OBJS_TEST:.o=.d)

#! ******************************************************************************#
#                                    COMMANDS                                    #
#! ******************************************************************************#

MKDIR := mkdir -p
RM := rm -rf
SLEEP = sleep 0.1
CC = cc
SHELL := /bin/bash

#! ******************************************************************************#
#                                 FLAGS E COMP                                   #
#! ******************************************************************************#

CFLAGS = -Wall -Wextra -Werror -g3
DFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDLIBS = -ldl -pthread -lreadline
LDFLAGS = $(LIBFT_DIR)libft.a $(GARB_DIR)garbage_collector.a
CPPFLAGS = $(addprefix -I, $(INCS_PATH)) -MMD -MP
COMP_OBJ = $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
COMP_EXE = $(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
COMP_TEST = $(CC) $(OBJS_TEST) $(LDFLAGS) $(LDLIBS) -o $(NAME_TEST)
COMP_TEST_B = $(CC) $(OBJS_TEST_B) $(LDFLAGS) $(LDLIBS) -o $(NAME_TEST_B)

#! ******************************************************************************#
#                                  FUNCTIONS                                     #
#! ******************************************************************************#

define create_dir
	$(MKDIR) $(dir $@)
endef

define comp_objs
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	@if [ $(COUNT) -eq 1 ]; then \
		printf "$(YELLOW)Building MiniShell files\n$(RESET)"; \
	fi
	$(COMP_OBJ)
	$(SLEEP)
	printf "Compiling MiniShell$(YELLOW) %d%%\r$(FCOLOR)" $$(echo $$(($(COUNT) * 100 / $(words $(SRCS)))))
	@if [ $(COUNT) -eq $(words $(SRCS)) ]; then \
		printf " Compiled $(DARK_GREEN)MiniShell 100%%$(FCOLOR) ✅"; \
	fi
endef

define comp_objs_test
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	@if [ $(COUNT) -eq 1 ]; then \
		printf "$(YELLOW)Building Tester files\n$(RESET)"; \
	fi
	$(COMP_OBJ)
	$(SLEEP)
	printf "Compiling Tester$(YELLOW) %d%%\r$(FCOLOR)" $$(echo $$(($(COUNT) * 100 / $(words $(TEST)))))
	@if [ $(COUNT) -eq $(words $(TEST)) ]; then \
		printf " Compiled $(DARK_GREEN)Tester 100%%$(FCOLOR) ✅"; \
	fi
endef

define comp_objs_test_b
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	@if [ $(COUNT) -eq 1 ]; then \
		printf "$(YELLOW)Building Tester Builtin files\n$(RESET)"; \
	fi
	$(COMP_OBJ)
	$(SLEEP)
	printf "Compiling Tester Builtin$(YELLOW) %d%%\r$(FCOLOR)" $$(echo $$(($(COUNT) * 100 / $(words $(TEST)))))
	@if [ $(COUNT) -eq $(words $(TEST_B)) ]; then \
		printf " Compiled $(DARK_GREEN)Tester 100%%$(FCOLOR) ✅"; \
	fi
endef

define comp_libft
	printf "$(YELLOW)Building libft files\n$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)
endef

define comp_exe
	$(COMP_EXE)
	printf "\n \n"
	printf "$(DARK_BLUE)MiniShell $(RESET)$(PURPLE)is Ready\n$(RESET)"
endef

define comp_garb
	printf "$(YELLOW)Building garb files\n$(RESET)"
	$(MAKE) -C $(GARB_DIR)
endef

define comp_tests
	$(COMP_TEST)
	printf "\n \n"
	printf "$(DARK_BLUE)Tester $(RESET)$(PURPLE)is Ready\n$(RESET)"
endef

define comp_tests_b
	$(COMP_TEST_B)
	printf "\n \n"
	printf "$(DARK_BLUE)Tester Builtin $(RESET)$(PURPLE)is Ready\n$(RESET)"
endef

define help
	printf "${DARK_RED}Available targets:${RESET}"
	printf "\n"
	printf "\n"
	printf "$(DARK_BLUE)all:${RESET}		${LIGHT_GRAY}Build $(ORANGE)MiniShell${RESET}\n"
	printf "${DARK_BLUE}bonus:${RESET}		${LIGHT_GRAY}Build $(ORANGE)MiniShell ${LIGHT_GRAY}Bonus${RESET}\n"
	printf "${DARK_BLUE}test:${RESET}		$(LIGHT_GRAY)Build $(ORANGE)Tester${RESET}\n"
	printf "${DARK_BLUE}re:${RESET}			$(CYAN)Rebuild ${LIGHT_GRAY}the program${RESET}\n"
	printf "${DARK_BLUE}rebonus:${RESET}	$(CYAN)Rebuild ${LIGHT_GRAY}the program bonus${RESET}\n"
	printf "${DARK_BLUE}retest:${RESET}		$(CYAN)Rebuild ${LIGHT_GRAY}the program test${RESET}\n"
	printf "${DARK_BLUE}clean:${RESET}		$(RED)Remove ${LIGHT_GRAY}the object files${RESET}\n"
	printf "${DARK_BLUE}fclean:${RESET}		$(RED)Remove ${LIGHT_GRAY}the program and the object files${RESET}\n"
endef

#! ******************************************************************************#
#                                   TARGETS                                      #
#! ******************************************************************************#

all: $(LIBFT) $(GARB) $(NAME)

$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	$(call comp_objs)

$(NAME): $(OBJS)
	$(call comp_exe)

$(LIBFT):
	$(call comp_libft)

$(GARB):
	$(call comp_garb)

clean:
	$(RM) $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_TEST)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GARB_DIR) fclean

val: readline.supp all
		@valgrind -q --suppressions=readline.supp \
								--leak-check=full \
								--show-leak-kinds=all \
								--track-origins=yes \
								--track-fds=yes \
								--trace-children=yes \
								--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
								./${NAME}

readline.supp:
		@echo '{' > $@
		@echo '   ignore_libreadline_memory_errors' >> $@
		@echo '   Memcheck:Leak' >> $@
		@echo '   ...' >> $@
		@echo '   obj:*/libreadline.so.*' >> $@
		@echo '}' >> $@

re: fclean all

rebonus: fclean bonus

retest: fclean test

help:
	$(call help)

-include $(DEPS)
