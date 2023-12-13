#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -g
#=================== NAME ===================#
NAME = pipex
#============= MANDATORY SOUCES =============#
SRCS = access.c \
	link_list.c \
	link_list_utils.c \
	pipex.c \
	utils.c \
	process.c \
	error.c \
	fd_fork_handle.c
#=============== BONUS SOURCES ==============#
#BONUS = 

#================= MAKE NAME ================#

LIBFT = Libft/libft.a

all : $(NAME)

make : 
	@: make -C Libft

make_clean : 
	@: make clean -C Libft

make_fclean : 
	@: make fclean -C Libft

make_re : 
	@: make re -C Libft
	
pipex_remove :
	@rm -rf $(NAME)

bonus : make
	$(CC) $(FLAGS) $(BONUS) $(LIBFT) -o $(NAME)

$(NAME) : make
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	
clean : make_clean pipex_remove

fclean : make_fclean pipex_remove

re : make_re pipex_remove all

.PHONY : all clean fclean re make make_clean make_fclean make_re pipex_remove
