/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/10/09 18:26:30 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define READ 0
# define WRITE 1

# define IN 0
# define OUT 1

# define FILE "bash: no such file or directory: "
# define COMMAND "bash: command not found: "
# define ARGUMENTS "Error: bad number of arguments"
# define CD "Error: No such file or directory"
# define CHILD "child error"
# define PIPE "pipe error"
# define MALLOC "memory error"
# define FORK "fork error"
# define DUP "dup error"
# define WAIT "waitpid error"
# define ENV "env error"
# define TOKEN "bash: syntax error near unexpected token"

extern volatile int sig;

typedef struct s_arguments
{
	int		in_fd;
	char	*command_one;
	char	*command_two;
	char	**split_one;
	char	**split_two;
	int		out_fd;
}				t_arguments;

typedef struct s_arguments_bonus
{
	int		in_fd;
	char	**commands;
	char	***splits;
	int		out_fd;
	int		here_doc;
	char	**argv;
}				t_arguments_bonus;

typedef struct s_word_info 
{
    int start;
    int length;
} 			t_word_info;

/*------START.C------*/
char	*ft_get_env(char *get);
void	print_minishell(void);
char	*current_directory(void);
char	*first_line(void);
/*-------------------*/

/*------UTILS.C------*/
/*BORRARBORRARBORRARBORRARBORRAR*/
void	print_matrix(char **matrix);
/*BORRARBORRARBORRARBORRARBORRAR*/
void	ft_error(char *str, char *file);
char	*ft_threejoin(char const *s1, char const *s2, char const *s3);
char	*ft_strstrend(const char *haystack, const char *needle);
char	*ft_replace(const char *haystack, const char *needle, const char replace);
char	*replace_pwd(void);
/*-------------------*/

/*------UTILS_TWO.C------*/
char	**ft_free(char **mat);
int		ft_fullcmp(const char *s1, const char *s2);
char	*ft_nulljoin(char *s1, char *s2);
size_t	dollar_size(char **mat, char *src);
char	*copy_character(char *src, char c);
/*-----------------------*/

/*------LINE.C------*/
int		size_char(char *src, char c);
char	*delete_character(char *src, char c);
char	*clean_line(char *line);
char	**mini_change_mat(char **mat, int i, int j, char **src);
/*------------------*/

/*-------CD.C-------*/
void	change_prev(void);
int		change_next(char *mat, char *cd, char *current);
void	full_directory(char *cd);
void	change_cd(char **command);
/*------------------*/

/*-------CD_TWO.C-------*/
char	*current_cd(void);
char	*previous_directory(void);
char	*next_directory(char *cd);
/*----------------------*/

/*-------ECHO.C-------*/
void	ft_echo(char **mat);
/*--------------------*/

/*------UTILS_THREE.C------*/
size_t	ft_matlen(char **mat);
char	*change_dollar(char **mat, char *src);
char	*dollar_digit(char *str);
char	*dollar_env(char *str);
char	*mini_env_dollar(char * src);
char	*env_dollar(char *strg);
/*-------------------------*/

/*------UTILS_FOUR.c------*/
void	ft_pwd(void);
char	*search_op(char *src);
void	frees(char *s1, char *s2);
char	*shell_strnstr(char *stack, char *needle, size_t len, char *qte);
/*-------------------------*/

/*-------LINE_TWO.C-------*/
char	**change_mat(char **mat);
char	**line_split(char *line);
/*----------------------*/

/*-------SPACES.C-------*/
void	handle_quotes(char **input, char **temp, int *doubl, int *single);
void	handle_operators(char **ipt, char **temp);
char	*add_spaces(char *input);
/*----------------------*/

/*-------COMMAND.C-------*/
char	*check_first(char **env, char *arg);
void	ft_command(char	**mat, char **env);
/*-----------------------*/

/*-------OPERATORS.C-------*/
char	**clean_in(char **commands);
char	**clean_out(char **commands);
void	exec_opin(char **commands, char **env, int stdin_copy);
void	ft_stdin(char **commands, char **env);
void	exec_opout(char **commands, char **env, int stdout_copy);
void	ft_operator(char **commands, char *here, char **env);
/*-----------------------*/

/*-------OPERATORS_TWO.C-------*/
void	ft_stdout(char **commands, char **env);
void	exec_stdinout(char **commands, char **env, int stdin, int stdout);
void	mini_in(char *commands, int stdin_copy);
void	mini_out(char *commands, int stdout_copy);
/*-----------------------*/

/*-------OPERATORS_THREE.C-------*/
void	heredoc(char *del, int *fd, int stdin_copy);
void	mini_here(char *del, int stdin_copy);
void	ft_stdinout(char **commands, char **env, char **mat_qte);
void	ft_operator(char **commands, char *here, char **env);
/*-----------------------*/

/*-------QUOTES.C-------*/
int		quote_close(char *str);
void    mini_qte(char *str, char *lit, int clsd, int clss);
char	*quote_line(char *str);
char	*clean_qt(char *str);
/*----------------------*/

/*-------QUOTES_TWO.C----*/
char	*clean_other(char *str);
/*----------------------*/

/*-------PIPEX-------*/
char				**path_env(char **env);
size_t				where_path(char **env);
char				*first_word(char *arg);
char				*command(char **env, char *arg);
t_arguments			check_arg(int argn, char **argv, char **env);

t_arguments_bonus	check_here(int argn, char **argv);
t_arguments_bonus	check_arg_bonus(int argn, char **argv, char **env);
void 				free_arguments_bonus(t_arguments_bonus *args);
void				pipex_free(int **fds, pid_t *pid, int i, int x);
int					**piping(t_arguments_bonus arguments, int argn);
void				fds_free(int **fds, int i, int x);
void 				ft_wait(t_arguments_bonus arguments, int argn, pid_t *pid, int **fds);
void				here_doc(char **argv, int *fd);
void				dup_here(char **argv);
/*----------------------*/

#endif