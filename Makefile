PATH_LIBFT:= libft
LIBFT:= libft.a

PATH_PRINTF:= ft_printf
FT_PRINTF:= libftprintf.a

FLAGS:= -g -Wall -Werror -Wextra 

INCLUDES = -I./headers -I./libft -I./ft_printf

FILES_LIST:= src/ft_nm \
			src/utils

FUNCTIONS:= $(patsubst %, %.c, $(FILES_LIST))

FUNCTIONS_OBJ:= $(FUNCTIONS:.c=.o)

NAME:= ft_nm

all: $(NAME)

%.o: %.c 
	gcc -g $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(FUNCTIONS_OBJ)
	@$(MAKE) -C $(PATH_LIBFT)
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
	clear && ./ft_nm ft_nm

debug:
	clear && gdb --args ./ft_nm ft_nm

re: fclean all

.PHONY: all clean fclean re