/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:05:35 by gautier           #+#    #+#             */
/*   Updated: 2024/02/19 10:51:12 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

char	*get_path(char *av, char **env)
{
	int		i;
	char	**allpaths;
	char	*goodpath;
	char	*subpath;
	char	**cmd;

	cmd = ft_split(av, ' ');
	allpaths = ft_split(extract_env(env), ':');
	i = -1;
	while (allpaths[++i])
	{
		subpath = ft_strjoin(allpaths[i], "/");
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
	int		file;

	file = open(av[1], O_RDONLY, 0777);
	if (file == -1)
	{
		perror("error opening file");
		exit (1);
	}
	dup2(file, 0);
	close(fd[0]);
	dup2(fd[1], 1);
	close(file);
	close(fd[1]);
	execute(av[2], env);
}

void	parent_process(char **av, int *fd, char **env)
{
	int		file;

	file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("error opening file");
		exit(1);
	}
	dup2(file, 1);
	close(fd[1]);
	dup2(fd[0], 0);
	close(file);
	close(fd[0]);
	execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (ac != 5)
		ft_error(1);
	if (pipe(fd) == -1)
		ft_error(2);
	pid = fork();
	if (pid == -1)
		ft_error(3);
	if (pid == 0)
		child_process(av, fd, env);
	else
		parent_process(av, fd, env);
	return (0);
}
