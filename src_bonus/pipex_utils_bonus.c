/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:38:30 by gdaignea          #+#    #+#             */
/*   Updated: 2024/02/12 13:49:53 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*extract_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

void	execute(char *av, char **env)
{
	char	*path;
	char	**cmd;

	path = get_path(av, env);
	cmd = ft_split(av, ' ');
	if (!path)
	{
		free_tab(cmd);
		perror("error. path to cmd not found.");
		exit(1);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		free_tab(cmd);
		perror("exec error");
		exit(1);
	}
}
