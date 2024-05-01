#! ******************************************************************************#
#                                   NAME                                         #
#! ******************************************************************************#

NAME = minishell
NAME_TEST = test
.DEFAULT_GOAL := all
.PHONY: all clean fclean re rebonus help test retest
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
INCS_PATH := includes/ libs/libft/include/ libs/garbage_collector/include/
BUILD_DIR := build/
BUILD_DIR_TEST := build/
LIBFT_DIR := libs/libft/
GARB_DIR := libs/garbage_collector/
TEST_DIR := tests/

#! ******************************************************************************#
#                                   FILES                                        #
#! ******************************************************************************#

SRCS =	$(addprefix $(SRCS_PATH),\
		main.c \
		lexer.c \
		utils.c)
TEST = $(addprefix $(TEST_DIR),\
		test_lexer.c) $(addprefix $(SRCS_PATH),\
		lexer.c \
		utils.c)
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
GARB = $(addprefix $(GARB_DIR), garbage_collector.a)
LIBS := $(LIBFT_DIR)libft.a $(GARB_DIR)garbage_collector.a
OBJS = $(SRCS:%.c=$(BUILD_DIR)%.o)
OBJS_TEST = $(TEST:%.c=$(BUILD_DIR)%.o)
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
LDLIBS = -ldl -lglfw -pthread -lreadline
LDFLAGS = $(LIBFT_DIR)libft.a $(GARB_DIR)garbage_collector.a 
CPPFLAGS = $(addprefix -I, $(INCS_PATH)) -MMD -MP
COMP_OBJ = $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
COMP_EXE = $(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
COMP_TEST = $(CC) $(OBJS_TEST) $(LDFLAGS) $(LDLIBS) -o $(NAME_TEST)

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

define help
	printf "${DARK_RED}Available targets:${RESET}"
	printf "\n"
	printf "\n"
	printf "$(DARK_BLUE)all:${RESET}		${LIGHT_GRAY}Build $(ORANGE)MiniShell${RESET}\n"
	printf "${DARK_BLUE}bonus:${RESET}		${LIGHT_GRAY}Build $(ORANGE)MiniShell ${LIGHT_GRAY}Bonus${RESET}\n"
	printf "${DARK_BLUE}test:${RESET}		$(LIGHT_GRAY)Build $(ORANGE)Tester${RESET}\n"
	printf "${DARK_BLUE}re:${RESET}		$(CYAN)Rebuild ${LIGHT_GRAY}the program${RESET}\n"
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

$(BUILD_DIR_TEST)%.o: %.c
	$(call create_dir)
	$(call comp_objs_test)

$(NAME): $(OBJS)
	$(call comp_exe)

$(LIBFT):
	$(call comp_libft)

$(GARB):
	$(call comp_garb)

test: $(LIBFT) $(GARB) $(OBJS_TEST)
	$(call comp_tests)
clean:
	$(RM) $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_TEST)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GARB_DIR) fclean

re: fclean all

rebonus: fclean bonus

retest: fclean test

help:
	$(call help)

-include $(DEPS)
