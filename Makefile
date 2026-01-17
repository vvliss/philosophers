# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/30 14:00:49 by wilisson          #+#    #+#              #
#    Updated: 2026/01/17 20:50:07 by wilisson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := philo
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -pthread -I.
SRCDIR  := .
OBJDIR  := build

SRCS    := cleanup.c init.c main.c monitor.c parsing.c routine.c utils.c
OBJS    := $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
DEPS    := $(OBJS:.o=.d)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run
-include $(DEPS)