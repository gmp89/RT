# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/15 00:09:57 by ebaudet           #+#    #+#              #
#    Updated: 2014/03/27 21:14:03 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= RT
FILES	= env.c error.c image.c main.c rtv1.c sphere.c vector.c ray.c hook.c \
		data.c vector_calculation.c color.c light.c intersection.c plan.c \
		parse.c cylinder.c normal.c tools.c ft_scene_init.c ft_set_sphere.c \
		ft_set_plan.c ft_set_light.c ft_set_cylinder.c cone.c ft_set_cone.c \
		color_effect.c color_calculation.c pixel_color.c \
		vector_calculation2.c ft_set_ref.c
SRCS	= $(addprefix srcs/, $(FILES))
OBJS	= $(SRCS:srcs/%.c=.obj/%.o)
INC		= -I includes -I libft/includes
FLAGS	= -Wall -Wextra -Werror
LIB		= -L libft -lft
LIBMLX	= -L /usr/X11/lib -lmlx -lXext -lX11
CC		= cc

all: $(NAME)

$(NAME): libft_comp create_fold_obj $(OBJS)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) $(LIBMLX)
	@echo "\n > \033[36m$(NAME)\033[m project compilation [\033[32mDONE\033[m]\n"

.obj/%.o: srcs/%.c
	@$(CC) -c $< -o $@ $(FLAGS) $(INC)
	@echo -n .

libft_comp:
	@make -C libft

create_fold_obj:
	@mkdir -p .obj

clean:
	@rm -rf .obj

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "fclean : [\033[32mDONE\033[m]"

re: fclean all

gdb: libft_comp
	cc -g $(FLAGS) $(SRCS) -o $(NAME) $(INC) $(LIB) $(LIBMLX)
	gdb $(NAME)

.PHONY: all libft_comp create_fold_obj clean fclean re
