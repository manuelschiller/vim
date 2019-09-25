/* option.c */
void set_init_1(int clean_arg);
void set_string_default(char *name, char_u *val);
void set_number_default(char *name, long val);
void set_local_options_default(win_T *wp, int do_buffer);
void free_all_options(void);
void set_init_2(void);
void set_init_3(void);
void set_helplang_default(char_u *lang);
void init_gui_options(void);
void set_title_defaults(void);
int do_set(char_u *arg, int opt_flags);
void did_set_option(int opt_idx, int opt_flags, int new_value, int value_checked);
int string_to_key(char_u *arg, int multi_byte);
char *check_cedit(void);
void did_set_title(void);
void set_options_bin(int oldval, int newval, int opt_flags);
void check_options(void);
int get_term_opt_idx(char_u **p);
int set_term_option_alloced(char_u **p);
int was_set_insecurely(char_u *opt, int opt_flags);
void redraw_titles(void);
int valid_name(char_u *val, char *allowed);
char *check_clipboard_option(void);
void set_option_sctx_idx(int opt_idx, int opt_flags, sctx_T script_ctx);
void set_term_option_sctx_idx(char *name, int opt_idx);
void check_redraw(long_u flags);
int findoption(char_u *arg);
int get_option_value(char_u *name, long *numval, char_u **stringval, int opt_flags);
int get_option_value_strict(char_u *name, long *numval, char_u **stringval, int opt_type, void *from);
char_u *option_iter_next(void **option, int opt_type);
long_u get_option_flags(int opt_idx);
void set_option_flag(int opt_idx, long_u flag);
void clear_option_flag(int opt_idx, long_u flag);
int is_global_option(int opt_idx);
int is_global_local_option(int opt_idx);
int is_window_local_option(int opt_idx);
int is_hidden_option(int opt_idx);
int is_crypt_key_option(int opt_idx);
char *set_option_value(char_u *name, long number, char_u *string, int opt_flags);
char_u *get_term_code(char_u *tname);
char_u *get_highlight_default(void);
char_u *get_encoding_default(void);
int makeset(FILE *fd, int opt_flags, int local_only);
int makefoldset(FILE *fd);
void clear_termoptions(void);
void free_termoptions(void);
void free_one_termoption(char_u *var);
void set_term_defaults(void);
int istermoption_idx(int opt_idx);
void unset_global_local_option(char_u *name, void *from);
char_u *get_option_varp_scope(int opt_idx, int opt_flags);
char_u *get_option_var(int opt_idx);
char_u *get_option_fullname(int opt_idx);
char_u *get_equalprg(void);
void win_copy_options(win_T *wp_from, win_T *wp_to);
void after_copy_winopt(win_T *wp);
void copy_winopt(winopt_T *from, winopt_T *to);
void clear_winopt(winopt_T *wop);
void buf_copy_options(buf_T *buf, int flags);
void reset_modifiable(void);
void set_iminsert_global(void);
void set_imsearch_global(void);
void set_context_in_set_cmd(expand_T *xp, char_u *arg, int opt_flags);
int ExpandSettings(expand_T *xp, regmatch_T *regmatch, int *num_file, char_u ***file);
int ExpandOldSetting(int *num_file, char_u ***file);
int has_format_option(int x);
int shortmess(int x);
void vimrc_found(char_u *fname, char_u *envname);
void change_compatible(int on);
int option_was_set(char_u *name);
int reset_option_was_set(char_u *name);
void fill_breakat_flags(void);
int check_opt_wim(void);
int can_bs(int what);
void save_file_ff(buf_T *buf);
int file_ff_differs(buf_T *buf, int ignore_empty);
long get_scrolloff_value(void);
long get_sidescrolloff_value(void);
void find_mps_values(int *initc, int *findc, int *backwards, int switchit);
int briopt_check(win_T *wp);
unsigned int get_bkc_value(buf_T *buf);
int signcolumn_on(win_T *wp);
dict_T *get_winbuf_options(int bufopt);
int fill_culopt_flags(char_u *val, win_T *wp);
/* vim: set ft=c : */
