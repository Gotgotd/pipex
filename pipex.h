/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:59:17 by gautier           #+#    #+#             */
/*   Updated: 2024/02/02 11:26:54 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "libft/libft.h"
# include <fcntl.h>

void	free_tab(char **tab);
void	parent_process(char **av, int *fd, char **env);
void	child_process(char **av, int *fd, char **env);
char    *get_path(char *av, char **env);
char    *extract_env(char **env);

#endif