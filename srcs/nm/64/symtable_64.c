#include <nm.h>

static void add_symdata_64(t_symdata **p, struct nlist_64 *nlist, char *str)
{
    t_symdata *loc;

    loc = (t_symdata *)malloc(sizeof(t_symdata));
    loc->nsect = nlist->n_sect;
    loc->type = nlist->n_type & N_TYPE;
    loc->stab = nlist->n_type & N_STAB;
    loc->ext = nlist->n_type & N_EXT;
    loc->pext = nlist->n_type & N_PEXT;
    loc->value = ppc_64(nlist->n_value);
    loc->str = str;
    loc->next = *p;
    *p = loc;
}

static void process_symtable_64_2(struct symtab_command *sym, void *ptr, t_symdata **psymbols, size_t filesize)
{
    uint32_t                off;
    uint32_t                nbsyms;
    uint32_t                i;
    char                    *str;
    struct nlist_64         *nlist;
    t_symdata               *p;

    nbsyms = ppc_64(sym->nsyms);
    if (nbsyms == 0)
        return ;
    i = 0;
    p = *psymbols;
    nlist = (struct nlist_64 *)(ptr + (ppc_64(sym->symoff)));
    str = (char *)ptr + ppc_64(sym->stroff);
    while (i < nbsyms)
    {
        off = ppc_64(nlist[i].n_un.n_strx);
        if (off + sym->stroff > filesize)
            return ;
        add_symdata_64(&p, &nlist[i], str + off);
        *psymbols = p;
        i++;
    }
}

void process_symtable_64(struct load_command *lc, void *ptr, t_symdata **psymbols, size_t filesize)
{
    struct symtab_command *sym;

    sym = (struct symtab_command *)lc;
    process_symtable_64_2(sym, ptr, psymbols, filesize);
}