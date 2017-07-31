/** ============================================================================
 *  @file  econ.cpp
 *  @brief Econsole
 *
 *  @author John Warnes
 *
 *  @internal
 *       Created:  27.Jul.2017
 *      Revision:  none
 *      Compiler:  gcc
 *  Organization:  Organization
 *     Copyright:  Copyright (c) 2017, John Warnes
 *
 * =============================================================================
 */
#define __USE_POSIX


#include <stdio.h>  // printf
#include <stdlib.h>
#include <stdint.h> // types

#include <string.h> // str funcs

#include "eConsole.h"

int command_count = 0;

struct command {
    char *label;
    command_handler handler;
};

struct command commands[MAXCOMMANDCOUNT];

int Console_Add_Command(char *Label, command_handler Handler)
{
    if (command_count >= MAXCOMMANDCOUNT) return -1;
    commands[command_count].label = Label;
    commands[command_count].handler = Handler;
    command_count++;
    return 0;
}

int Console_Process(char *command_line)
{
    int error = -1;
    for (int i=0; i<command_count; i++)
        if (strncmp(commands[i].label, command_line, strlen(commands[i].label)) == 0)
        {
            if (strchr(command_line,' ')==NULL)
                error = commands[i].handler("");
            else
                error = commands[i].handler( strchr(command_line,' ')+1 );
        }
    if (error==-1) 
    {
        printf("Command Not Found: %s\r\n", command_line);
        return -1;
    }
    return 0;
}

long Console_Process_Arg_As_Int(void *arg)
{
    if (arg == NULL) return 0;
    char *str = (char*) arg;

    if (str[0] >= '1' && str[0] <= '9') return atol(str);

    if (str[0] == '0')
    {
        if (str[1] >= '1' && str[1] <= '7')
            return strtol(str, NULL, 8);
        if (str[1] == 'B' || str[1] == 'B')
            return strtol(str, NULL, 2);
        if (str[1] == 'x' || str[1] == 'X')
            return strtol(str, NULL, 16);
    }

    printf("[Console_Process_Arg_As_Int] Error on arg: '%s\r\n' == $d", str);
    return 0;
}

double Console_Process_Arg_As_Double(void *arg)
{
    if (arg == NULL) return 0;
    return strtof((char *)arg, NULL);
}




int LOG(void *args)
{
    printf("[LOG]: %s\r\n", (char *)args);
    return 0;
}

int PrintTest(void *args)
{
    char arg[MAXCOMMANDSIZE+1];
    strncpy(arg,args,MAXCOMMANDSIZE);

    printf("PrintTest String: %s", arg);

    printf("[PrintTest]: %ld,", Console_Process_Arg_As_Int(strtok(arg ," ")));
    printf("%ld, ", Console_Process_Arg_As_Int(strtok(NULL ," ")));
    printf("%f, ", Console_Process_Arg_As_Double(strtok(NULL ," ")));
    printf("%f\r\n",   Console_Process_Arg_As_Double(strtok(NULL ," ")));

//    printf("[PrintTest]: %s\r\n",strtok(arg," ") );
      return 0;
}

int main(int argc, char *argv[])
{
    //char cmd[MAXCOMMANDSIZE+1];
    //cmd[MAXCOMMANDSIZE] = '\0';
    //

    Console_Add_Command("LOG",&LOG);
    Console_Add_Command("log",&LOG);
    Console_Add_Command("log",&LOG);

    int error = Console_Process("LOG 'LOG' TEST");

    if (error)
    {
        printf("Error Command not found or invalid: %d\r\n", error);
    }

    printf ("Numbers '123' = %ld\r\n",Console_Process_Arg_As_Int("123"));
    printf ("Numbers '07' = %ld\r\n",Console_Process_Arg_As_Int("07"));
    printf ("Numbers '0xA' = %ld\r\n",Console_Process_Arg_As_Int("0xA"));


    printf ("Numbers '1.2f' = %f\r\n",Console_Process_Arg_As_Double("1.2f"));
    printf ("Numbers '0.001' = %f\r\n",Console_Process_Arg_As_Double("0.001"));
    printf ("Numbers '3451.1456' = %f\r\n",Console_Process_Arg_As_Double("3451.1456"));


    printf ("Start Printtest\r\n");

    PrintTest("99 100 123 500\r\n");
    PrintTest("123 0xAA 10.123 0x0.00091\r\n");

    printf ("end of main\r\n");
    return 0;
}
