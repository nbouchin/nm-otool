/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_nm.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 10:24:19 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 15:46:02 by nbouchin         ###   ########.fr       */
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
	char							*end;
	int								nsect;
	t_section_64					*sectab;
	t_nlist_64						*symtab;
}									t_metadata;

typedef struct						s_fmetadata
{
	size_t							size;
	int								fd;
	int								new_file;
	char							*fname;
	char							*subfile;
	int								argc;
	int								to_print;
	int								alone;
}									t_fmetadata;

t_section_64						*get_section(
		t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64, t_metadata *metadata);
t_section_64						*otool_get_section(
		t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64, t_metadata *metadata);
t_section_64						*get_big_section(
		t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64,
		t_metadata *metadata);
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
void								print_cputype(
		t_mach_header_64 const *mach_header_64,
		int pass, t_fmetadata *fmetadata);
uint32_t							swi(uint32_t x);
int									is_out(char *offset);

t_section_64						*sectab_realloc(t_section_64 *sectab,
		size_t new_size, uint32_t old_size);

t_section_64						*alloc_sectab_64(t_section_64 *sectab,
		t_metadata *metadata, t_segment_command_64 const *sc_64);

t_section_64						*alloc_sectab(
		t_mach_header_64 const *mach_header_64, t_section_64 *sectab,
		t_metadata *mdata, t_segment_command const *sc);

void								process_symtab(t_metadata *mdata,
		t_mach_header_64 const *mach_header_64,
		t_load_command *lcommand, int flag);

void								print_symbol_32(uint64_t const n_value,
		char const letter, char const *symname, t_metadata const *metadata);
void								print_symbol_64(uint64_t const n_value,
		char const letter, char const *symname, t_metadata const *metadata);

char								get_type_char(t_metadata const *mdata,
		int const i);
char								*get_st(char *string_table,
		t_metadata const *metadata, int i);
void								get_symbol(uint64_t const n_value,
		char const *symbol_name, t_metadata const *metadata, int const i);

void								gsym_64(uint64_t const n_value,
		char const *symbol_name, t_metadata const *metadata, int const i);
char								*bst(char *string_table,
		t_metadata const *metadata, int i);
t_ar_hdr							*ret_ar_hdr(t_ar_hdr *ar_hdr);
t_mach_header_64					*ret_mach_header(t_ar_hdr *ar_hdr);
void								delete_file_metadata(
		t_fmetadata *fmetadata);
void								delete_data(
		t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata, t_stat buf, int fd);
void								file_error(int fd, t_stat buf,
		t_fmetadata *fmetadata);
void								run_nm(t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata, t_stat buf, int fd);
int									regular_files(
		t_mach_header_64 const *mach_header_64, t_fmetadata *fmetadata);
void								run_archive_files(
		t_mach_header_64 *mach_header_64, t_fmetadata *fmetadata);
void								run_regular_files(
		t_mach_header_64 *mach_header_64, t_fmetadata *fmetadata);
void								init_file_metadata(
		t_fmetadata *fmetadata, int argc, char **argv, int nb_file);
t_section_64						*get_current_section(
		t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64);
t_section_64						*get_sectab(
		t_load_command const *load_command,
		t_mach_header_64 const *mach_header_64, t_metadata *metadata);
void								print_error_fd(char const *file_name,
		char const *error, int fd);
void								print_section(
		t_mach_header_64 const *mach_header_64, t_section_64 *section);
void								print_section_32(
		t_mach_header_64 const *mach_header_64, t_section_64 *section);
void								print_big_section_32(
		t_mach_header_64 const *mach_header_64, t_section_64 *section);

#endif
