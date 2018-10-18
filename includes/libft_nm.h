#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "../srcs/libft/includes/libft.h"

typedef struct mach_header_64		t_mach_header_64;
typedef struct mach_header			t_mach_header;
typedef struct fat_header			t_fat_header;
typedef struct fat_arch				t_fat_arch;
typedef struct load_command 		t_load_command;
typedef struct segment_command_64	t_segment_command_64;
typedef struct segment_command		t_segment_command;
typedef struct stat					t_stat;
typedef struct section_64			t_section_64;
typedef struct section				t_section;
typedef struct symtab_command		t_symtab_command;
typedef struct nlist_64				t_nlist_64;
typedef struct nlist				t_nlist;

int									ft_nm(t_mach_header_64 *mach_header_64);
int									fat_header(t_fat_header *fat_header);
int									regular_header(t_mach_header_64 *mach_header_64);
void								print_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64, t_nlist_64 *symtab);
t_nlist_64							*get_symtab(t_load_command *load_command, t_mach_header_64 *mach_header_64);
