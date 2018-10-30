/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:34:00 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/30 12:45:25 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		regular_files(t_mach_header_64 const *mach_header_64, t_fmetadata *fmetadata)
{
	if (is_fat(mach_header_64->magic))
		process_fat_header((t_fat_header*)mach_header_64, fmetadata);
	else
		process_header(mach_header_64, mach_header_64->magic, fmetadata);
	return (1);
}

int		archive_files(t_mach_header_64 const *mach_header_64, t_fmetadata *fmetadata)
{
	t_ar_hdr			*ar_hdr;

	if (!ft_strncmp((char *)mach_header_64, ARMAG, SARMAG))
	{
		ar_hdr = (t_ar_hdr*)((char *)mach_header_64 + 8);
		while (42)
		{
			if (!ft_strncmp(ar_hdr->ar_fmag, ARFMAG, 2))
			{
				fmetadata->subfile = (char*)ar_hdr + 60;
				regular_files((t_mach_header_64 *)((char *)ar_hdr
				+ 60 + ft_atoi((char *)ar_hdr->ar_name + 3)), fmetadata);
				ar_hdr = (t_ar_hdr*)((char *)ar_hdr + ft_atoi(ar_hdr->ar_size) + 60);
			}
			else
				break ;
		}
		return (1);
	}
	return (0);
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
	t_fmetadata			*fmetadata;

	nb_file = 0;
	while (++nb_file < argc)
	{
		fd = open(argv[nb_file], O_RDONLY);
		fmetadata = (t_fmetadata*)ft_memalloc(sizeof(t_fmetadata));
		fmetadata->fname = ft_strdup(argv[nb_file]);
		fmetadata->argc = argc;
		fmetadata->subfile = NULL;
		fmetadata->to_print = 1;
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
		if (is_magic(mach_header_64->magic))
		{
			regular_files(mach_header_64, fmetadata);// TODO: free fmetadata.
			free(fmetadata);
			munmap(mach_header_64, buf.st_size);
			close(fd);
		}
		else
		{
			if (archive_files(mach_header_64, fmetadata))
			{
				free(fmetadata);
				munmap(mach_header_64, buf.st_size);
			}
			else
			{
				munmap(mach_header_64, buf.st_size);
				print_error(argv[nb_file], " The file was not recognized as a valide object file\n");
			}
		}
	}
}
