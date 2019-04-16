# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrari <tferrari@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/13 16:44:11 by tferrari          #+#    #+#              #
#    Updated: 2019/04/16 15:46:01 by tferrari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: libft

NAME = ft_ssl

SRC_DIR = src

SRC_FILE =	main.c md5.c error.c sha256.c option.c write.c intchar.c \
			update_h.c intchar_64.c sha224.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE))

OBJS_DIR = obj

OBJS = $(addprefix $(OBJS_DIR)/, $(SRC_FILE:.c=.o))

INC = -ILibft/include -Iincludes

LFT = -L./Libft -lft

FLAGS = -Wall -Werror -Wextra

all : libft $(NAME)

$(NAME): $(OBJS)
	@gcc $(LFT) -o $(NAME) $(OBJS) $(FLAGS)
	@echo "\033[32mexecutable ft_ssl créé\033[0m"

libft:
	make -C Libft/

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@gcc $(INC) -o $@ -c $< $(FLAGS)
	@echo "Fichier" $< "recompilé."

clean:
	@rm -rf $(OBJS_DIR)
	@make -C Libft clean
	@echo "\033[31mFichier objet de ft_ssl supprimé\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f Libft/libft.a
	@echo "\033[31mLibft.a supprimé\033[0m"
	@echo "\033[31mft_ssl supprimé\033[0m"

re: fclean all
