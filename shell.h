#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct lliststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct lliststr
{
	int num;
	char *str;
	struct lliststr *next;
} listt_T;

/**
 *struct pass_infoo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct pass_infoo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	listt_T *env;
	listt_T *history;
	listt_T *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;	  /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} infoo_tT;

#define INFO_INIT                                                               \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infoo_tT *);
} builtin_table;

/* sa_hsh.c */
int hsh(infoo_tT *, char **);
int fi_pu(infoo_tT *);
void fi_cmd(infoo_tT *);
void fo_cmd(infoo_tT *);

/* sa_path.c */
int is_cmd(infoo_tT *, char *);
char *du_ch(char *, int, int);
char *f_pa(infoo_tT *, char *, char *);

/* sa_loophsh.c */
int loophsh(char **);

/* sa_err_string_functions.c */
void e_pu(char *);
int e_p_c(char);
int p_fd(char c, int fd);
int pu_fd(char *str, int fd);

/* sa_string_functions.c */
int str_leE(char *);
int str_mpP(char *, char *);
char *s_wiI(const char *, const char *);
char *str_catT(char *, char *);

/* sa_string_functions2.c */
char *str_py(char *, char *);
char *str_du(const char *);
void _puts(char *);
int _putchar(char);

/* sa_string_functions3.c */
char *str_nc(char *, char *, int);
char *str_at(char *, char *, int);
char *str_hr(char *, char);

/* sa_string_functions4.c */
char **str_tTT(char *, char *);
char **str_t2(char *, char);

/* sa_memory_functions */
char *me_s(char *, char, unsigned int);
void f_f(char **);
void *r_os(void *, unsigned int, unsigned int);

/* sa_memory_functions2.c */
int b_f(void **);

/* sa_more_functions.c */
int in_a(infoo_tT *);
int is_d(char, char *);
int is_a(int);
int a_t(char *);

/* sa_more_functions2.c */
int er_a(char *);
void pr_er(infoo_tT *, char *);
int pr_d(int, int);
char *co_n(long int, int, int);
void re_c(char *);

/* sa_builtin_emulators.c */
int my_e(infoo_tT *);
int my_c(infoo_tT *);
int my_h(infoo_tT *);

/* sa_builtin_emulators2.c */
int m_h(infoo_tT *);
int m_l(infoo_tT *);

/* sa_getline.c module */
ssize_t g_i(infoo_tT *);
int g_l(infoo_tT *, char **, size_t *);
void s_h(int);

/* sa_info.c module */
void c_i(infoo_tT *);
void s_i(infoo_tT *, char **);
void f_i(infoo_tT *, int);

/* sa_env.c module */
char *g_e(infoo_tT *, const char *);
int m_e(infoo_tT *);
int m_s_e(infoo_tT *);
int m_u_s_e(infoo_tT *);
int p_e_l(infoo_tT *);

/* sa_env2.c module */
char **ge_e(infoo_tT *);
int u_s_e(infoo_tT *, char *);
int s_e(infoo_tT *, char *, char *);

/* sa_file_io_functions.c */
char *g_h_f(infoo_tT *info);
int w_h(infoo_tT *info);
int r_h(infoo_tT *info);
int b_h_l(infoo_tT *info, char *buf, int linecount);
int r_hi(infoo_tT *info);

/* sa_liststr.c module */
listt_T *a_n(listt_T **, const char *, int);
listt_T *a_n_e(listt_T **, const char *, int);
size_t p_l_s(const listt_T *);
int d_n_a_i(listt_T **, unsigned int);
void f_l(listt_T **);

/* sa_liststr2.c module */
size_t l_l(const listt_T *);
char **l_t_s(listt_T *);
size_t p_l(const listt_T *);
listt_T *n_s_w(listt_T *, char *, char);
ssize_t g_n_i(listt_T *, listt_T *);

/* sa_chain.c */
int ischa(infoo_tT *, char *, size_t *);
void che_cha(infoo_tT *, char *, size_t *, size_t, size_t);
int rep_al(infoo_tT *);
int rep_v(infoo_tT *);
int rep_s(char **, char *);

#endif
