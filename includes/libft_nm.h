#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "../srcs/libft/includes/libft.h"

typedef struct mach_header_64		t_mach_header;
typedef struct load_command 		t_load_command;
typedef struct segment_command_64	t_segment_command;
typedef struct stat					t_stat;
typedef struct section_64			t_section;
typedef struct symtab_command		t_symtab_command;
typedef struct nlist_64				t_nlist;
