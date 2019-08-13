/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdudko <kdudko@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 01:22:14 by kdudko            #+#    #+#             */
/*   Updated: 2019/01/05 03:14:42 by kdudko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len_word(char const *s, char c)
{
	size_t i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	size_t	row;
	size_t	words;

	if (!(s && c))
		return (NULL);
	words = ft_count_words((char*)s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (arr == NULL)
		return (NULL);
	row = -1;
	while (++row < words)
	{
		while (*s && *s == c)
			s++;
		arr[row] = ft_strsub(s, 0, ft_len_word(s, c));
		if (arr[row] == NULL)
		{
			free(arr[row]);
			return (NULL);
		}
		s = s + ft_len_word(s, c);
	}
	arr[row] = NULL;
	return (arr);
}
