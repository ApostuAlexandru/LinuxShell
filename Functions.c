#include "Functions.h"

int f_quit(char** args) {
    return 0;
}

// ----------------------------- Andy ----------------------------- //

int f_clear(char** args) {

    printf("\x1b[H\x1b[J");
    return 1;
}

int f_search(char** args) {

    int pipe1[2];   // parinte -> copil
    int pipe2[2];   // copil -> parinte
    char input_str[100];
    pid_t p;

    if (pipe(pipe1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    if (pipe(pipe2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    printf("File name: ");
    scanf("%s", input_str);

    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "Fork Failed" );
        return 1;
    }

    if(p > 0)   
    {
        char answer[10];
        close(pipe1[0]);   
        write(pipe1[1], input_str, strlen(input_str)+1);
        close(pipe1[1]);    
        wait(NULL);  
        close(pipe2[1]);
        read(pipe2[0], answer, 10);
        printf("Answer is: %s\n", answer);
        close(pipe2[0]);
    }

    else    // copilul
    {
        struct dirent *de;
        char file_name[30];   
        char answer[10];
        DIR *dr = opendir(".");  
        close(pipe1[1]);    
        read(pipe1[0], file_name, 30);
        strcpy(answer, "Not found");
        if (dr == NULL)
        {
            printf("Could not open current directory!" );
            return 1;
        }
        while ((de = readdir(dr)) != NULL)
        {
            if(strcmp(file_name, de->d_name) == 0)
                strcpy(answer, "Found");
        }
        closedir(dr);
        close(pipe1[0]);
        close(pipe2[0]);
        write(pipe2[1], answer, 10);
        close(pipe2[1]);
        exit(0);
    }

    return 1;
}

int f_time(char** args) {

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("Time: %d:%d \n", tm->tm_hour, tm->tm_min);
    return 1;
}

int f_date(char** args) {

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("Date: %d-%d-%d \n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    return 1;
}

int f_help(char** args) {

    puts("\n ***Welcome to MyShell Help*** \n\n"
    "\nList of supported shell commands: \n"
    "\ncd \nls \npwd \nhelp \nhistory \nexec"
    "\ntime \ndate \nsysinfo \nclear \nsearch \nhelp"
    "\ncp \nmkdir \nrm \nshutdown \nreboot"
    "\nexit \nquit \nclose");
    printf("\nYou have been helped :)\n\n");
    return 1;
}

int f_sysinfo(char** args) {

    struct utsname username;
    int status = uname(&username);
    if(status == -1)
    {
        fprintf(stderr,"%s : uname(2) \n",strerror(errno));
        exit (1);
    }

    printf("\n System infomation: \n\n");
    printf(" System name = %s;\n", username.sysname);
    printf(" Node name = %s;\n", username.nodename);
    printf(" Machine = %s;\n", username.machine);
    printf(" Release = %s;\n", username.release);
    printf(" Version = %s;\n\n", username.version);
    return 1;
}


// --------------------------- Cristina --------------------------- //

int f_cd(char** args) {

  if (args[1] == NULL) {
      fprintf(stderr, "[Error] No argument given to \"cd\"\n");
  } else {
      if (chdir(args[1]) == -1) {
          perror("[Error] cd");
      }
  }

  return 1;
}

int f_ls(char** args) {

  DIR* p;
  struct dirent *dir_info;
  int empty = 0;

  p = opendir("./");
  dir_info = readdir(p);
  while(dir_info) {
      if(strcmp(dir_info->d_name, ".") != 0 && strcmp(dir_info->d_name, ".."))
          printf("%s ",dir_info->d_name);

      dir_info = readdir(p);
      empty ++;
      //printf("%d", empty);
  }

  if (empty == 2)
    printf("Empty directory");
  printf("\n");

  return 1;
}

int f_pwd(char** args) {
    char cwd[1024];

    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);

    return 1;
}

int f_touch(char **args) {
  FILE *fp;
  fp = fopen(args[1], "w");
  if ( fp == NULL)
    printf("[ERROR]: Could not create file");
  else
    printf("File created\n");
  return 1;
}

int f_exec(char** args) {
  char command[1024];

  int no_commands = num_args(args);
  if(no_commands <= 1 ) return 1;

  strcpy(command, args[1]);
  int i;
  for(i = 2; i < no_commands; i++) {
      strcat(command, " ");
      strcat(command, args[i]);
  }

  system(command);

  return 1;
}

// --------------------------- Georgiana --------------------------- //

int f_cp(char** args) {

    char ch, source_file[20], target_file[20];
    FILE *source, *target;

    //if(argc != 3) return 0;
    strcpy(source_file, args[1]);
    strcpy(target_file, args[2]);

    source = fopen(source_file, "r");

    if(source == NULL)
    {
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }

    target = fopen(target_file, "w");

    if(target == NULL)
    {
        fclose(source);
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }

    while((ch = fgetc(source)) != EOF)
        fputc(ch, target);

    printf("File copied successfully.\n");

    fclose(source);
    fclose(target);

    return 1;
}

int f_mkdir(char** args) {

  char temp[50];
  strcpy(temp, args[1]);
  if(mkdir(temp, 0777) == -1)
    printf("Unable to create directory! \n");
  else
    printf("Directory created successfully! \n");
  return 1;
}

int f_rm(char** args) {

    int delete_status;
    delete_status = unlink(args[1]);
    if( delete_status == 0)
          printf("File %s deleted successfully! \n" , args[1]);
   	else
      	  printf("Unable to delete the file! \n");

    return 1;
}

int f_shutdown(char** args) {
    sync();
    system("shutdown -P now");
    return 0;
}

int f_reboot(char** args) {
    sync();
    system("reboot");
    return(0);
}
