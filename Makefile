CC:= gcc

PATH_LIBFT:= libft
LIBFT:= libft.a

PATH_PRINTF:= ft_printf_fd
FT_PRINTF:= libftprintffd.a

FLAGS:= -g -Wall -Werror -Wextra 

INCLUDES = -I./headers -I./libft -I./ft_printf_fd

YELLOW = "\e[93m"
BRIGHT_GREEN = "\e[1;92m"
RED = "\e[1;31m"
RESET = "\e[0m"

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
TEST:= ./ft_nm #./test/lib/lib1_x32.so #./test/binaries/bin2_x32 #./test/lib/lib1_x64.so #./src/ft_nm.o

all:
	@echo $(YELLOW) "Compiling..." $(RESET)
	@{ \
	    $(MAKE) --no-print-directory build > build.log 2>&1 & \
	    PID=$$!; \
	    while kill -0 $$PID 2>/dev/null; do \
	        echo $(YELLOW) "Compiling..." $(RESET); \
			sleep 0.8; \
	    done; \
	    wait $$PID; \
	    STATUS=$$?; \
	    if [ $$STATUS -eq 0 ]; then \
	        echo $(BRIGHT_GREEN) "ft_nm compiled successfully!" $(RESET); \
	        rm -f build.log; \
	    else \
	        echo $(RED) "Failed!" $(RESET); \
	        cat build.log; \
	        rm -f build.log; \
	        exit 1; \
	    fi \
	}

build: $(NAME)

%.o: %.c 
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(FUNCTIONS_OBJ)
	@$(MAKE) -C $(PATH_LIBFT) bonus
	@$(MAKE) -C $(PATH_PRINTF)
	@$(CC) $(FLAGS) $(FUNCTIONS_OBJ) $(PATH_LIBFT)/$(LIBFT) $(PATH_PRINTF)/$(FT_PRINTF) -o $(NAME)
	
clean:
	@{ \
		$(MAKE) --no-print-directory _clean > _clean.log 2>&1 & \
		PID=$$!; \
		wait $$PID; \
	    STATUS=$$?; \
	    if [ $$STATUS -eq 0 ]; then \
	        echo $(BRIGHT_GREEN) "ft_nm clean successful!" $(RESET); \
	        rm -f _clean.log; \
	    else \
	        echo $(RED) "Cleaning failed!" $(RESET); \
	        cat _clean.log; \
	        rm -f _clean.log; \
	        exit 1; \
	    fi \
	}

_clean:
	@$(MAKE) clean -C $(PATH_LIBFT)
	@$(MAKE) clean -C $(PATH_PRINTF)
	rm -f $(FUNCTIONS_OBJ)

fclean:
	@{ \
		$(MAKE) --no-print-directory _fclean > _fclean.log 2>&1 & \
		PID=$$!; \
		wait $$PID; \
	    STATUS=$$?; \
	    if [ $$STATUS -eq 0 ]; then \
	        echo $(BRIGHT_GREEN) "ft_nm full clean successful!" $(RESET); \
	        rm -f _fclean.log; \
	    else \
	        echo $(RED) "Full cleaning failed!" $(RESET); \
	        cat _fclean.log; \
	        rm -f _fclean.log; \
	        exit 1; \
	    fi \
	}

_fclean: clean
	@$(MAKE) fclean -C $(PATH_LIBFT)
	@$(MAKE) fclean -C $(PATH_PRINTF)
	@rm -f $(NAME)

run:
	@./ft_nm $(TEST) -a

nm:
	@clear && nm $(TEST) -a

diff_nm:
	clear && nm $(TEST) > ./out/t1 && nm -a $(TEST) > ./out/t2; \
	diff t1 t2 

debug:
	clear && gdb --args ./ft_nm $(TEST)

valgrind:
	clear && valgrind --leak-check=full ./ft_nm $(TEST)

test_ft_nm:
	clear && ./ft_nm $(TEST) > ./diff/ft_nm.txt

test_nm:
	clear & nm $(TEST) > ./diff/nm.txt

diff: test_nm test_ft_nm
	@diff ./diff/nm.txt ./diff/ft_nm.txt;	\
	echo $$?

re: fclean all

.PHONY: all clean fclean re