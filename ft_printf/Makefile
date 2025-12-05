FLAGS:= -Wall -Werror -Wextra

NAME:= libftprintf.a

FILES:= ft_printf \
		ft_strlen \
		ft_putchar \
		ft_putstr \
		ft_putnbr \
		ft_putnbr_base \
		ft_putptr \
		ft_put_unsigned \
		ft_count_digits \

OBJECTS:= $(patsubst %, %.o, $(FILES))

all: $(NAME)
	
$(NAME):
	gcc $(FLAGS) -c $(patsubst %, %.c, $(FILES))
	ar -rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

clean: 
	rm -f $(patsubst %, %.o, $(FILES)) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus