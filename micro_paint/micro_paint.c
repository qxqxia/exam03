/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 09:48:33 by qxia              #+#    #+#             */
/*   Updated: 2022/04/05 11:36:08 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"

int error_file(void)//check file
{
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int main(int ac, char **av)
{
	FILE 	*fd;//fopen
	int	bw;
	int	bh;
	char	bc;
	int	fs;
	float	cx;
	float	cy;
	float	cw;
	float	ch;
	char	cc;
	char	type;//check 'R' or 'r'
	int	i;
	int	j;

	if (ac != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	fd = fopen(av[1],"r");
	if (!fd)
		return (error_file());
	fs = fscanf(fd, "%d %d %c\n", &bw, &bh, &bc);//la premiere ligne
	if (fs != 3 || bw <= 0 || bh <= 0 || bw > 300 || bh > 300)
		return (error_file());
	char draw[bh][bw];
	i = 0;
	while (i < bh)//draw background
	{
		j = 0;
		while (j < bw)
		{
			draw[i][j] = bc;
			j++;
		}
		i++;
	}
	fs = fscanf(fd, "%c %f %f %f %f %c\n", &type, &cx, &cy, &cw, &ch, &cc);// la 2eme ligne
	if (fs != -1 && fs != 6) // la 2eme ligne peut etre eof
		return (error_file());
	if (fs != -1 && (type != 'R' && type != 'r') || cw <= 0 || ch <= 0)
		return (error_file());
	while (fs != -1)
	{
		i = 0;//inside while loop
		while (i < bh)
		{
			j = 0;
			while (j < bw)
			{
				if (i >= cy && i <= cy + ch && j >= cx && j <= cw + cx)
				{
					if (i - cy < 1 || cy + ch - i < 1 || j - cx < 1 || cx + cw - j < 1)
						draw[i][j] = cc;
					if (type == 'R')
						draw[i][j] = cc;
				}
				j++;
			}
			i++;
		}
		fs = fscanf(fd, "%c %f %f %f %f %c\n", &type, &cx, &cy, &cw, &ch, &cc);
		if (fs != -1 && fs != 6)
			return (error_file());
		if (fs != -1 && (type != 'R' && type != 'r') || cw <= 0 || ch <= 0)
			return (error_file());
	}
	i = 0;//imprimer a la fin
	while (i < bh)
	{
		j = 0;
		while(j < bw)
		{
			write (1, &draw[i][j], 1);
			j++;
		}
		write (1, "\n", 1);
		i++;
	}
	return (0);
}
