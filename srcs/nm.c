/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:34:00 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/18 09:31:39 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		ft_nm(t_mach_header *mach_header)
{
	if (mach_header->magic == FAT_CIGAM)
		fat_header(mach_header);
	else
		regular_header(mach_header);
	return (1);
}

int		main(int argc, char **argv)
{
	int				fd;
	int	nb_file;
	t_stat			buf;
	t_mach_header	*mach_header;

	nb_file = 0;
	while (++nb_file < argc) 
	{
		fd = open(argv[nb_file], O_RDONLY);
		if (fstat(fd, &buf) == -1)
		{
			printf("%s: No such file or directory.\n", argv[nb_file]);
			(nb_file + 1 < argc) ? ft_putendl("") : 0;
			continue ;
		}
		mach_header = mmap(NULL, buf.st_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
		if (mach_header == MAP_FAILED)
			return (0);
		(argc > 2) ? printf("%s:\n", argv[nb_file]) : 0;
		ft_nm(mach_header);
		munmap(mach_header, buf.st_size);
		close(fd);
		(nb_file + 1 < argc) ? ft_putendl("") : 0;
	}
}
