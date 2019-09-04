/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_max.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshvets <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:06:08 by mshvets           #+#    #+#             */
/*   Updated: 2019/09/04 21:06:10 by mshvets          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char		*ft_new(const char *s, char **end, char c)
{
	char	*arr;

	if (!(*end = ft_strchr(s, c)))
		*end = ft_strchr(s, '\0');
	if (!(arr = ft_strnew(*end - s)))
		return (NULL);
	return (arr);
}

char			**ft_strsplit(char const *s, char c, int num_wrd)
{
	char	**arr;
	char	*end;
	size_t	i;

	if (!(i = 0) && !s)
		return (NULL);
	if (!(arr = (char **)ft_memalloc(sizeof(*arr) * (ft_cntwrd(s, c) + 1))))
		return (NULL);
	if (num_wrd != ft_cntwrd(s, c))
		return (NULL);
	while (*s && i < num_wrd)
	{
		if (*s != c)
		{
			if (!(arr[i] = ft_new(s, &end, c)))
			{
				ft_strdeli(arr, i);
				return (NULL);
			}
			ft_memcpy(arr[i++], s, (end - s));
			s = end;
		}
		++s;
	}
	return (arr);
}