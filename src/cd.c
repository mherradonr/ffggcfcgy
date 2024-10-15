/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/09/16 20:50:17 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

void	change_prev(void)
{
	char	*dir;

	dir = previous_directory();
	if (chdir(dir) == -1)
	{
		free(dir);
		ft_error("chdir error", NULL);
	}
	free(dir);
}

int	change_next(char *mat, char *cd, char *current)
{
	char	*dir;

	dir = next_directory(mat);
	if (chdir(dir) == -1)
	{
		free(dir);
		if (chdir(current) == -1)
			ft_error("chdir error", NULL);
		printf("-bash: cd: %s: No such file or directory\n", cd);
		return (1);
	}
	free(dir);
	return (0);
}

int	mini_change(char *mat, char *cd, char *current)
{
	if (ft_strncmp(mat, "..", 3) == 0)
		change_prev();
	else
	{
		if (change_next(mat, cd, current) == 1)
			return (1);
	}
	return (0);
}

void	full_directory(char *cd)
{
	char	**mat;
	char	*current;
	size_t	i;

	i = -1;
	current = current_directory();
	if (cd[0] == '/')
		change_next(cd, cd, current);
	else
	{
		mat = ft_split(cd, '/');
		if (!mat)
			ft_error(MALLOC, NULL);
		while (mat[++i] != NULL)
		{
			if (mini_change(mat[i], cd, current) == 1)
					break ;
		}
		ft_free(mat);
	}
	free(current);
}

void	change_cd(char **command)
{
	char	*dir;

	if (command[2])
		printf("bash: cd: too many arguments\n");
	else if (command[1] && ft_strncmp(command[1], "~", 2) != 0)
		full_directory(command[1]);
	else
	{
		dir = ft_get_env("HOME");
		if (chdir(dir) == -1)
			ft_error("chdir error", NULL);
	}
}
