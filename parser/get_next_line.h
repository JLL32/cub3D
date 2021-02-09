/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:17:20 by jll32             #+#    #+#             */
/*   Updated: 2021/02/09 12:33:43 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define MAXINT 2147483647
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 32

int			get_next_line(int fd, char **line);
void		*ft_char_calloc(size_t i);
size_t		ft_strlen(const char *s);
char		*ft_strcpy(char *dest, const char *src);
#endif
