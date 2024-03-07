# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 17:48:39 by hsebille          #+#    #+#              #
#    Updated: 2023/06/15 13:35:48 by hsebille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=	minishell

#-------------------------------#
#          INGREDIENTS          #
#-------------------------------#

SRC				:=	src/builtins/builtins_utils_bis.c				\
					src/builtins/builtins_utils.c					\
					src/builtins/echo.c								\
					src/builtins/cd.c								\
					src/builtins/env.c								\
					src/builtins/export.c							\
					src/builtins/pwd.c								\
					src/builtins/unset.c							\
					src/builtins/exit.c								\
					src/exec/dup2.c									\
					src/exec/exec_utils_bis.c						\
					src/exec/exec_utils_ter.c						\
					src/exec/exec_utils_quater.c					\
					src/exec/exec_utils.c							\
					src/exec/exec.c									\
					src/expansion/expansion_utils.c					\
					src/expansion/expansion.c						\
					src/expansion/turbo_split_utils.c				\
					src/expansion/turbo_split.c						\
					src/features/heredoc.c							\
					src/features/prompt.c							\
					src/features/signals.c							\
					src/parsing/commands/commands_utils_bis.c		\
					src/parsing/commands/commands_utils_quater.c	\
					src/parsing/commands/commands_utils_quinquies.c	\
					src/parsing/commands/commands_utils_ter.c		\
					src/parsing/commands/commands_utils.c			\
					src/parsing/commands/commands.c					\
					src/parsing/syntax/syntax_utils.c				\
					src/parsing/syntax/syntax.c						\
					src/utils/list/cmd_list.c						\
					src/utils/list/env_list.c						\
					src/main.c										\

LIBFT			:=	libft/libft.a

SRC_OBJS		:=	$(SRC:%.c=.build/%.o)
DEPS			:=	$(SRC_OBJS:%.o=%.d)

CC				:=	clang
CFLAGS			:=	-Wall -Wextra -Werror -g
CPPFLAGS		:=	-MP -MMD -Iinclude -Ilibft/include
LDFLAGS			:=	-Llibft -lft -lreadline

#----------------------------#
#          UTENSILS          #
#----------------------------#

MAKEFLAGS		+= --silent --no-print-directory

#---------------------------#
#          RECIPES          #
#---------------------------#

all: $(LIBFT) $(NAME)

$(NAME): $(SRC_OBJS)
	$(CC) $(CFLAGS) $(SRC_OBJS) $(LDFLAGS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBFT):
	$(MAKE) -C $(dir $@)

.build/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $(CPPFLAGS) $< -o $@
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(MAKE) -C libft clean
	rm -rf .build

fclean: clean
	$(MAKE) -C libft fclean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------#
#          SPEC          #
#------------------------#

.PHONY: all clean fclean re $(LIBFT)
.DELETE_ON_ERROR:
