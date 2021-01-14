#ifndef Functions_h
#define Functions_h
#define clear() printf("\033[H\033[J")

#include "Utilities.h"

#include <unistd.h>
#include <sys/wait.h>
#include <libgen.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/reboot.h>

int f_quit(char** args);

// ----------------------------- Andy ----------------------------- //

int f_search(char** args);
int f_clear(char** args);
int f_time(char** args);
int f_date(char** args);
int f_help(char** args);
int f_sysinfo(char** args);

// --------------------------- Cristina --------------------------- //

int f_ls(char** args);
int f_cd(char** args);
int f_pwd(char** args);
int f_touch(char** args);
int f_exec(char** args);
// si f_history din main.c

// -------------------------- Georgiana --------------------------- //

int f_mkdir(char** args);
int f_rm(char** args);
int f_cp(char** args);
int f_reboot(char** args);
int f_shutdown(char** args);


#endif /* Functions_h */
