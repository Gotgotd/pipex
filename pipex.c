/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:05:35 by gautier           #+#    #+#             */
/*   Updated: 2024/01/31 15:57:17 by gautier          ###   ########.fr       */
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

char *get_path(char *av, char **env)
{
	int		i;
	char	**allpaths;
	char	*goodpath;
	char	*subpath;
	char 	**cmd;

	cmd = ft_split(av, ' ');
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
	return (NULL);
}

void	child_process(char **av, int *fd, char **env)
{
	char	*path;
	int		file;
	char	**cmd;
	
	path = get_path(av[2], env);
	cmd = ft_split(av[2], ' ');
	if (!path)
		perror("path not found");
	file = open(av[1], O_RDONLY, 0777);
	dup2(file, 0);
	close(fd[0]);
	dup2(fd[1], 1);
	execve(path, cmd, env);
}


int main(int ac, char **av, char *env)
{
	pid_t	pid;
	int	fd[2];
	
	if(ac != 5)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	pipe(fd);
	if (pid == 0)
		child_process(av, fd, env);
	if (pid > 0)
		parent_process(av, fd, env);
	return (0);
}

