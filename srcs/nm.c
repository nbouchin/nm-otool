/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:34:00 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/23 12:30:24 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		ft_nm(t_mach_header_64 *mach_header_64)
{
	if (is_fat(mach_header_64->magic))
		process_fat_header((t_fat_header*)mach_header_64);
	else
		process_header(mach_header_64, mach_header_64->magic);
	return (1);
}

int		main(int argc, char **argv)
{
	int					fd;
	int					nb_file;
	t_stat				buf;
	t_mach_header_64	*mach_header_64;

	nb_file = 0;
	while (++nb_file < argc)
	{
		fd = open(argv[nb_file], O_RDONLY);
		if (fstat(fd, &buf) == -1)
		{
			ft_printf("%s: No such file or directory.\n", argv[nb_file]);
			(nb_file + 1 < argc) ? ft_putendl("") : 0;
			continue ;
		}
		mach_header_64 = mmap(NULL, buf.st_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
		if (mach_header_64 == MAP_FAILED)
		{
			munmap(mach_header_64, buf.st_size);
			continue ;
		}
		if (!is_magic(mach_header_64->magic))
		{
			munmap(mach_header_64, buf.st_size);
			ft_printf("nm: %s The file was not recognized as a valid object file\n", argv[nb_file]);
		}
		else
		{
			(argc > 2) ? ft_printf("%s:\n", argv[nb_file]) : 0;
			ft_nm(mach_header_64);
			munmap(mach_header_64, buf.st_size);
			close(fd);
			(nb_file + 1 < argc) ? ft_putendl("") : 0;
		}
	}
}
