/** ============================================================================
 *  @file  eConsol.cpp
 *  @brief Econsole
 *
 *  @author John Warnes
 *
 *  @internal
 *       Created:  27.Jul.2017
 *      Revision:  none
 *      Compiler:  gcc
 *  Organization:  jwanres
 *     Copyright:  Copyright (c) 2017, John Warnes
 *
 * =============================================================================
 */

#include <stdio.h>  // printf
#include <stdlib.h> // ??
#include <stdint.h> // Types
#include <string.h> // Strings

#include "eConsole.h"


// Internal Command Line Buffer
char lineBuf[EC_COMMANDMAXSIZE+1] = "";
int  linePos = 0;


// Struct for holding commands and handlers
int eC_commandCount = 0; // Number of current commands
struct eC_command {      // Command Structure
    char *label;         // Command as a string
    eC_commandHandler handler; // Function handler for the command
};

// Array of the registered commands
struct eC_command eC_commands[EC_COMMANDMAXCOUNT];



//
// #### Functions 
//


/**
* @brief: Add one char to the internal line buffer if it has room
*
* @param: char character to add
*
* @return: int 0 success and -1 on line buffer full
*/
int eC_LineAddChar(char ch)
{
    if (linePos < EC_COMMANDMAXSIZE)
    {
        lineBuf[linePos++] = ch;
        return 0;
    }

    lineBuf[EC_COMMANDMAXSIZE] = '\0';
    return -1;
}


/**
* @brief: Remove one char from the internal line buffer if one exists
*
* @param: void
*
* @return: int always 0
*/
int eC_LineDelChar(void)
{
    if (linePos <= 0 || lineBuf[0] == '\0') return -1;
    lineBuf[--linePos] = '\0';
    return 0;
}


/**
* @brief: Process the internal Line as a completed command
*
* @param: void
*
* @return: 0 on success, -1 on command not found, else command error
*/
int eC_LineProcess(void)
{
    if (lineBuf[0] == '\0' || lineBuf[0] == '\n' || lineBuf[0] == '\r') return 0; // If no command reutrn did nothing successfully
    lineBuf[linePos] = '\0'; //Null Term the current line just in case
    return eC_ProcessCommandLine(lineBuf);
}


/**
* @brief: Attempt to match the current line to a command and complete it
*
* @param: void
*
* @return: char* pointer to the part of the command append to current line
*/
char* eC_LineComplete(void)
{
    lineBuf[linePos] = '\0';
    char *match = eC_CommandComplete(lineBuf);
    strncpy(lineBuf+linePos, match, EC_COMMANDMAXSIZE-linePos);
    linePos += strlen(match);
    if ( linePos > EC_COMMANDMAXSIZE ) linePos = EC_COMMANDMAXSIZE;
    return match;
}


/**
* @brief: Clear the internal line buffer
*
* @param: void
*
* @return: void
*/
void eC_LineClear(void)
{
    linePos=0;
    lineBuf[0] = '\0';
}


/**
* @brief: Add a command and function handler to the eConsole system
*
* @param: char *Label
*       : eC_commandHandler Handler pouinter to the function
*
* @return: -1 on no more room for commands 0 on success
*/
int eC_AddCommand(char *Label, eC_commandHandler Handler)
{
    if (eC_commandCount >= EC_COMMANDMAXCOUNT) return -1;
    eC_commands[eC_commandCount].label = Label;
    eC_commands[eC_commandCount].handler = Handler;
    eC_commandCount++;
    return 0;
}



/**
* @brief: Find command match for given command line, Note returns first match
*
* @param: char* The current partial command line to match
*
* @return: char* pointer to string with the reminder of a match or NULL on no match
*
* @example: eC_CommandComplete("Com"); might return "mand" if match was found for "Command"
*/
char* eC_CommandComplete(char *curCommandLine)
{
    int i;
    for (i=0; i<eC_commandCount; i++)
        if (strncmp(eC_commands[i].label, curCommandLine, strlen(curCommandLine)) == 0)
            return eC_commands[i].label + strlen(curCommandLine);
    return NULL;
}



/**
* @brief: Processes given string in the eConsole System as a commandLine
*
* @param: char* String containing the commandLine to process
*
* @return: 0 on success, -1 command not found, other error are command specific
*/
int eC_ProcessCommandLine(char *commandLine)
{
    int error = -1;
    int i;
    for (i=0; i<eC_commandCount; i++)
        if (strncmp(eC_commands[i].label, commandLine, strlen(eC_commands[i].label)) == 0)
        {
            if (strchr(commandLine,' ')==NULL)
            {
                error = eC_commands[i].handler("");
                break;
            }
            else
            {
                error = eC_commands[i].handler( strchr(commandLine,' ')+1 );
                break;
            }
        }
    if (error==-1) printf(" Command Not Found: '%s'\r\n", commandLine);
    return error;
}


/**
* @brief: covert a string into a Int, with support for Hex Oct and Binary Prefixes
*
* @param: char* pointer to NULL term string with arg
*
* @return: long converted value or 0 if unable to convert
*/
long eC_Arg2Int(void *arg)
{
    if (arg == NULL) return 0;
    char *str = (char*) arg;

    if (str[0] >= '1' && str[0] <= '9') return atol(str);

    if (str[0] == '0')
    {
        if (str[1] >= '1' && str[1] <= '7')
            return strtol(str, NULL, 8);
        if (str[1] == 'b' || str[1] == 'B')
            return strtol(str, NULL, 2);
        if (str[1] == 'x' || str[1] == 'X')
            return strtol(str, NULL, 16);
        return 0;
    }

    printf("[Error] 'Process_Arg_As_Int' Arg: '%s' int($d)\r\n", str);
    return 0;
}


/**
* @brief: covert a string into a Double
*
* @param: char* pointer to NULL term string with arg
*
* @return: double converted value or 0 if unable to convert
*/
double eC_Arg2Double(void *arg)
{
    if (arg == NULL) return 0;
    return strtof((char *)arg, NULL);
}


