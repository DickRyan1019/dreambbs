/*-------------------------------------------------------*/
/* proto.h      ( NTHU CS MapleBBS Ver 3.02 )            */
/*-------------------------------------------------------*/
/* target : prototype and macros                         */
/* create : 95/03/29                                     */
/* update : 95/12/15                                     */
/*-------------------------------------------------------*/

#ifndef PROTO_H
#define PROTO_H

/* Macros for implementation-defined attributes */
#include "attrdef.h"

#ifdef NO_SO
#include "so.h"
#endif

#ifdef M3_USE_PFTERM
#include "pfterm.h"
#endif

/* ----------------------------------------------------- */
/* External function declarations                        */
/* ----------------------------------------------------- */

/* OS */
char *genpasswd(char *pw, int mode);

/* ----------------------------------------------------- */
/* prototypes                                            */
/* ----------------------------------------------------- */

/* acct.c */
void logitfile(const char *file, const char *key, const char *msg);
void addmoney(int addend, const char *userid);
void addpoint1(int addend, const char *userid);
void addpoint2(int addend, const char *userid);
void keeplog(const char *fnlog, const char *board, const char *title, int mode);
int acct_load(ACCT *acct, const char *userid);
void acct_save(const ACCT *acct);
int acct_userno(const char *userid);
int acct_get(const char *msg, ACCT *acct);
void x_file(int mode, const char *const xlist[], const char *const flist[]);
int check_admin(const char *name);
void bitmsg(const char *msg, const char *str, int level);
unsigned int bitset(unsigned int pbits, int count, int maxon, const char *msg, const char *const perms[]);
void acct_show(const ACCT *u, int adm);
void bm_setup(ACCT *u, int adm);
void deny_log_email(const char *mail, time_t deny);
int add_deny(ACCT *u, int adm, int cross);
void acct_setup(ACCT *u, int adm);
int u_info(void);
int m_user(void);
int m_bmset(void);
int ban_addr(const char *addr);
void check_nckuemail(char *email);
int find_same_email(const char *mail, int mode);
int u_addr(void);
void su_setup(ACCT *u);
int u_setup(void);
int ue_setup(void);
int u_lock(void);
int u_xfile(void);
int m_newbrd(void);
void brd_edit(int bno);
int a_editbrd(void);
int u_verify(void);
/* bbsd.c */
void blog(const char *mode, const char *msg);
void u_exit(const char *mode);
GCC_NORETURN void abort_bbs(void);
/* board.c */
void brh_get(time_t bstamp, int bhno);
GCC_PURE int brh_unread(time_t chrono);
void brh_visit(int mode);
void brh_add(time_t prev, time_t chrono, time_t next);
void remove_perm(void);
int Ben_Perm(const BRD *bhdr, unsigned int ulevel);
GCC_PURE int bstamp2bno(time_t stamp);
void brh_load(void);
void brh_save(void);
void XoPost(int bno);
int Select(void);
int Class(void);
void check_new(BRD *brd);
int Favorite(void);
void board_main(void);
int Boards(void);
int brd_list(int reciper);
/* cache.c */
void sem_init(void);
void ushm_init(void);
void utmp_mode(int mode);
int utmp_new(const UTMP *up);
void utmp_free(void);
GCC_PURE UTMP *utmp_find(int userno);
GCC_PURE UTMP *pid_find(int pid);
int utmp_count(int userno, int show);
GCC_PURE int cmpclasstable(const void *ptr);
void classtable_free(void);
void classtable_main(void);
void bshm_init(void);
GCC_PURE int brd_bno(const char *bname);
GCC_PURE int observeshm_find(int userno);
void observeshm_load(void);
void observeshm_init(void);
void count_update(void);
void count_load(void);
void count_init(void);
void fwshm_load(void);
void fwshm_init(void);
void fshm_init(void);
int film_out(int tag, int row);
GCC_PURE UTMP *utmp_check(const char *userid);
/* edit.c */
void ve_string(const char *str);
const char *tbf_ask(int n);
FILE *tbf_open(int n);
void ve_backup(void);
void ve_recover(void);
void ve_header(FILE *fp);
int ve_subject(int row, const char *topic, const char *dft);
int vedit(char *fpath, int ve_op);
/* gem.c */
void brd2gem(const BRD *brd, HDR *gem);
int gem_gather(XO *xo);
void XoGem(const char *folder, const char *title, int level);
void gem_main(void);
/* mail.c */
void ll_new(void);
void ll_add(const char *name);
int ll_del(const char *name);
GCC_PURE int ll_has(const char *name);
void ll_out(int row, int column, const char *msg);
int bsmtp(const char *fpath, const char *title, const char *rcpt, int method);
int bsmtp_file(const char *fpath, const char *title, const char *rcpt);
int m_verify(void);
int m_total_size(void);
unsigned int m_quota(void);
int m_zip(void);
int m_query(const char *userid);
void m_biff(int userno);
int m_setforward(void);
int m_setmboxdir(void);
int hdr_reply(int row, const HDR *hdr);
int mail_external(const char *addr);
int mail_send(const char *rcpt, const char *title);
void mail_reply(HDR *hdr);
void my_send(const char *rcpt);
int m_send(void);
int mail_sysop(void);
int mail_list(void);
int tag_char(int chrono);
void hdr_outs(const HDR *hdr, int cc);
int mbox_send(XO *xo);
int mail_stat(int mode);
int mbox_check(void);
void mbox_main(void);
/* menu.c */
int pad_view(void);
void vs_head(const char *title, const char *mid);
void clear_notification(void);
void movie(void);
const char *check_info(const char *input);
GCC_NORETURN void menu(void);
/* more.c */
char *mgets(int fd);
void *mread(int fd, int len);
int more(const char *fpath, const char *footer);
/* post.c */
GCC_PURE int cmpchrono(const void *hdr);
int checksum_find(const char *fpath, int check, int state);
void btime_update(int bno);
void outgo_post(const HDR *hdr, const char *board);
void cancel_post(const HDR *hdr);
void move_post(HDR *hdr, const char *board, int by_bm);
void log_anonymous(const char *fname);
GCC_PURE int seek_log(const char *title, int state);
int getsubject(int row, int reply);
int post_cross(XO *xo);
void post_history(XO *xo, const HDR *fhdr);
int post_gem(XO *xo);
int post_tag(XO *xo);
int post_edit(XO *xo);
void header_replace(XO *xo, const HDR *hdr);
int post_title(XO *xo);
int post_ban_mail(XO *xo);
void record_recommend(int chrono, const char *text);
int post_resetscore(XO *xo);
int post_recommend(XO *xo);
int post_manage(XO *xo);
int post_write(XO *xo);
/* banmail.c */
int BanMail(void);
void post_mail(void);
/* talk.c */
const char *bmode(const UTMP *up, int simple);
GCC_PURE int is_boardpal(const UTMP *up);
GCC_PURE int is_pal(int userno);
GCC_PURE int is_banmsg(int userno);
void pal_cache(void);
void aloha_sync(void);
void pal_sync(const char *fpath);
int t_pal(void);
int t_bmw(void);
int bm_belong(const char *board);
int XoBM(XO *xo);
void my_query(const char *userid, int paling);
void bmw_edit(UTMP *up, const char *hint, BMW *bmw, int cc);
void bmw_reply(int replymode);
int pal_list(int reciper);
void aloha(void);
int t_loginNotify(void);
void loginNotify(void);
int t_recall(void);
void talk_save(void);
void bmw_save(void);
void bmw_rqst(void);
int t_message(void);
int t_pager(void);
int t_cloak(XO *xo);
int t_query(void);
void talk_rqst(void);
void talk_main(void);
int check_personal_note(int newflag, const char *userid);
void banmsg_cache(void);
void banmsg_sync(const char *fpath);
int t_banmsg(void);

