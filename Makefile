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
BONUS = access_bonus.c \
	chain_process_bonus.c \
	error_bonus.c \
	fd_fork_handle_bonus.c \
	gnl_bonus.c \
	heredoc_bonus.c \
	link_list_bonus.c \
	link_list_utils_bonus.c \
	pipex_bonus.c \
	process_bonus.c \
	utils_bonus.c

#============ TRANSFORM .c TO .o ============#
#============== MANDATORY PART ==============#
OBJM = $(SRCS:.c=.o)

#================ BONUS PART ================#
OBJB = $(BONUS:.c=.o)

#================= MAKE NAME ================#

LIBFT = Libft/libft.a

all : $(NAME)

$(LIBFT) :
	@ $(MAKE) -C Libft all

%.o : %.c pipex.h
	@ $(CC) $(FLAGS) -c $< -o $@

bonus : $(OBJB) $(LIBFT)
	$(CC) $(FLAGS) $(OBJB) $(LIBFT) -o $(NAME)

$(NAME) : $(OBJM) $(LIBFT)
	$(CC) $(FLAGS) $(OBJM) $(LIBFT) -o $(NAME)
	
clean :
	@ $(MAKE) -C Libft clean
	rm -rf $(OBJM) $(OBJB)

fclean :
	@ $(MAKE) -C Libft fclean
	rm -rf $(NAME) $(OBJM) $(OBJB)

re : fclean all

.PHONY : all clean fclean re bonus
