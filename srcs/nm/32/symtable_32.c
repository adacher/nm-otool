#include <ft_nm.h>

static void add_symdata_32(t_symdata **p, struct nlist *nlist, char *str)
{
    t_symdata *loc;

    loc = (t_symdata *)malloc(sizeof(t_symdata));
    loc->nsect = nlist->n_sect;
    loc->type = nlist->n_type & N_TYPE;
    loc->stab = nlist->n_type & N_STAB;
    loc->ext = nlist->n_type & N_EXT;
    loc->value = nlist->n_value;
    loc->str = str;
    loc->next = *p;
    *p = loc;
}

static void process_symtable_32_2(struct symtab_command *sym, void *ptr, t_symdata **psymbols, size_t filesize)
{
    uint32_t                off;
    uint32_t                nbsyms;
    uint32_t                i;
    char                    *str;
    struct nlist            *nlist;
    t_symdata               *p;

    nbsyms = sym->nsyms;
    if (nbsyms == 0)
        return ;
    i = 0;
    p = *psymbols;
    nlist = (struct nlist *)(ptr + sym->symoff);
    str = (char *)ptr + sym->stroff;
    while (i < nbsyms)
    {
        off = nlist[i].n_un.n_strx;
        if (off > filesize)
            return ;
        add_symdata_32(&p, &nlist[i], str + off);
        *psymbols = p;
        i++;
    }
}

void process_symtable_32(struct load_command *lc, void *ptr, t_symdata **psymbols, size_t filesize)
{
    struct symtab_command *sym;

    sym = (struct symtab_command *)lc;
    process_symtable_32_2(sym, ptr, psymbols, filesize);
}