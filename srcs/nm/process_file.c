/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:47:37 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 14:40:30 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void				run_nm(t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata, t_stat buf, int fd)
{
	if (is_magic(mach_header_64->magic))
		run_regular_files(mach_header_64, fmetadata);
	else
		run_archive_files(mach_header_64, fmetadata);
	delete_data(mach_header_64, fmetadata, buf, fd);
}

void				init_file_metadata(t_fmetadata *fmetadata, int argc,
		char **argv, int nb_file)
{
	fmetadata->new_file = 1;
	fmetadata->fname = ft_strdup(argv[nb_file]);
	fmetadata->argc = argc;
	fmetadata->subfile = NULL;
	fmetadata->to_print = 1;
	fmetadata->alone = 0;
}

void				delete_file_metadata(t_fmetadata *fmetadata)
{
	free(fmetadata->fname);
	free(fmetadata);
}

void				delete_data(t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata, t_stat buf, int fd)
{
	delete_file_metadata(fmetadata);
	munmap(mach_header_64, buf.st_size);
	close(fd);
}

int					regular_files(t_mach_header_64 const *mach_header_64,
		t_fmetadata *fmetadata)
{
	if (is_fat(mach_header_64->magic))
		process_fat_header((t_fat_header*)mach_header_64, fmetadata);
	else
		process_header(mach_header_64, mach_header_64->magic, fmetadata);
	return (1);
}

int					archive_files(t_mach_header_64 const *mach_header_64,
		t_fmetadata *fmetadata)
{
	t_ar_hdr			*ar_hdr;
	t_mach_header_64	*mh_64;

	if (!ft_strncmp((char *)mach_header_64, ARMAG, SARMAG))
	{
		ar_hdr = (t_ar_hdr*)((char *)mach_header_64 + 8);
		while (42)
		{
			if (!ft_strncmp(ar_hdr->ar_fmag, ARFMAG, 2))
			{
				fmetadata->subfile = (char*)ar_hdr + sizeof(t_ar_hdr);
				mh_64 = ret_mach_header(ar_hdr);
				if (mh_64->cputype == CPU_TYPE_X86_64
						&& mh_64->cpusubtype != CPU_SUBTYPE_X86_64_H)
					regular_files(ret_mach_header(ar_hdr), fmetadata);
				ar_hdr = ret_ar_hdr(ar_hdr);
				if (!ft_strncmp((char *)ar_hdr, ARMAG, SARMAG))
					ar_hdr = (t_ar_hdr*)((char *)ar_hdr + 8);
			}
			else
				break ;
		}
		return (1);
	}
	return (0);
}

void				run_regular_files(t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata)
{
	regular_files(mach_header_64, fmetadata);
}
