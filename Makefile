# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llethuil <llethuil@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/25 15:43:51 by llethuil          #+#    #+#              #
#    Updated: 2022/04/22 18:08:19 by llethuil         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                              ~~~ COLOR CODES ~~~                             #
#                                                                              #
# **************************************************************************** #

ERASE	:=	\033[2K\r
BOLD	:=	\033[1m
redir		:=	\033[31m
GREEN	:=	\033[32m
BLUE	:=	\033[34m
PINK	:=	\033[35m
BOLD	:=	\033[1m
END		=	\033[0m

# **************************************************************************** #
#                                                                              #
#                              ~~~ VARIABLES ~~~                               #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror -ggdb3

RM			:= rm -f

LIBFT_DIR	:= libft

INCS_DIR	:= incs

SRCS_DIR	:= srcs

OBJS_DIR	:= .objs

INCS_LST	:=	header.h			\
				built_ins.h			\
				cmd_line_manager.h	\
				cmd_lst_manager.h	\
				cmd_separator.h		\
				env_var_manager.h	\
				executer.h			\
				gb_collector.h		\
				main.h				\
				arg_separator.h		\
				redir_collector.h	\
				signal_manager.h	\
				shell_initializer.h	\
				utils.h				\

SRCS_LST	:=	main/main.c										\
				shell_initializer/shell_initializer.c			\
				cmd_line_manager/cmd_line_manager.c				\
				cmd_separator/cmd_separator.c					\
				cmd_separator/check_pipe.c						\
				cmd_separator/check_quotes.c					\
				cmd_separator/check_redir.c						\
				cmd_separator/split_cmd.c						\
				cmd_separator/simulate_heredoc.c				\
				redir_collector/copy_filenames_in_redir_tab.c	\
				redir_collector/get_last_redir_types_tab.c		\
				redir_collector/redir_collector.c				\
				arg_separator/arg_separator.c					\
				arg_separator/create_arg_tab.c					\
				arg_separator/get_arg_len.c						\
				arg_separator/get_number_of_arg.c				\
				cmd_lst_manager/cmd_lst_init.c					\
				cmd_lst_manager/cmd_lst_manager.c				\
				cmd_lst_manager/utils_cmd_lst_manager.c			\
				executer/built_in_utils.c						\
				executer/close_all_files.c						\
				executer/convert_env_tab.c						\
				executer/executer.c								\
				executer/get_path.c								\
				executer/handle_heredocs.c						\
				executer/pipe_exec.c							\
				executer/pipe_utils.c							\
				executer/open_all_files.c						\
				executer/set_data_flux.c						\
				built_ins/ft_cd.c								\
				built_ins/ft_echo.c								\
				built_ins/ft_env.c								\
				built_ins/ft_exit.c								\
				built_ins/ft_export.c							\
				built_ins/ft_pwd.c								\
				built_ins/ft_unset.c							\
				env_var_manager/convert_env_var_in_str.c		\
				env_var_manager/env_var_counter.c				\
				env_var_manager/utils_env_var_processing.c		\
				env_var_manager/utils_env_var.c					\
				utils/utils_build_heredoc_str.c					\
				utils/utils_check_fork_error.c					\
				utils/utils_clean_str.c							\
				utils/utils_copy_filename.c						\
				utils/utils_count_filename_len.c				\
				utils/utils_count_n_file.c						\
				utils/utils_error.c								\
				utils/utils_ft_free.c							\
				utils/utils_gb_add.c							\
				utils/utils_gb_clear.c							\
				utils/utils_get_history_path.c					\
				utils/utils_get_status.c						\
				utils/utils_is_space.c							\
				utils/utils_pipe.c								\
				utils/utils_set_termios.c						\
				utils/utils_signal.c							\
				utils/utils_skip.c								\

SUBDIRS_LST	:=	main				\
				shell_initializer	\
				cmd_line_manager	\
				cmd_separator		\
				redir_collector		\
				arg_separator		\
				cmd_lst_manager		\
				executer			\
				built_ins			\
				env_var_manager		\
				utils				\

OBJS_LST	:=	$(SRCS_LST:.c=.o)

LIBFT_AR	:=	$(LIBFT_DIR)/libft.a

RL_LIB		:=	-L$(shell brew --prefix readline)/lib

RL_INC		:=	-I$(shell brew --prefix readline)/include

INCS		:=	$(addprefix $(INCS_DIR)/, $(INCS_LST))

SRCS		:=	$(addprefix $(SRCS_DIR)/, $(SRCS_LST))

OBJS		:=	$(addprefix $(OBJS_DIR)/, $(OBJS_LST))

# ************************************************************************** #
#                                                                            #
#                              ~~~ RULES & COMMANDS ~~~                      #
#                                                                            #
# ************************************************************************** #

all: libft $(NAME)

.SILENT:

libft:
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_AR)
	test -z '$(filter %.o,$?)' || printf "$(GREEN)> All the .c files from minishell have been compiled successfully !$(END)\n"
	printf "$(BLUE)> Creating the executable file :$(END) $@\n"
	$(CC) $(OBJS) $(LIBFT_AR) $(RL_INC) $(RL_LIB) -lreadline -o $(NAME)
	printf "$(GREEN)> Executable file has been created successfully !$(END)\n"

$(OBJS_DIR):
	mkdir -p $(addprefix $(OBJS_DIR)/, $(SUBDIRS_LST))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCS) Makefile | $(OBJS_DIR)
	printf "$(BLUE)> Compiling :$(END) $<\n"
	$(CC) $(CFLAGS) -I $(INCS_DIR) $(RL_INC) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	printf "$(PINK)> Removing minishell .o files ...$(END)\n"
	$(RM) $(OBJS)
	printf "$(PINK)> Removing .objs directory ...$(END)\n"
	rm -rf $(OBJS_DIR)
	printf "$(GREEN)> All the .o files have been removed successfully !$(END)\n"

fclean: clean
	printf "$(PINK)> Removing libft archive file ...$(END)\n"
	$(RM) $(LIBFT_AR)
	printf "$(PINK)> Removing minishell executable file ...$(END)\n"
	$(RM) $(NAME)
	printf "$(GREEN)> Libft archive and minishell executable files have been removed successfully !$(END)\n"

re: fclean all

.PHONY: all clean fclean libft re
