/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:52:11 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 15:24:10 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

t_ar_hdr			*ret_ar_hdr(t_ar_hdr *ar_hdr)
{
	return ((t_ar_hdr*)((char *)ar_hdr + ft_atoi(ar_hdr->ar_size)
				+ sizeof(t_ar_hdr)));
}

t_mach_header_64	*ret_mach_header(t_ar_hdr *ar_hdr)
{
	return ((t_mach_header_64 *)((char *)ar_hdr + sizeof(t_ar_hdr)
				+ ft_atoi((char *)ar_hdr->ar_name + 3)));
}

void				print_error(char const *file_name, char const *error)
{
	ft_putstr_fd("nm: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putendl_fd(error, 2);
}

void				run_archive_files(t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata)
{
	if (!archive_files(mach_header_64, fmetadata))
		print_error(fmetadata->fname,
				" The file was not recognized as a valide object file\n");
}

void				file_error(int fd, t_stat buf, t_fmetadata *fmetadata)
{
	if (fstat(fd, &buf) == -1)
		print_error(fmetadata->fname, ": No such file or directory.");
	else if (S_ISDIR(buf.st_mode))
		print_error(fmetadata->fname, ": is a directory.");
	delete_file_metadata(fmetadata);
}
