/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:52:08 by qxia              #+#    #+#             */
/*   Updated: 2022/04/05 12:22:39 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>

int file_error(void)
{
	write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int main(int ac, char **av)
{
	FILE *fd;
	int fs;
	int bw;
	int bh;
	char bc;
	char type;
	float cx;
	float cy;
	float cr;
	char cc;
	int i;
	int j;

	if (ac == 2)
	{
		fd = fopen(av[1], "r");
		if (!fd)
			return (file_error());
		fs = fscanf(fd, "%d %d %c\n", &bw, &bh, &bc);
		if (fs != 3 || bw <= 0 || bh <= 0 || bw > 300 || bh > 300)
			return (file_error());
		char draw[bh][bw];		
		i = 0;
		while (i < bh)
		{
			j = 0;
			while (j < bw)
			{
				draw[i][j] = bc;
				j ++;
			}
			i ++;
		}
		fs = fscanf(fd, "%c %f %f %f %c\n", &type, &cx, &cy, &cr, &cc);
		if (fs != -1 && fs != 5)
			return (file_error());
		if (fs != -1 && ((type != 'C' && type != 'c') || cr <= 0))
			return (file_error());
		while (fs != -1)
		{
			i = 0;
			while (i < bh)
			{
				j = 0;
				while (j < bw)
				{
					float r = sqrtf(powf((i - cy), 2) + powf((j - cx), 2));
					if (r <= cr)
					{
						if (cr - r < 1)
							draw[i][j] = cc;
						if (type == 'C')
							draw[i][j] = cc;
					}
					j ++;
				}
				i ++;
			}
			fs = fscanf(fd, "%c %f %f %f %c\n", &type, &cx, &cy, &cr, &cc);
			if (fs != -1 && fs != 5)
				return (file_error());
			if (fs != -1 && ((type != 'C' && type != 'c') || cr <= 0))
				return (file_error());
		}
		i = 0;
		while (i < bh)
		{
			j = 0;
			while (j < bw)
			{
				write(1, &draw[i][j], 1);
				j ++;
			}
			write(1, "\n", 1);
			i ++;
		}
		return (0);
	}
	else
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
}

