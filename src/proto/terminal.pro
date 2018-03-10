/* terminal.c */
void ex_terminal(exarg_T *eap);
int term_write_session(FILE *fd, win_T *wp);
int term_should_restore(buf_T *buf);
void free_terminal(buf_T *buf);
void write_to_term(buf_T *buffer, char_u *msg, channel_T *channel);
int term_job_running(term_T *term);
int term_none_open(term_T *term);
int term_try_stop_job(buf_T *buf);
int term_in_normal_mode(void);
void term_enter_job_mode(void);
int send_keys_to_term(term_T *term, int c, int typed);
int terminal_is_active(void);
cursorentry_T *term_get_cursor_shape(guicolor_T *fg, guicolor_T *bg);
int term_use_loop(void);
int terminal_loop(int blocking);
void term_job_ended(job_T *job);
void term_channel_closed(channel_T *ch);
int term_update_window(win_T *wp);
int term_is_finished(buf_T *buf);
int term_show_buffer(buf_T *buf);
void term_change_in_curbuf(void);
int term_get_attr(buf_T *buf, linenr_T lnum, int col);
char_u *term_get_status_text(term_T *term);
int set_ref_in_term(int copyID);
void set_terminal_default_colors(int cterm_fg, int cterm_bg);
void f_term_dumpwrite(typval_T *argvars, typval_T *rettv);
int term_swap_diff(void);
void f_term_dumpdiff(typval_T *argvars, typval_T *rettv);
void f_term_dumpload(typval_T *argvars, typval_T *rettv);
void f_term_getaltscreen(typval_T *argvars, typval_T *rettv);
void f_term_getattr(typval_T *argvars, typval_T *rettv);
void f_term_getcursor(typval_T *argvars, typval_T *rettv);
void f_term_getjob(typval_T *argvars, typval_T *rettv);
void f_term_getline(typval_T *argvars, typval_T *rettv);
void f_term_getscrolled(typval_T *argvars, typval_T *rettv);
void f_term_getsize(typval_T *argvars, typval_T *rettv);
void f_term_getstatus(typval_T *argvars, typval_T *rettv);
void f_term_gettitle(typval_T *argvars, typval_T *rettv);
void f_term_gettty(typval_T *argvars, typval_T *rettv);
void f_term_list(typval_T *argvars, typval_T *rettv);
void f_term_scrape(typval_T *argvars, typval_T *rettv);
void f_term_sendkeys(typval_T *argvars, typval_T *rettv);
void f_term_setrestore(typval_T *argvars, typval_T *rettv);
void f_term_setkill(typval_T *argvars, typval_T *rettv);
void f_term_start(typval_T *argvars, typval_T *rettv);
void f_term_wait(typval_T *argvars, typval_T *rettv);
void term_send_eof(channel_T *ch);
int terminal_enabled(void);
/* vim: set ft=c : */
