/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:05:35 by gautier           #+#    #+#             */
/*   Updated: 2024/02/06 14:36:15 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	char	*path;
	int		file;
	char	**cmd;

	path = get_path(av[2], env);
	cmd = ft_split(av[2], ' ');
	if (!path)
	{
		free_tab(cmd);
		perror("cmd1 path not found");
		exit(1);
	}
	file = open(av[1], O_RDONLY, 0777);
	dup2(file, 0);
	close(fd[0]);
	dup2(fd[1], 1);
	close(file);
	close(fd[1]);
	if (execve(path, cmd, env) == -1)
	{
		perror("child exec error\n");
		exit(1);
	}
}

void	parent_process(char **av, int *fd, char **env)
{
	char	*path;
	int		file;
	char	**cmd;

	path = get_path(av[3], env);
	cmd = ft_split(av[3], ' ');
	if (!path)
	{
		free_tab(cmd);
		perror("cmd2 path not found");
		exit(1);
	}
	file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(file, 1);
	close(fd[1]);
	dup2(fd[0], 0);
	close(file);
	close(fd[0]);
	if (execve(path, cmd, env) == -1)
	{
		perror("parent exec error\n");
		exit(1);
	}
}

int main(int ac, char **av, char **env)
{
	pid_t	pid;
	int	fd[2];
	
	if(ac != 5)
	{
		perror("Error. program must be executed as follow : ./pipex file1 cmd1 cdm2 file2");
		exit(1);
	}
	pipe(fd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork error.");
		exit(1);
	} 
	if (pid == 0)
		child_process(av, fd, env);
	else
		parent_process(av, fd, env);
	return (0);
}

