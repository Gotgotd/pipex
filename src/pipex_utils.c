/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:38:30 by gdaignea          #+#    #+#             */
/*   Updated: 2024/02/14 16:38:16 by gautier          ###   ########.fr       */
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

void	ft_error(int flag)
{
	if (flag == 1)
	{
		perror("Error. arguments invalid");
		exit(1);
	}
	else if (flag == 2)
	{
		perror("pipe error.");
		exit(1);
	}
	else if (flag == 3)
	{
		perror("fork error.");
		exit(1);
	}
	else if (flag == 4)
	{
		perror("error executing command");
		exit(1);
	}
}