/* bbslua.c */
int bbslua(const char *fpath);
int bbslua_isHeader(const char *ps, const char *pe);

/* bbsruby.c */
void run_ruby(const char *fpath);

/* visio.c */
void bell(void);
#ifdef M3_USE_PFTERM
void ochar(int ch);
void outl(int line, const char *msg);
void outr(const char *str);
void oflush(void);
#else
void move(int y, int x);
void move_ansi(int y, int x);
void refresh(void);
void clear(void);
void clrtoeol(void);
void clrtobot(void);
void outc(int ch);
void outs(const char *str);
void scroll(void);
void rscroll(void);
void save_foot(screenline *slp);
void restore_foot(const screenline *slp);
int vs_save(screenline *slp);
void vs_restore(const screenline *slp);
void clearange(int from, int to);
#endif  /* #ifdef M3_USE_PFTERM */

void getyx(int *y, int *x);
int expand_esc_star_visio(char *buf, const char *src, int szbuf);
void outx(const char *str);
void outz(const char *msg);
void outf(const char *str);
GCC_CHECK_FORMAT(1, 2) void prints(const char *fmt, ...);
void cursor_save(void);
void cursor_restore(void);
void vmsg_body(const char *msg);
int vmsg(const char *msg);
void zmsg(const char *msg);
void vs_bar(const char *title);
#ifndef M3_USE_PFTERM
void grayout(int y, int end, int level);
#endif  /* #ifndef M3_USE_PFTERM */
void add_io(int fd, int timeout);
int iac_count(const unsigned char *current);
int igetch(void);
BRD *ask_board(char *board, unsigned int perm, const char *msg);
int vget(int line, int col, const char *prompt, char *data, int max, int echo);
int vans(const char *prompt);
int vkey(void);

