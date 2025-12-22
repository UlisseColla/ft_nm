PATH_LIBFT:= libft
LIBFT:= libft.a

PATH_PRINTF:= ft_printf_fd
FT_PRINTF:= libftprintffd.a

FLAGS:= -g -Wall -Werror -Wextra 

INCLUDES = -I./headers -I./libft -I./ft_printf_fd

FILES_LIST:= src/main \
			src/ft_nm \
			src/utils \
			src/args_lexer \
			src/print \
			src/set_flag \
			src/quick_sort

FUNCTIONS:= $(patsubst %, %.c, $(FILES_LIST))

FUNCTIONS_OBJ:= $(FUNCTIONS:.c=.o)

NAME:= ft_nm
TEST:= ft_nm #./test/lib/lib1_shname_corrupted_x64.so #./src/ft_nm.o

all: $(NAME)

%.o: %.c 
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(FUNCTIONS_OBJ)
	@$(MAKE) -C $(PATH_LIBFT) bonus
	@$(MAKE) -C $(PATH_PRINTF)
	gcc $(FLAGS) $(FUNCTIONS_OBJ) $(PATH_LIBFT)/$(LIBFT) $(PATH_PRINTF)/$(FT_PRINTF) -o $(NAME)
	@echo "Compiled successfully!"
	
clean:
	@$(MAKE) clean -C $(PATH_LIBFT)
	@$(MAKE) clean -C $(PATH_PRINTF)
	rm -f $(FUNCTIONS_OBJ)
	@echo "Clean done"

fclean: clean
	@$(MAKE) fclean -C $(PATH_LIBFT)
	@$(MAKE) fclean -C $(PATH_PRINTF)
	rm -f $(NAME)
	@echo "Full clean done"

run:
	clear && ./ft_nm $(TEST) #> ./diff/ft_nm.txt

debug:
	clear && gdb --args ./ft_nm $(TEST)

valgrind:
	clear && valgrind ./ft_nm $(TEST)

nm: 
	clear & nm $(TEST) #> ./diff/nm.txt

diff: nm run
	@diff ./diff/nm.txt ./diff/ft_nm.txt;	\
	echo $$?

re: fclean all

.PHONY: all clean fclean re