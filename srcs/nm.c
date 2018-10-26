/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:34:00 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/26 14:24:59 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		ft_nm(t_mach_header_64 const *mach_header_64, char const *fname)
{
	if (is_fat(mach_header_64->magic))
		process_fat_header((t_fat_header*)mach_header_64, fname);
	else
		process_header(mach_header_64, mach_header_64->magic, fname);
	return (1);
}

void	print_error(char const *file_name, char const *error)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putendl_fd(error, 2);
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
			print_error(argv[nb_file], ": No such file or directory.");
			continue ;
		}
		if (S_ISDIR(buf.st_mode))
		{
			print_error(argv[nb_file], ": is a directory.");
			continue ;
		}
		mach_header_64 = mmap(NULL, buf.st_size, PROT_WRITE
				| PROT_READ, MAP_PRIVATE, fd, 0);
		if (mach_header_64 == MAP_FAILED)
		{
			munmap(mach_header_64, buf.st_size);
			continue ;
		}
		if (!is_magic(mach_header_64->magic))
		{
			munmap(mach_header_64, buf.st_size);
			print_error(argv[nb_file], " The file was not recognized as a valide object file\n");
		}
		else
		{
			(argc > 2) ? ft_printf("%s:\n", argv[nb_file]) : 0;
			ft_nm(mach_header_64, argv[nb_file]);
			munmap(mach_header_64, buf.st_size);
			close(fd);
			(nb_file + 1 < argc) ? ft_putendl("") : 0;
		}
	}
}
