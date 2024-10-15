/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_two.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by ***********       #+#    #+#             */
/*   Updated: 2024/09/16 20:48:41 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*current_cd(void)
{
	char	*cwd;
	size_t	i;
	size_t	j;
	size_t	k;
	char	*tmp;

	cwd = current_directory();
	i = ft_strlen(cwd);
	j = 0;
	if (i == 0 && cwd[i] == '/')
		return ("/");
	while (cwd[--i] != '/' && i > 0)
		j++;
	tmp = ft_calloc(j + 1, sizeof(char));
	if (!tmp)
		ft_error(MALLOC, NULL);
	k = 0;
	while (cwd[++i])
	{
		tmp[k] = cwd[i];
		k++;
	}
	free(cwd);
	return (tmp);
}

char	*previous_directory(void)
{
	char	*cwd;
	char	*prev;
	char	*current;

	cwd = current_directory();
	if (ft_strlen(cwd) == 1 && cwd[0] == '/')
		return (cwd);
	current = current_cd();
	prev = ft_strtrim(cwd, current);
	free(cwd);
	free(current);
	if (!prev)
		ft_error(MALLOC, NULL);
	return (prev);
}

char	*next_directory(char *cd)
{
	char	*cwd;
	char	*new_cd;
	char	*trim;

	cwd = current_directory();
	if (cd[0] == '/')
	{
		new_cd = ft_strdup(cd);
		if(!new_cd)
			ft_error(MALLOC, NULL);
	}
	else
		new_cd = ft_threejoin(cwd, "/", cd);
	free(cwd);
	trim = ft_strtrim(new_cd, "\n");
	free(new_cd);
	if (!trim)
		ft_error(MALLOC, NULL);
	return (trim);
}
