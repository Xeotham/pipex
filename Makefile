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
	utils.c
#=============== BONUS SOURCES ==============#
# BONUS = 

#================= MAKE NAME ================#

LIBFT = Libft/libft.a

all : $(NAME)

make : 
	@(cd Libft && make )

make_clean : 
	@( cd Libft && make clean )

make_fclean : 
	@( cd Libft && make fclean )

make_re : 
	@( cd Libft && make re )
	
pipex_remove :
	@rm -rf $(NAME)

$(NAME) : make
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	
clean : make_clean pipex_remove

fclean : make_fclean pipex_remove

re : make_re pipex_remove all

.PHONY : all clean fclean re make make_clean make_fclean make_re pipex_remove
