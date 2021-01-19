/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:43:25 by gpaeng            #+#    #+#             */
/*   Updated: 2021/01/19 17:22:32 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 반복하면서 하나씩 읽어오기 때문에 read()의 fd는 0이 되어야 합니다.
// '\n' 까지 계속 arr에 추가를 하고 '\n'이 있는 경우에 line에 '\n'전까지 저장하고
// arr는 free 해주고 다시 arr에 '\n'다음 부터 저장합니다.

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t idx;

	idx = 0;
	while (*str++)
	{
		idx++;
	}
	return (idx);
}

char		*ft_strndup(const char *str, size_t num)
{
	char	*arr;
	size_t	idx;

	if (!(arr = (char *)malloc(sizeof(char) * (num + 1))))
		return (0);
	idx = 0;
	while (*str && idx < num)
	{
		arr[idx] = *str;
		idx++;
		str++;
	}
	arr[idx] = '\0';
	return (arr);
}

char		*ft_strjoin(const char *a, const char *b)
{
	size_t	alen;
	size_t	blen;
	size_t	idx;
	char	*arr;

	alen = ft_strlen(a);
	blen = ft_strlen(b);
	if (!(arr = (char *)malloc(sizeof(char) * (alen + blen + 1))))
		return (0);
	idx = 0;
	while (a[idx] && idx < alen)
	{
		arr[idx] = a[idx];
		idx++;
	}
	idx = 0;
	while (b[idx] && idx < blen)
	{
		arr[idx + alen] = b[idx];
		idx++;
	}
	arr[alen + blen] = '\0';
	return (arr);
}

char		*ft_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	return (0);
}

int		ft_make_arr(char **arr, char *buf, ssize_t nr)
{
	char *backup;

	if (*arr == NULL)
	{
		backup = ft_strndup(buf, nr);
		*arr = backup;
	}
	else
	{
		backup = ft_strjoin(*arr, buf);
		free(*arr);
		*arr = backup;
	}
	if (ft_strchr(*arr, '\n'))
		return (1);
	return (0);
}

char	*ft_make_line(char **arr, int *check)
{
	char *new_lineptr;
	char *backup;
	char *tmp;

	new_lineptr = ft_strchr(*arr, '\n');
	if (new_lineptr)
	{
		*check = 1;
		backup = ft_strndup(*arr, new_lineptr - *arr);
		tmp = ft_strndup(new_lineptr + 1, ft_strlen(new_lineptr + 1));
		free(*arr);
		*arr = tmp;
		return (backup);
	}
	else
	{
		*check = 0;
		return (*arr);
	}
}

int		get_next_line(char **line)
{
	static char *arr;
	char		buf[256];
	ssize_t		nr;
	int			check;

	if (!line)
		return (-1);
	while ((nr = read(0, buf, 1)) >= 0)
	{
		buf[nr] = '\0';
		if (ft_make_arr(&arr, buf, nr) || nr == 0)
			break ;
	}
	if (nr < 0)
		return (-1);
	*line = ft_make_line(&arr, &check);
	if (!check)
	{
		arr = 0;
		return (0);
	}
	return (1);
}
