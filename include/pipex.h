/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:59:17 by gautier           #+#    #+#             */
/*   Updated: 2024/02/14 10:30:06 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>

/* PIPEX */
void	parent_process(char **av, int *fd, char **env);
void	child_process(char **av, int *fd, char **env);
char	*get_path(char *av, char **env);
char	*extract_env(char **env);
void	init_pipe(char *av, char **env);

/* PIPEX UTILS*/
void	ft_error(int flag);
void	free_tab(char **tab);

/* PIPEX_BONUS */
void	here_doc(int ac, char **av, char **env);
int		here_doc_init(char **av);

/* PIPEX_BONUS_UTILS */
void	execute(char *av, char **env);

/* GNL */
char	*get_next_line(int fd);

#endif