#include "Utilities.h"
#include "Functions.h"

char** shellHistory;
int cmdMax = 128, cmdCount = 0;

void history_update( char* cmd ) {

    int i;
    for( i = cmdMax - 1; i > 0; i-- ) {
        strcpy( shellHistory[i], shellHistory[i-1] );
    }

    strcpy( shellHistory[0], cmd );

    if( cmdCount < 128 )
      cmdCount++;
}

int f_history( char** args ) {

    int i;
    for( i = 0; i < cmdCount; i++ )
        printf( "%s \n", shellHistory[i] );

    return 1;
}

// ------------------------ Functii ------------------------ //

char *f_list[] = {

    //  Exit Shell Commands ( apeleaza aceeasi functie)
    "close", "exit", "quit",

    // ------------------------ Andy ------------------------ //
    "search", "clear", "time", "date", "help", "sysinfo",

    // ---------------------- Cristina ---------------------- //
    "ls", "cd", "pwd", "touch", "exec", "history",

    // --------------------- Georgiana ---------------------- //
    "mkdir", "rm", "cp", "reboot", "shutdown"

};

int ( *f_pointers[] )(char **) = {
    &f_quit, &f_quit, &f_quit,
    &f_search, &f_clear, &f_time, &f_date, &f_help, &f_sysinfo,
    &f_ls, &f_cd, &f_pwd, &f_touch, &f_exec, &f_history,
    &f_mkdir, &f_rm, &f_cp, &f_reboot, &f_shutdown
};

//

int search_and_execute( char** args ) {

    if ( args[0] == NULL ) {
        return 1;
    }

    int i, numberOfFunctions;
    numberOfFunctions = sizeof(f_list) / sizeof(f_list[0]);

    for ( i = 0; i < numberOfFunctions; i++ ) {
        if ( strcmp( args[0], f_list[i] ) == 0 ) {
            return ( *f_pointers[i] )(args);   
        }
    }

    printf( "Command not found...\n" );
    return 1;
}

void startup_message() {

    clear();
    printf("\n\n  ****************");
    printf("\n\n      My Shell \n\n");
    printf("  ****************\n\n");
    char *username = getenv("USER");
    printf("\nCurrent user is: @%s", username);
    printf("\n\n");
    //sleep(1);
}

int main(int argc, char** argv) {

    char *line;
    char **argVector;
    int flag = 1;

    shellHistory = malloc(cmdMax * sizeof(char*));
    int i;
    for(i = 0; i < cmdMax; i++)
      shellHistory[i] = malloc(1024 * sizeof(char));

    startup_message();

    while(flag) {

        printf("LinuxShell >: ");

        line = read_line(stdin);
        argVector = split_line(line);

        history_update(line);

        flag = search_and_execute(argVector);

        free(line);
        free(argVector);
    }

    return EXIT_SUCCESS;
}
