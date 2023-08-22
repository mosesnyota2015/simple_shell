#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* "environment" */
extern char **environ;
/**
 * struct data - holds runtime data
 * @av:  vector of arguments
 * @input: user inputs
 * @args: cmd tokens
 * @status: shell's last status
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: shell's process ID
 */
typedef struct data
{
	char **_environ;
	char *pid;
	char **av;
	char *input;
	char **args;
	int status;
	int counter;

} shell_data;

/**
 * struct seplist - singly linked list 
 * @separatr: ; | &
 * @next: next node
 * Description: stores separatrs
 */
typedef struct seplist
{
	char separatr;
	struct seplist *next;
} seplists;

/**
 * struct cmd_lines - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct cmd_lines
{
	char *line;
	struct cmd_lines *next;
} cmd_lines_list;

/**
 * struct rvarlist - single linked list
 * @len_var: variable length
 * @val: variable
 * @len_val: value length
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct rvarlist
{
	int len_var;
	char *val;
	int len_val;
	struct rvarlist *next;
} rvars;

/**
 * struct args_cmd_s - struct for command arguments.
 * @name: command name
 * @f: data type pointer function.
 */
typedef struct args_cmd_s
{
	char *name;
	int (*f)(shell_data *datash);
} args_builtin_cmd;


seplists *add_sep_end_node(seplists **head, char sep);
void free_seplist(seplists **head);
cmd_lines_list *add_line_end_node(cmd_lines_list **head, char *line);
void free_cmd_line_lst(cmd_lines_list **head);


rvars *addrvar_node(rvars **hd, int lvr, char *vr, int vall);
void freervarlist(rvars **head);

char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(shell_data *datash, char *input, int i, int bool);
int check_syntax_error(shell_data *datash, char *input);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(shell_data *datash);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(seplists **head_s, cmd_lines_list **head_l, char *input);
void go_next(seplists **list_s, cmd_lines_list **list_l, shell_data *datash);
int split_commands(shell_data *datash, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(rvars **h, char *in, shell_data *data);
int check_vars(rvars **h, char *in, char *st, shell_data *data);
char *replaced_input(rvars **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell_data *datash);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(shell_data *datash);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell_data *datash);
int check_error_cmd(char *dir, shell_data *datash);
int cmd_exec(shell_data *datash);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(shell_data *datash);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, shell_data *datash);
int _setenv(shell_data *datash);
int _unsetenv(shell_data *datash);

/* cd.c */
void cd_dot(shell_data *datash);
void cd_to(shell_data *datash);
void cd_previous(shell_data *datash);
void cd_to_home(shell_data *datash);

/* cd_shell.c */
int cd_shell(shell_data *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(shell_data *datash);

/* _exit.c */
int exit_shell(shell_data *datash);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(shell_data *, char *, char *, char *);
char *error_get_cd(shell_data *datash);
char *error_not_found(shell_data *datash);
char *error_exit_shell(shell_data *datash);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(shell_data *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(shell_data *datash);


/* get_error.c */
int get_error(shell_data *datash, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(shell_data *datash);

#endif