/* xover.c */
XO *xo_new(const char *path);
XO *xo_get(const char *path);
void xo_load(XO *xo, int recsiz);
void xo_fpath(char *fpath, const char *dir, HDR *hdr);
int hdr_prune(const char *folder, int nhead, int ntail, int post);
int xo_delete(XO *xo);
int Tagger(time_t chrono, int recno, int op);
void EnumTagHdr(HDR *hdr, const char *dir, int locus);
int AskTag(const char *msg);
int xo_uquery_lite(XO *xo);
int xo_uquery(XO *xo);
int xo_usetup(XO *xo);
int xo_getch(XO *xo, int ch);
void xover(int cmd);
void every_Z(void);
void every_U(void);
void every_B(void);
void every_S(void);
int xo_cursor(int ch, int pagemax, int num, int *pageno, int *cur, int *redraw);
/* favorite.c */
void favorite_main(void);
/* socket.c */
int Get_Socket(const char *site, int *sock);
int POP3_Check(const char *site, const char *account, const char *passwd);
int Ext_POP3_Check(const char *site, const char *account, const char *passwd);
#ifdef M3_USE_PMORE
/* pmore.c */
int pmore(const char *fpath, int promptend);
#endif  /* #ifdef M3_USE_PMORE */
/* popupmenu.c */
int popupmenu_ans(const char *const desc[], const char *title, int x, int y);
void popupmenu(MENU pmenu[], XO *xo, int x, int y);
void pmsg_body(const char *msg);
int pmsg(const char *msg);
int Every_Z_Screen(void);
/* window.c */
int popupmenu_ans2(const char *const desc[], const char *title, int x, int y);
void pmsg2_body(const char *msg);
int pmsg2(const char *msg);
/* myfavorite.c */
void brd2myfavorite(const BRD *brd, HDR *gem);
int MyFavorite(void);
int myfavorite_find_chn(const char *brdname);
void myfavorite_parse(char *fpath);
void myfavorite_main(void);
int class_add(XO *xo);

/* ----------------------------------------------------- */
/* macros                                                */
/* ----------------------------------------------------- */

#define dashd(fpath)    S_ISDIR(f_mode(fpath))
#define dashf(fpath)    S_ISREG(f_mode(fpath))

#define STR4(x)         ((x[0] << 24) + (x[1] << 16) + (x[2] << 8) + x[3])
                        /* Thor.980913: �O��precedence */

#endif                          /* PROTO_H */
