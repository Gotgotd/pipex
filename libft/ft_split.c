/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:42:20 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/16 15:37:03 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, int n)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)ft_calloc(n + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (i < n)
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}

static void	mallocsecure(char **tab, int j)
{
	while (j)
	{
		j--;
		free(tab[j]);
	}
	free(tab);
}

static char	**fill_tab(char **tab, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		k = i;
		while (s[i] != c && s[i])
			i++;
		if (i > k)
		{
			tab[j] = ft_strndup(&s[k], (i - k));
			if (!tab[j])
			{
				mallocsecure(tab, j);
				return (NULL);
			}
			j++;
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	str = (char **)ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	str = fill_tab(str, s, c);
	return (str);
}

/*int	main(void)
{
	char	*str = "ceci  __est_un__test___!";
	char	**fct = ft_split(str, '_');
	int	i;
	
	printf("%d\n", count_words(str, '_'));
	for (i = 0; i < count_words(str, '_'); i++)
	{
		printf("%s\n", fct[i] );
	}
	free (fct);
	return (0);
}*/