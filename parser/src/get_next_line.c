/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:17:20 by mobaz             #+#    #+#             */
/*   Updated: 2020/11/12 10:33:41 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int		ft_check_new_line(char *line)
{
	if (!line)
		return (0);
	while (*line != '\0')
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

int		ft_final_line(char **str, char **line)
{
	int		i;
	char	*tmp;
	char	*temp2;

	i = 0;
	tmp = *str;
	temp2 = *line;
	while (*(*str + i) != '\n')
		i++;
	*line = ft_substr(*str, 0, i);
	*str = ft_strdup(*str + i + 1);
	if (**str == '\0')
		ft_free(str);
	free(temp2);
	free(tmp);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char *str;
	int			state;
	char		*tmp;

	state = 1;
	if (!str)
		str = ft_char_calloc(1);
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > MAXINT || !line)
		return (-1);
	if (!(*line = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (state > 0 && !ft_check_new_line(str))
	{
		if ((state = read(fd, *line, BUFFER_SIZE)) < 0)
			return (-1);
		*(*line + state) = '\0';
		str = ft_strjoin(str, *line);
	}
	if (state > 0)
		return (ft_final_line(&str, line));
	tmp = *line;
	*line = ft_strdup(str);
	free(tmp);
	ft_free(&str);
	return (0);
}
