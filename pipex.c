/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:05:35 by gautier           #+#    #+#             */
/*   Updated: 2024/01/31 11:40:24 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *extract_env(char **env)
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

char *get_path(char **av, char **env)
{
	int		i;
	char	**allpaths;
	char	*goodpath;
	char	*subpath;
	char 	**cmd;

	cmd = ft_split(av[3], ' ');
	allpaths = ft_split(extract_env(env), ':');
	i = -1;
	while (allpaths[++i])
	{
		subpath = ft_strjoin(allpaths[i], '/');
		goodpath = ft_strjoin(subpath, cmd[0]);
		free(subpath);
		if (access(goodpath, F_OK | X_OK) == 0)
		{
			free_tab(cmd);
			free_tab(allpaths);
			return (goodpath);
		}
		free(goodpath);
	}
	free_tab(cmd);
	free_tab(allpaths);
	exit(1);
}

void	child_process(char **av, char **env)
{
	char *path;
	int	p
	
	path = get_path(av, env);
	execv(path);
}


int main(int ac, char **av, char *env)
{
	__pid_t	pid;
	
	if(ac != 5)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child_process(av, env);
	if (pid > 0)
		parent_process(av, env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char *path;
	(void)	ac;
	(void)	av;
	
	path = extract_env(env);
	printf("%s\n", path);
	return (0);
}