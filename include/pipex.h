/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:59:17 by gautier           #+#    #+#             */
/*   Updated: 2024/02/12 13:19:42 by gautier          ###   ########.fr       */
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
char    *get_path(char *av, char **env);
char    *extract_env(char **env);
void    init_pipe(char *av, char **env);


/* PIPEX_BONUS */
void	free_tab(char **tab);
void    here_doc(int ac, char **av, char **env);
int		here_doc_init(char **av);
void    execute(char *av, char **env);

/* PIPEX_BONUS_UTILS */
void    execute(char *av, char **env);

/* GNL */
char	*get_next_line(int fd);


#endif