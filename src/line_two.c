/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/09/25 23:02:02 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

char	**change_mat(char **mat)
{
	char	**src;
	int		i;
	int		j;

	src = ft_calloc(ft_matlen(mat) + 1, sizeof(char *));
	i = -1;
	j = -1;
	src = mini_change_mat(mat, i, j, src);
	return (src);
}

char **prepare_split(char *str)
{
	char	*quotes;
	char	**qte_split;

	quotes = clean_other(str);
	if (!quotes)
		ft_error(MALLOC, NULL);
	qte_split = ft_split(quotes, ' ');
	free(quotes);
	if (!qte_split)
		ft_error(MALLOC, NULL);
	return (qte_split);
}

char **quote_split(char *str, char **qte_split)
{
	char	**mat;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (qte_split[i])
		i++;
	mat = ft_calloc(i + 1, sizeof(char *));
	if (!mat)
		ft_error(MALLOC, NULL);
	tmp = clean_qt(str);
	if (!tmp)
		ft_error(MALLOC, NULL);
	i = -1;
	j = 0;
	while (qte_split[++i])
	{
		mat[i] = ft_substr(tmp, j, ft_strlen(qte_split[i]));
		if (!mat[i])
			return (ft_free(mat), ft_free(qte_split), NULL);
		j += ft_strlen(qte_split[i]) + 1;
	}
	free(tmp);
	return (mat);
}

char **ft_quotesplit(char *str)
{
	char **qte_split;
	char **mat;

	qte_split = prepare_split(str);
	if (!qte_split)
		ft_error(MALLOC, NULL);
	mat = quote_split(str, qte_split);
	ft_free(qte_split);
	return (mat);
}


char	**line_split(char *line)
{
	char	*clean;
	char	**mat;
	char	**dollar;
	// char	*quotes;

	clean = clean_line(line);
	// quotes = clean_qt(clean);
	// mat = ft_split(quotes, ' '); // HAY QUE VER SI ESTA BIENN EL SPLIT DE COMILLAS
	mat = ft_quotesplit(clean);
	if (!mat)
		ft_error(MALLOC, NULL);
	free(clean);
	dollar = change_mat(mat);
	ft_free(mat);
	return (dollar);
}
