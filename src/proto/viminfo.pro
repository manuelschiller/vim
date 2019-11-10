/* viminfo.c */
int viminfo_error(char *errnum, char *message, char_u *line);
int read_viminfo(char_u *file, int flags);
void write_viminfo(char_u *file, int forceit);
int viminfo_readline(vir_T *virp);
char_u *viminfo_readstring(vir_T *virp, int off, int convert);
void viminfo_writestring(FILE *fd, char_u *p);
int barline_writestring(FILE *fd, char_u *s, int remaining_start);
void ex_viminfo(exarg_T *eap);
int read_viminfo_filemark(vir_T *virp, int force);
void prepare_viminfo_marks(void);
void finish_viminfo_marks(void);
void handle_viminfo_mark(garray_T *values, int force);
void write_viminfo_filemarks(FILE *fp);
int removable(char_u *name);
void write_viminfo_marks(FILE *fp_out, garray_T *buflist);
void copy_viminfo_marks(vir_T *virp, FILE *fp_out, garray_T *buflist, int eof, int flags);
/* vim: set ft=c : */
