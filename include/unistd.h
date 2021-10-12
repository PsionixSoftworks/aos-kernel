#ifndef _UNISTD_H
#define _UNISTD_H

#ifndef _TYPES_H
#include <sys/types.h>
#endif

#include <kernel/kernel.h>

/* Values used by the access() function */
#ifndef ACCESS_VALUES
#define F_OK                    0
#define X_OK                    1
#define W_OK                    2
#define R_OK                    4
#endif

/* Values used by the lseek function */
#ifndef LSEEK_VALUES
#define SEEK_SET                0
#define SEEK_CUR                1
#define SEEK_END                2
#endif

/* The POSIX version we're under */
#ifndef _POSIX_VERSION
#define _POSIX_VERSION          199009L
#endif

/* Values used by stdio functions */
#ifndef STDIO_VALUES
#define STDIN_FILENO            0
#define STDOUT_FILENO           1
#define STDERR_FILENO           2
#endif

/* Define NULL here as stated in POSIX Standard */
#define NULL                    ((void *)0)

/* Configurable system variables */
#define _SC_ARG_MAX             1
#define _SC_CHILD_MAX           2
#define _SC_CLOCKS_PER_SEC      3
#define _SC_CLK_TCK             3
#define _SC_NGROUPS_MAX         4
#define _SC_OPEN_MAX            5
#define _SC_JOB_CONTROL         6
#define _SC_SAVED_IDS           7
#define _SC_VERSION             8
#define _SC_STREAM_MAX          9
#define _SC_TZNAME_MAX          10

/* Configurable path name variables */
#define _PC_LINK_MAX            1
#define _PC_MAX_CANON           2
#define _PC_MAX_INPUT           3
#define _PC_NAME_MAX            4
#define _PC_PATH_MAX            5
#define _PC_PIPE_BUF            6
#define _PC_NO_TRUNC            7
#define _PC_VDISABLE            8
#define _PC_CHOWN_RESTRICTED    9

#define _POSIX_NO_TRUNC         (-1)
#define _POSIX_CHOWN_RESTRICTED 1

KERNEL_API void _exit(int _status);
KERNEL_API int access(const char *_path, int _amode);
KERNEL_API unsigned int alarm(unsigned int _seconds);
KERNEL_API int chdir(const char *_path);
KERNEL_API int fchdir(int _fd);
KERNEL_API int chown(const char *_path, int _owner, int _group);
KERNEL_API int close(int _fd);
KERNEL_API char *ctermid(char *_s);
KERNEL_API char *cuserid(char *_s);
KERNEL_API int dup(int _fd);
KERNEL_API int dup2(int _fd1, int _fd2);
KERNEL_API int execl(const char *_path, const char *_arg, ...);
KERNEL_API int execle(const char *_path, const char *_arg, ...);
KERNEL_API int execlp(const char *_file, const char *_arg, ...);
KERNEL_API int execv(const char *_path, char *const _argv[]);
KERNEL_API int execve(const char *_path,  char *const _argv[], char *const _envp[]);

KERNEL_API int execvp(const char *_file, char *const _argv[]);
KERNEL_API pid_t fork(void);
KERNEL_API long fpathconf(int _fd, int _name);
KERNEL_API char *getcwd(char *_buf, size_t _size);
KERNEL_API gid_t getegid(void);
KERNEL_API uid_t geteuid(void);
KERNEL_API gid_t getgid(void);
KERNEL_API int getgroups(int _gidsetsize, gid_t _grouplist[]);
KERNEL_API char *getlogin(void);
KERNEL_API pid_t getpgrp(void);
KERNEL_API pid_t getpid(void);
KERNEL_API pid_t getppid(void);
KERNEL_API uid_t getuid(void);
KERNEL_API int isatty(int _fd);
KERNEL_API int link(const char *_existing, const char *_new);
KERNEL_API off_t lseek(int _fd, off_t _offset, int _whence);
KERNEL_API long pathconf(const char *_path, int _name);
KERNEL_API int pause(void);
KERNEL_API int pipe(int _filedes[2]);
KERNEL_API ssize_t read(int _fd, void *_buf, size_t _n);
KERNEL_API int rmrmdir(const char *_path);
KERNEL_API int setgid(int gid);
KERNEL_API int setpgid(pid_t _pid, pid_t _pgid);
KERNEL_API pid_t setsid(void);
KERNEL_API int setuid(int _uid);
KERNEL_API unsigned int sleep(unsigned int _seconds);
KERNEL_API long sysconf(int _name);
KERNEL_API pid_t tcgetpgrp(int _fd, pid_t _pgrp_id);
KERNEL_API char *ttyname(int _fd);
KERNEL_API int unlink(const char *_path);
KERNEL_API ssize_t write(int _fd, const void *_buf, size_t _n);

KERNEL_API int symlink(const char *_path1, const char *_path2);
KERNEL_API int getopt(int _argc, char **_argv, char *_opts);
extern char *optarg;
extern int optind, opterr, optopt;
KERNEL_API int usleep(useconds_t _useconds);

/* BEGIN MINIX SPECIFIC STUFF... */
KERNEL_API int brk(char *_addr);
KERNEL_API int chroot(const char *_name);
KERNEL_API int mknod(const char *_name, unsigned int _mode, int _addr);
KERNEL_API int mknod4(const char *_name, unsigned int _mode, int _addr, long _size);
KERNEL_API char *mktemp(char *_template);
KERNEL_API int mount(char *_spec, char *_name, int _flag);
KERNEL_API long ptrace(int _req, pid_t _pid, long _addr, long _data);
KERNEL_API char *sbrk(int _incr);
KERNEL_API int sync(void);
KERNEL_API int fsync(int _fd);
KERNEL_API int unmount(const char *_name);
KERNEL_API int reboot(int _how, ...);
KERNEL_API int gethostname(char *_hostname, size_t _len);
KERNEL_API int getdomainname(char *_domain, size_t _len);
KERNEL_API int ttyslot(void);
KERNEL_API int fttyslot(int _fd);
KERNEL_API char *crypt(const char *_key, const char *_salt);
KERNEL_API int getsysinfo(int _who, int _what, void *_where);
KERNEL_API int getprocnr(void);
KERNEL_API int findproc(char *proc_name, int *_proc_nr);
KERNEL_API int allocmem(unsigned long _size, unsigned long _base);

#define DEV_MAP     1
#define DEV_UNMAP   2
#define mapdriver(driver, device, style)    devctl(DEV_MAP, driver, device, style)
#define unmapdriver(driver, device, style)  devctl(DEV_UNMAP, driver, device, style)

KERNEL_API int devctl(int _ctl_req, int _driver, int _device, int _style);

KERNEL_API int getpagesize(void);
KERNEL_API int setgroups(int _ngroups, const gid_t *gidset);
/* END MINIX SPECIFIC STUFF... */
/* ^^^ MOST LIKELY TO BE REMOVED ^^^ */

KERNEL_API int readlink(const char *, char *, int);
KERNEL_API int getopt(int, char **, char *);


#endif
