#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include <libft.h>
# include <ar.h>

typedef struct			s_data
{
	unsigned long long	value;
	char				*str;
	uint8_t				type;
	uint8_t				sect;
	struct s_data		*next;
}						t_data;



// nm_sections
char **get_section_64(char **load, struct segment_command_64 *seg, size_t filesize);

// nm_utility
int		check_format(void *ptr, char *av);

//  nm_errors
int	no_file(char *av);
void display_av(char *av);
int file_is_dir(char *av);
int unvalid_object(char *av);
int check_file(struct stat buf, char *av, int error);

// nm_macho
void macho_32(void *ptr);
void macho_64(void *ptr, uint32_t filesize);

// nm_fat
void fat_32(void *ptr);
void fat_64(void *ptr);

// nm_display
void display_m64(void *ptr, char **tab, struct symtab_command *sym, size_t filesize);

// nm_list
void			create_64(t_data **lt, char *str, struct nlist_64 array);


// nm_mask
void				mask_32(unsigned long long n);
void				mask_64(unsigned long long n);
// nm_ar
void    archive_lib(void *ptr, char *av, size_t filesize, void *tmp);

// nm_symbols
void display_symbol(t_data *lt, char **tab);

// nm_list_two
int		further_fill(t_data *tmp, t_data *init);
#endif