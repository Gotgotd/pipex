/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:38:30 by gdaignea          #+#    #+#             */
/*   Updated: 2024/02/14 10:26:12 by gdaignea         ###   ########.fr       */
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
		
	}
	else if (flag == 2)
	{

	}
	else if (flag == 3)
	{
		
	}
	else if (flag == 4)
}
