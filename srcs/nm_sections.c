#include <ft_nm.h>

static int check_1(char **load, char **tmp)
{
    int i;

    i = 0;
    while (load && load[i])
    {
        if (tmp[i] != load[i])
            tmp[i] = load[0];
        i++;
    }
    return (i);
}

static void check_2(char **tmp, int i, struct section_64 *sec, struct segment_command_64 *seg)
{
    int y;

    y = 0;
    while (y < (int)seg->nsects)
    {
        if (tmp[i] != sec->sectname)
            tmp[i] = sec->sectname;
        sec++;
        i++;
        y++;
    }
}

char **get_section_64(char **load, struct segment_command_64 *seg)
{
    int i;
    struct section_64 *sec;
    char **tmp;

    i = 0;
    sec = (struct section_64*)(seg + 1);
    if (seg->nsects <= 0)
        return (load);
    while (load && load[i])
		i++;
    tmp = (char**)malloc(sizeof(char*) * ((int)seg->nsects + i + 1));
    tmp[seg->nsects + i] = 0;
    i = check_1(load, tmp);
    check_2(tmp, i, sec, seg);
    free(load);
    return (tmp);
}
