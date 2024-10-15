/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/10/09 20:46:08 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

int	size_char(char *src, char c)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	while (src[++i])
	{
		if (src[i] != c)
			j++;
	}
	return (j);
}

char	*delete_character(char *src, char c)
{
	int		i;
	int		j;
	char	*delete;

	j = size_char(src, c);
	if ((size_t)j == ft_strlen(src))
	{
		delete = ft_strdup(src);
		if (!delete)
			ft_error(MALLOC, NULL);
		return (delete);
	}
	delete = ft_calloc(j + 1, sizeof(char));
	if (!delete)
		ft_error(MALLOC, NULL);
	i = -1;
	j = -1;
	while (src[++i])
	{
		if (src[i] != c)
			delete[++j] = src[i];
	}
	return (delete);
}

char	*clean_line(char *line)
{
	char	*trm_line;
	char	*otmp;
	char	*spaces;

	spaces = add_spaces(line); // CAMBIARCAMBIARCAMBIARCAMBIARCAMBIARCAMBIARCAMBIARCAMBIARCAMBIARCAMBIAR ^POR FUNCIOON DE COMILLAS NUEVAS
	trm_line = ft_strtrim(spaces, " ");
	free(spaces);
	//trm_line = ft_strtrim(line, " ");
	if (!trm_line)
		ft_error(MALLOC, NULL);
	otmp = ft_strtrim(trm_line, "\n");
	if (!otmp)
		ft_error(MALLOC, NULL);
	free(trm_line);
	return (otmp);
}

char	**mini_change_mat(char **mat, int i, int j, char **src)
{
	char	*tmp;

	while (mat[++i])
	{
		if (ft_strchr(mat[i], '$') && ft_strlen(mat[i]) > 1)
		{
			tmp = env_dollar(mat[i]);
			if (!tmp)
				continue ;
			else
			{
				src[++j] = ft_strdup(tmp);
				free(tmp);
			}
		}
		else
			src[++j] = ft_strdup(mat[i]);
		if (!src[j])
			return (ft_free(src), ft_error(MALLOC, NULL), mat);
	}
	return (src);
}

