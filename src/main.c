/** ============================================================================
 *  @file  main.c
 *  @brief main function and eConsole Example
 *
 *  @author John Warnes
 *
 *  @internal
 *       Created:  31.Jul.2017
 *      Revision:  none
 *      Compiler:  gcc
 *  Organization:  Personal Project
 *     Copyright:  Copyright (c) 2017, John Warnes
 *
 * =============================================================================
 */

#include <stdio.h>
#include <string.h>

#include "eConsole.h"

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
