/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:53:28 by gdaignea          #+#    #+#             */
/*   Updated: 2023/11/06 15:33:09 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//UTILS
int		ft_strchr(const char *str, int c);
char	*ft_strdup(char *s);
char	*ft_strjoin_and_free(char *s1, char *s2);
int		ft_strlen(char *str);

//FONCTION
char	*get_next_line(int fd);
char	*extract_line(char *stash);
char	*free_stash(char *stash);
char	*read_fd(int fd, char *stash);

#endif