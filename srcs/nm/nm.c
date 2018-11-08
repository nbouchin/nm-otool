/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:34:00 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 14:40:05 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

t_mach_header_64	*ret_map(t_stat buf, int fd)
{
	return (mmap(NULL, buf.st_size,
				PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0));
}

int					check_map(t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata, t_stat buf)
{
	if (mach_header_64 == MAP_FAILED)
	{
		delete_data(mach_header_64, fmetadata, buf, fmetadata->fd);
		return (1);
	}
	return (0);
}

int					main(int argc, char **argv)
{
	int					nb_file;
	t_stat				buf;
	t_mach_header_64	*mach_header_64;
	t_fmetadata			*fmetadata;

	nb_file = 0;
	while (++nb_file < argc)
	{
		fmetadata = (t_fmetadata*)ft_memalloc(sizeof(t_fmetadata));
		fmetadata->fd = open(argv[nb_file], O_RDONLY);
		init_file_metadata(fmetadata, argc, argv, nb_file);
		if (fstat(fmetadata->fd, &buf) == -1 || S_ISDIR(buf.st_mode))
		{
			file_error(fmetadata->fd, buf, fmetadata);
			continue ;
		}
		mach_header_64 = ret_map(buf, fmetadata->fd);
		fmetadata->size = buf.st_size;
		if (check_map(mach_header_64, fmetadata, buf))
			continue ;
		if (is_out((char *)mach_header_64 + buf.st_size))
			return (-1);
		run_nm(mach_header_64, fmetadata, buf, fmetadata->fd);
	}
}
