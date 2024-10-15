/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/09/30 23:34:03 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc(char *del, int *fd, int stdin_copy)
{
	char	*here;
	char 	*delimitier;

	delimitier = ft_strjoin(del, "\n");
	if (!delimitier)
		ft_error(MALLOC, NULL);
	while (1)
	{
		ft_putstr_fd(">", stdin_copy);
		here = get_next_line(stdin_copy);
		if (ft_strncmp(here, delimitier, ft_strlen(here)) == 0)
		{
			free(delimitier);
			break ;
		}
		ft_putstr_fd(here, fd[WRITE]);
		free(here);
	}
	free(here);
	close(fd[WRITE]);
}

void	mini_here(char *del, int stdin_copy)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_error(PIPE, NULL);
	heredoc(del, fd, stdin_copy);
	if (dup2(fd[READ], STDIN_FILENO) == -1)
		ft_error(DUP, NULL);
}

void	mini_append(char *commands, int stdout_copy)
{
	int	out_fd;

	out_fd = open(commands, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (out_fd < 0)
	{
		printf("-bash: %s: No such file or directory\n", commands);
		if (dup2(stdout_copy, STDIN_FILENO) == -1)
			ft_error(DUP, NULL);
		return ;
	}
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		ft_error(DUP, NULL);
	close(out_fd);
}

void	ft_stdinout(char **commands, char **env, char **mat_qte)
{
	int	i;
	int	stdout_copy;
	int	stdin_copy;
	
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	i = -1;
	while (commands[++i] && commands[i + 1])
	{
		if (ft_strncmp(commands[i], "<<", 2) == 0
				&& ft_strncmp(mat_qte[i], "nn", 2) == 0)
			mini_here(commands[++i], stdin_copy);
		else if (ft_strncmp(commands[i], "<", 1) == 0
				&& ft_strncmp(mat_qte[i], "n", 1) == 0)
			mini_in(commands[++i], stdin_copy);
		else if (ft_strncmp(commands[i], ">>", 2) == 0
				&& ft_strncmp(mat_qte[i], "nn", 2) == 0)
			mini_append(commands[++i], stdout_copy);
		else if (ft_strncmp(commands[i], ">", 1) == 0
				&& ft_strncmp(mat_qte[i], "n", 1) == 0)
			mini_out(commands[++i], stdout_copy);
	}
	exec_stdinout(commands, env, stdin_copy, stdout_copy);
}

int	*ft_stdpipex(char **commands, char **env)
{
	int	i;
	int	stdout_copy;
	int	stdin_copy;
	int	*stds;


	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	stds = ft_calloc(2 + 1, sizeof(int));
	if (!stds)
		ft_error(MALLOC, NULL);
	i = -1;
	while (commands[++i] && commands[i + 1])
	{
		if (ft_strncmp(commands[i], "<<", 2) == 0)
			mini_here(commands[++i], stdin_copy);
		else if (ft_strncmp(commands[i], "<", 1) == 0)
			mini_in(commands[++i], stdin_copy);
		else if (ft_strncmp(commands[i], ">>", 2) == 0)
			mini_append(commands[++i], stdout_copy);
		else if (ft_strncmp(commands[i], ">", 1) == 0)
			mini_out(commands[++i], stdout_copy);
	}
	stds[IN] = dup(STDIN_FILENO);
	stds[OUT] = dup(STDOUT_FILENO);
	exec_stdinout(commands, env, stdin_copy, stdout_copy);
	return (stds);
}

void	ft_pipe(char **mat, char **env)
{
	int		fds[2];
	int		fds_tmp[2];
	char	**space;
	int		*files;
	int		i;

	if (pipe(fds) == -1)
		ft_error(PIPE, NULL);
	if (pipe(fds_tmp) == -1)
		ft_error(PIPE, NULL);
	files = ft_calloc(2 + 1, sizeof(int));
	if (!files)
		ft_error(MALLOC, NULL);
	i = -1;
	while (mat[++i])
	{
		space = ft_split(mat[i], ' ');
		if (!space)
			ft_error(MALLOC, NULL);
		files = ft_stdpipex(space, env);
		ft_free(space);
		close(fds[READ]);
		if (dup2(files[1], STDOUT_FILENO) == -1)
			ft_error(DUP, NULL);
		close(fds[WRITE]);
		if (dup2(fds[READ], STDIN_FILENO) == -1)
			ft_error(DUP, NULL);
	}
	
}

void	ft_operator(char **commands, char *here, char **env)
{
	char	*src;
	char	**mat_pipe;
	char	*quote;
	char	**mat_qte;

	quote = clean_other(here); ////// MIRAR EN TODAS ESTAS FUNCIONES QUE NO HAYA FT_ERROR SI NO NULL
	src = clean_line(here);
	if (shell_strnstr(src, "|", ft_strlen(src), quote))
	{
		mat_pipe = ft_split(src, '|');
		if (!mat_pipe)
			ft_error(MALLOC, NULL);
		ft_pipe(mat_pipe, env);
		ft_free(mat_pipe);
	}
	else
	{
		mat_qte = ft_split(quote, ' ');
		ft_stdinout(commands, env, mat_qte);
		ft_free(mat_qte);
	}
	frees(src, quote);
}
