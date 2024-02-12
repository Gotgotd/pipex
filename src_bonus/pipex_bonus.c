/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:19:18 by gautier           #+#    #+#             */
/*   Updated: 2024/02/12 13:19:27 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipex.h"

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


void    init_pipe(char *av, char **env)
{
    int fd[2];
    int pid;

    if (pipe(fd) == -1)
    {
        perror("pipe init error");
        exit (1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if (!pid)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        execute(av, env);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], 0);
    }
}
int	here_doc_init(char **av)
{
	char *line;
	int	file1;

	line = NULL;
    file1 = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file1 == -1)
	{
		perror("error opening file");
		exit(1);
	}
	while(1)
    {
        write(1, "pipe here_doc>", 14);
        line = get_next_line(0);
		if (!line)
			return(1);
		if (ft_strlen(av[2]) + 1 == ft_strlen(line) 
			&& ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			return(0);
		}
		ft_putstr_fd(line, file1);
		free(line);
	}
	close(file1);
	return (1);
}

void    here_doc(int ac, char **av, char **env)
{
    int 	file1;
    int 	file2;
	int		i;

	i = 3;
    if (ac < 6)
    {
		exit(1);
		perror("error running program");
    }
	here_doc_init(av);
	file1 = open("here_doc", O_RDONLY, 0777);
    file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file1 == -1 || file2 == -1)
	{
		perror("error opening file");
		exit(1);
	}
	dup2(file1, 0);
	while (i < ac - 2)
		init_pipe(av[i++], env);
	dup2(file2, 1);
	execute(av[ac - 2], env);
}


int main(int ac, char **av, char **env)
{
    int i;
    int file1;
    int file2;

    if (ac < 5)
    {
        perror("error running program");
        exit(1);
    }
    if (strncmp(av[1], "here_doc", 7) == 0)
	{
		i = 3;
        here_doc(ac, av, env);
	}
	i = 2;
    file1 = open(av[1], O_RDONLY, 0777);
    file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    dup2(file1, 0);
    while (i < ac - 2)
        init_pipe(av[i++], env);
    dup2(file2, 1);
    execute(av[ac - 2], env);
	return (0);
}
