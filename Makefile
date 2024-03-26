# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhotchki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 11:38:53 by jhotchki          #+#    #+#              #
#    Updated: 2024/02/04 11:38:55 by jhotchki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME := client
SERVER_NAME := server
CLIENT_BONUS_NAME := client_bonus
SERVER_BONUS_NAME := server_bonus

CLIENT_SRCS := client.c print_utils.c utils.c
SERVER_SRCS := server.c print_utils.c utils.c
CLIENT_BONUS_SRCS := client_bonus.c print_utils_bonus.c utils_bonus.c
SERVER_BONUS_SRCS := server_bonus.c print_utils_bonus.c utils_bonus.c

CLIENT_OBS := client.o print_utils.o utils.o 
SERVER_OBS := server.o print_utils.o utils.o
CLIENT_BONUS_OBS := client_bonus.o print_utils_bonus.o utils_bonus.o
SERVER_BONUS_OBS := server_bonus.o print_utils_bonus.o utils_bonus.o

LIBFT_PATH = libft
LIBFT_ARCH = $(LIBFT_PATH)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror

RM := rm -f
MAKEFLAGS += --no-print-directory

COLOR_RESET = \033[0m
COLOR_GREEN = \033[1;92m 

define print_colored
	@echo "$(COLOR_GREEN)$(1)$(COLOR_RESET) $(2)"
endef

.SILENT:

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBS) $(LIBFT_ARCH)
	$(CC) $^ -L$(LIBFT_PATH) -lft -o $@
	$(call print_colored, "[SUCCESS]", "$(CLIENT_NAME) ready")

$(SERVER_NAME): $(SERVER_OBS) $(LIBFT_ARCH)
	$(CC) $^ -L$(LIBFT_PATH) -lft -o $@	
	$(call print_colored, "[SUCCESS]", "$(SERVER_NAME) ready")

$(LIBFT_ARCH):
	$(MAKE) -C $(LIBFT_PATH)

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

$(CLIENT_BONUS_NAME): $(CLIENT_BONUS_OBS) $(LIBFT_ARCH)
	$(CC) $^ -L$(LIBFT_PATH) -lft -o $@
	$(call print_colored, "[SUCCESS]", "$(CLIENT_BONUS_NAME) ready")

$(SERVER_BONUS_NAME): $(SERVER_BONUS_OBS) $(LIBFT_ARCH)
	$(CC) $^ -L$(LIBFT_PATH) -lft -o $@	
	$(call print_colored, "[SUCCESS]", "$(SERVER_BONUS_NAME) ready")

clean: 
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(CLIENT_OBS)
	$(RM) $(SERVER_OBS)
	$(RM) $(CLIENT_BONUS_OBS)
	$(RM) $(SERVER_BONUS_OBS)

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(CLIENT_NAME)
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_BONUS_NAME)
	$(RM) $(SERVER_BONUS_NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
