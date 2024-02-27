#================ COMPILATOR ================#
CC = cc
#=================== FLAGS ==================#
FLAGS = -Wall -Wextra -Werror -g
#=================== NAME ===================#
NAME = pipex
#============= MANDATORY SOUCES =============#
SRCS = SRCS/access.c \
	SRCS/link_list.c \
	SRCS/link_list_utils.c \
	SRCS/pipex.c \
	SRCS/utils.c \
	SRCS/process.c \
	SRCS/error.c \
	SRCS/fd_fork_handle.c

#=============== BONUS SOURCES ==============#
BONUS = BONUS/access_bonus.c \
	BONUS/chain_process_bonus.c \
	BONUS/error_bonus.c \
	BONUS/fd_fork_handle_bonus.c \
	BONUS/gnl_bonus.c \
	BONUS/heredoc_bonus.c \
	BONUS/link_list_bonus.c \
	BONUS/link_list_utils_bonus.c \
	BONUS/pipex_bonus.c \
	BONUS/process_bonus.c \
	BONUS/utils_bonus.c

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
