# *********************************************** #
#      ____  ____ ___  ____ _____  ____ ______    #
#     / __ \/ __ `__ \/ __ `/ __ \/ __ `/ ___/    #
#    / /_/ / / / / / / /_/ / / / / /_/ / /        #
#    \____/_/ /_/ /_/\__,_/_/ /_/\__,_/_/         #
#                                                 #
#    Makefile                                     #
#    By: omanar <omanar@student.1337.ma>          #
#    Created: 2022/04/24 23:32:00 by omanar       #
#                                                 #
# *********************************************** #

NAME	=	pipex
PIPEX_B	=	pipex_bonus
CC		=	gcc
RM		=	rm -f
LIBFT	=	libft/libft.a

SRCS	=	srcs/pipex.c srcs/pipex_utils.c srcs/pipex_utils_2.c $(LIBFT)
OBJS	=	$(SRCS:.c=.o)
SRCS_B	=	srcs/pipex_bonus.c srcs/pipex_utils.c srcs/pipex_utils_2.c $(LIBFT)
OBJS_B	=	$(SRCS_B:.c=.o)

define HEADER_M
       .__                       
______ |__|_____   ____ ___  ___ 
\____ \|  \____ \_/ __ \\\  \/  /
|  |_> >  |  |_> >  ___/ >    <  
|   __/|__|   __/ \___  >__/\_ \ 
|__|      |__|        \/      \/ 
endef
export HEADER_M

define HEADER_B
       .__                          ___.                                
______ |__|_____   ____ ___  ___    \_ |__   ____   ____  __ __  ______ 
\____ \|  \____ \_/ __ \\\  \/  /     | __ \ /  _ \ /    \|  |  \/  ___/
|  |_> >  |  |_> >  ___/ >    <      | \_\ (  <_> )   |  \  |  /\___ \  
|   __/|__|   __/ \___  >__/\_ \_____|___  /\____/|___|  /____//____  > 
|__|      |__|        \/      \/_____/   \/            \/           \/  
endef
export HEADER_B

all: header_m $(NAME)

header_m:
	@echo "\033[0;32m$$HEADER_M\033[0m\n"

header_b:
	@echo "\033[0;32m$$HEADER_B\033[0m\n"

%.o: %.c
	@ $(CC) -Wall -Wextra -Werror -c $< -o $@

$(LIBFT):
	@echo "\033[0;36m</ Compiling libft >\033[0m"
	@make -C libft

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[0;36m</ Compiling pipex >\033[0m"
	@$(CC) $(OBJS) -o $(NAME)
	@echo "\033[1;32mPipex has been compiled!\033[0m\n"

$(PIPEX_B): $(OBJS_B) $(LIBFT)
	@echo "\033[0;36m</ Compiling pipex bonus >\033[0m"
	@$(CC) $(OBJS_B) -o $(PIPEX_B)
	@echo "\033[1;32mPipex bonus has been compiled!\033[0m\n"

bonus: header_b $(PIPEX_B)

clean:
	@$(RM) $(OBJS) $(OBJS_B)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME) $(PIPEX_B)
	@make fclean -C libft
	@echo "\n\033[0;31m</ EVERYTHING HAS BEEN DELETED! >\033[0m\n"

re: fclean all

.PHONY: all clean fclean re bonus