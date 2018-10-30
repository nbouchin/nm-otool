/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_nm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 10:24:19 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/30 11:04:56 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_NM_H
# define LIBFT_NM_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <ar.h>
# include "../srcs/libft/includes/libft.h"

typedef struct mach_header_64		t_mach_header_64;
typedef struct mach_header			t_mach_header;
typedef struct fat_header			t_fat_header;
typedef struct fat_arch				t_fat_arch;
typedef struct load_command			t_load_command;
typedef struct segment_command_64	t_segment_command_64;
typedef struct segment_command		t_segment_command;
typedef struct stat					t_stat;
typedef struct section_64			t_section_64;
typedef struct section				t_section;
typedef struct symtab_command		t_symtab_command;
typedef struct nlist_64				t_nlist_64;
typedef struct nlist				t_nlist;
typedef struct ar_hdr				t_ar_hdr;

typedef struct						s_metadata
{
	int								nsect;
	t_section_64					*sectab;
	t_nlist_64						*symtab;
}									t_metadata;

typedef struct						s_fmetadata
{
	char							*fname;
	char							*subfile;
	int								argc;
	int								to_print;
}									t_fmetadata;

t_section_64						*get_section(t_load_command const
*load_command, t_mach_header_64 const *mach_header_64, t_metadata *metadata);
t_section_64						*get_big_section(t_load_command const
*load_command, t_mach_header_64 const *mach_header_64, t_metadata *metadata);
int									is_magic(uint32_t magic);
int									is_fat(uint32_t magic);
int									is_mach(uint32_t magic);
int									is_64bits(uint32_t magic);
int									is_32bits(uint32_t magic);
int									ft_nm(t_mach_header_64 const
		*mach_header_64, char const *fname, int const argc);
int									process_fat_header(t_fat_header const
		*fat_header, t_fmetadata *fmetadata);
int									process_header(t_mach_header_64 const
		*mach_header_64, uint32_t const magic, t_fmetadata *fmetadata);
void								print_symtab(t_load_command const
		*load_command, t_mach_header_64 const *mach_header_64,
		t_metadata const *metadata);
void								print_big_symtab(t_load_command const
		*load_command, t_mach_header_64 const *mach_header_64,
		t_metadata const *metadata);
t_nlist_64							*get_symtab(t_load_command const
		*load_command, t_mach_header_64 const *mach_header_64);
t_nlist_64							*get_big_symtab(t_load_command const
		*load_command, t_mach_header_64 const *mach_header_64);
int									archive_files(t_mach_header_64 const
		*mach_header_64, t_fmetadata *fmetadata);

#endif
