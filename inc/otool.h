#ifndef  OTOOL_H
# define OTOOL_H

#include <universal.h>

// otool
void otool(void *ptr, char *av, size_t filesize);
// ar
void archive_lib(void *ptr, char *av, size_t filesize);
// fat
void do_fat_32(void *ptr, char *av);
void do_fat_64(void *ptr, char *av);
// loadcmd
void do_bits_64(void *ptr);
void do_bits_32(void *ptr);
// display
void display_m64(struct section_64 *sect, char *header);
void display_m32(struct section *sect, char *header);


#endif