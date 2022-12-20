#*** VARIABLES ***#

SERVER_NAME				=	server

CLIENT_NAME				=	client

# FILES				

SRCS_SERVER				=	$(addprefix $(DIR_SERVER), $(SERVER))		\
							$(addprefix $(DIR_ERROR), $(ERROR))
							
SRCS_CLIENT				=	$(addprefix $(DIR_CLIENT), $(CLIENT))		\
							$(addprefix $(DIR_ERROR), $(ERROR))

SERVER					=	server.c

CLIENT					=	client.c

ERROR					=	error.c

OBJS_SERVER				=	$(SRCS_SERVER:%.c=$(DIR_OBJS)%.o)

OBJS_CLIENT				=	$(SRCS_CLIENT:%.c=$(DIR_OBJS)%.o)

OBJS					=	$(OBJS_SERVER) $(OBJS_CLIENT)

DEPS					= 	$(OBJS:.o=.d)

# DIR

HEAD					=	includes/

DIR_SRCS				=	srcs/

DIR_SERVER				=	server/

DIR_CLIENT				=	client/

DIR_ERROR				=	error/

DIR_LIBFT				=	$(DIR_SRCS)libft/

DIRS					=	$(DIR_SERVER) $(DIR_CLIENT) $(DIR_ERROR)

DIR_OBJS				=	.build/

# PATH

PATHS_OBJS				=	$(addprefix $(DIR_OBJS), $(DIRS))

# CMD

CC						=	cc

CFLAGS					=	-Wall -Wextra -Werror -g3

LFLAGS					=	-L$(DIR_LIBFT) -lft

DEPS_FLAGS				=	-MMD -MP

MKDIR					=	mkdir -p

RM						=	rm -rf

#*** RULES ***#

all						:	$(DIR_OBJS)
						@$(MAKE) -C $(DIR_LIBFT)
						@$(MAKE) $(SERVER_NAME)
						@$(MAKE) $(CLIENT_NAME)

-include				$(DEPS)

$(SERVER_NAME)			:	$(OBJS_SERVER)
						$(CC) $(OBJS_SERVER) -o $(SERVER_NAME) $(LFLAGS)

$(CLIENT_NAME)			:	$(OBJS_CLIENT)
						$(CC) $(OBJS_CLIENT) -o $(CLIENT_NAME) $(LFLAGS)

$(DIR_OBJS)%.o			:	$(DIR_SRCS)%.c
						$(CC) $(CFLAGS) $(DEPS_FLAGS) -I $(HEAD) -I $(DIR_LIBFT)$(HEAD) -c $< -o $@

$(DIR_OBJS)				:
						$(MKDIR) $(PATHS_OBJS)

clean					:
						$(MAKE) -C $(DIR_LIBFT) clean
						$(RM) $(DIR_OBJS)

fclean					:	clean
						$(MAKE) -C $(DIR_LIBFT) fclean
						$(RM) $(CLIENT_NAME) $(SERVER_NAME)

re						:
						$(MAKE) fclean
						$(MAKE) all
