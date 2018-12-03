#ifndef FT_OTOOL_H
# define FT_OTOOL_H

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

// otool
void			otool(void *ptr, char *av, uint32_t filesize, void *tmp);

// otool_ar
void    archive_lib(void *ptr, char *av, uint32_t filesize, void *tmp);

// otool_Fat
void		fat_32(void *ptr);
void		fat_64(void *ptr);

// otool_macho
void macho_64(void *ptr, struct segment_command_64 *tmp);
void macho_32(void *ptr, struct segment_command *tmp);


// otool_errors
int fd_bug(char *av);
int object_bug(char *av);
int file_check(struct stat buf, char *av, int error);
int dir_bug(char *av);
int check_format(char *ptr, char *av);

// otool_display
void display_m64(struct section_64 *sect, char *header);
void display_m32(struct section *sect, char *header);

//otool_mask
void				mask_32(unsigned long long n);
void				mask_64(unsigned long long n);

#endif