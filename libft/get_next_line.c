/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 08:32:32 by hbuisser          #+#    #+#             */
/*   Updated: 2020/08/19 22:24:26 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strchar(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

char			*ft_gnljoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = ft_calloc(len1 + len2 + 1, sizeof(char));
	i = 0;
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		res[i + j] = s2[j];
		j++;
	}
	if (s1)
		free (s1);
	return (res);
}

int				ft_getpos(char **str, char **line)
{
	int		pos;
	char	*tmp;

	pos = ft_strchar(*str, '\n');
	if (pos >= 0)
	{
		*line = ft_substr(*str, 0, pos);
		tmp = *str;
		*str = ft_substr(*str, pos +1, ft_strchar(*str,'\0'));
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_substr(*str, 0, ft_strchar(*str, '\0'));
		free(*str);
		return (0);
	}
}

int				get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*str;
	int			ret;

	if (!line)
		return (-1);
	if (!(str) && !(str = ft_calloc(1, sizeof(char))))
		return (-1);
	while (ft_strchar(str, '\n') < 0 && (ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		str = ft_gnljoin(str, buff);
	}
	return (ft_getpos(&str, line));
}
