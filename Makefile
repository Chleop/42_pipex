# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 16:48:04 by cproesch          #+#    #+#              #
#    Updated: 2021/10/30 14:13:26 by cproesch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= src/main.c src/find_path.c src/del_exit_utils.c src/process.c 

SRCS_B		= src_bonus/main_bonus.c src_bonus/find_path_bonus.c \
			src_bonus/del_exit_utils_bonus.c src_bonus/process_bonus.c \
			src_bonus/process_utils_bonus.c

OBJS		= $(SRCS:.c=.o)

OBJS_B		= $(SRCS_B:.c=.o)

NAME		= pipex

CC			= clang

IFLAGS		= -I. -Ilibft

CFLAGS		= -Wall -Wextra -Werror $(IFLAGS)

LFLAGS		= -Llibft -lft 

RM			= rm -rf

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

all:		$(NAME)

clean:	
			make -C libft -f Makefile clean
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			make -C libft -f Makefile fclean
			$(RM) $(NAME)

re:			fclean all

bonus:		$(OBJS_B)
			make -C libft
			$(CC) $(OBJS_B) $(LFLAGS) -o $(NAME)

.PHONY:		all clean fclean re