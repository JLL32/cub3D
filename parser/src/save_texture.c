/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:56:14 by jll32             #+#    #+#             */
/*   Updated: 2021/02/09 12:33:08 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

char	*save_texture(char **texture)
{
	char		*texture_path;
	static int	tex_num;
	int			i;

	if (tex_num > 4)
		ft_error(NULL, "Error\nDuplicate texture");
	tex_num++;
	i = 1;
	while (texture[i])
		i++;
	if (i != 2)
		ft_error(NULL, "Error\nTexture information is incorrect\n");
	texture_path = ft_strdup(texture[1]);
	free_double_pointer(texture);
	return (texture_path);
}
