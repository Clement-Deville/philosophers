NAME = $(BIN_DIR)philo_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror

DEBUG = -g

SRCS_FILES =	main_bonus	\
				actions_bonus	\
				check_bonus	\
				clear_bonus	\
				create_philo_bonus	\
				do_continue_bonus	\
				errors_bonus	\
				forks_bonus	\
				global_monitoring_bonus	\
				init_bonus	\
				is_valid_arg_bonus	\
				print_bonus	\
				process_bonus	\
				pthreads_bonus	\
				pthread_for_one_bonus	\
				sem_utils	\
				time_bonus	\
				utils_bonus	\
				wait_bonus	\

INCLUDES_FILES = philosophers
SOURCE_DIR =	./src/
INCLUDES_DIR =	./include/
OBJS_DIR =		./obj/
BIN_DIR =		./bin/
TEST_DIR =		./test/
SOURCES =	$(addprefix $(SOURCE_DIR), $(addsuffix .c, $(SRCS_FILES)))
INCLUDES =	$(addprefix $(INCLUDES_DIR), $(addsuffix .h, $(INCLUDES_FILES)))
OBJS =		$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))

.PHONY: all clean fclean re bonus norminette

all: $(NAME)

bonus: $(NAME_B)

$(OBJS_DIR)%.o : $(SOURCE_DIR)%.c
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(DEBUG) -I$(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\e[0;32m\nLinking executable:\n\e[0m"
	$(CC) $(FLAGS) $(OBJS) $(DEBUG) -o $(NAME)
	@echo "\e[0;32m\nMandatory part compiled !\n\e[0m"

clean:
	@echo "\e[0;31m\nDeleting objects\n\e[0m"
	rm -rf $(OBJS_DIR)

fclean: clean
	@echo "\e[0;31m\nDeleting executable\n\e[0m"
	rm -rf $(BIN_DIR)

re: fclean all

norminette:
			@echo "\e[0;32m\nChecking .c norme:\n\e[0m"
			norminette ./src
			@echo "\e[0;32m\nChecking .h norme:\n\e[0m"
			norminette ./include
