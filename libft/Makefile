# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 13:59:33 by laprieur          #+#    #+#              #
#    Updated: 2023/06/14 11:20:17 by laprieur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=	libft.a

#-------------------------------#
#          INGREDIENTS          #
#-------------------------------#

MANDATORY			:=	mandatory/ft_atoi.c					\
						mandatory/ft_bzero.c				\
						mandatory/ft_calloc.c				\
						mandatory/ft_isalnum.c				\
						mandatory/ft_isalpha.c				\
						mandatory/ft_isascii.c				\
						mandatory/ft_isdigit.c				\
						mandatory/ft_isprint.c				\
						mandatory/ft_itoa.c					\
						mandatory/ft_memchr.c				\
						mandatory/ft_memcmp.c				\
						mandatory/ft_memcpy.c				\
						mandatory/ft_memmove.c				\
						mandatory/ft_memset.c				\
						mandatory/ft_putchar_fd.c			\
						mandatory/ft_putendl_fd.c			\
						mandatory/ft_putnbr_fd.c			\
						mandatory/ft_putstr_fd.c			\
						mandatory/ft_split_utils.c			\
						mandatory/ft_split.c				\
						mandatory/ft_strchr.c				\
						mandatory/ft_strdup.c				\
						mandatory/ft_striteri.c				\
						mandatory/ft_strjoin.c				\
						mandatory/ft_strlcat.c				\
						mandatory/ft_strlcpy.c				\
						mandatory/ft_strlen.c				\
						mandatory/ft_strmapi.c				\
						mandatory/ft_strncmp.c				\
						mandatory/ft_strnstr.c				\
						mandatory/ft_strrchr.c				\
						mandatory/ft_strtrim.c				\
						mandatory/ft_substr.c				\
						mandatory/ft_tolower.c				\
						mandatory/ft_toupper.c				\

BONUS				:=	bonus/ft_lstadd_back_bonus.c		\
						bonus/ft_lstadd_front_bonus.c		\
						bonus/ft_lstclear_bonus.c			\
						bonus/ft_lstdelone_bonus.c			\
						bonus/ft_lstiter_bonus.c			\
						bonus/ft_lstlast_bonus.c			\
						bonus/ft_lstmap_bonus.c				\
						bonus/ft_lstnew_bonus.c				\
						bonus/ft_lstsize_bonus.c			\

ADD_ON				:=	add_on/ft_atod.c					\
						add_on/ft_atol.c					\
						add_on/ft_free_taboftab.c			\
						add_on/ft_isblank.c					\
						add_on/ft_isdouble.c				\
						add_on/ft_sort_int_tab.c			\
						add_on/ft_strcmp.c					\
						add_on/ft_strcspn.c					\
						add_on/ft_strspn.c					\
						add_on/ft_str_is_blank.c			\
						add_on/ft_tabdup.c					\
						
FT_PRINTF			:=	ft_printf/ft_printf.c				\
						ft_printf/ft_putadd.c				\
						ft_printf/ft_putchar.c				\
						ft_printf/ft_puthexa_base.c			\
						ft_printf/ft_puthexa_lower.c		\
						ft_printf/ft_puthexa_upper.c		\
						ft_printf/ft_putnbr.c				\
						ft_printf/ft_putstr.c				\
						ft_printf/ft_putunsignedint.c		\

MANDATORY_OBJS		:=	$(MANDATORY:%.c=.build/%.o)
BONUS_OBJS			:=	$(BONUS:%.c=.build/%.o)
ADD_ON_OBJS			:=	$(ADD_ON:%.c=.build/%.o)
FT_PRINTF_OBJS		:=	$(FT_PRINTF:%.c=.build/%.o)

DEPS				:=	$(MANDATORY_OBJS:%.o=%.d) $(BONUS_OBJS:%.o=%.d)		\
						$(ADD_ON_OBJS:%.o=%.d) $(FT_PRINTF_OBJS:%.o=%.d)	\

CC					:=	clang
CFLAGS				:=	-Wall -Wextra -Werror -g
CPPFLAGS			:=	-MP -MMD -Iinclude

#----------------------------#
#          UTENSILS          #
#----------------------------#

MAKEFLAGS			+= --silent --no-print-directory

#---------------------------#
#          RECIPES          #
#---------------------------#

all: $(NAME)

$(NAME): $(MANDATORY_OBJS) $(BONUS_OBJS) $(ADD_ON_OBJS) $(FT_PRINTF_OBJS)
	ar rcs $(NAME) $(MANDATORY_OBJS) $(BONUS_OBJS) $(ADD_ON_OBJS) $(FT_PRINTF_OBJS)
	$(info CREATED $(NAME))

.build/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $(CPPFLAGS) $< -o $@

-include $(DEPS)

clean:
	rm -rf .build

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

#------------------------#
#          SPEC          #
#------------------------#

.PHONY: all clean fclean re
.DELETE_ON_ERROR:
