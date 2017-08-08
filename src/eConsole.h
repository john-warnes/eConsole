/** ============================================================================
 *  @file  eConsole.h
 *  @brief Description
 *
 *  @author Full Name
 *
 *  @internal
 *       Created:  31.Jul.2017
 *      Revision:  none
 *      Compiler:  gcc
 *  Organization:  Organization
 *     Copyright:  Copyright (c) 2017, Full Name
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 * =============================================================================
 */

#ifndef __ECONSOLE_H__
#define __ECONSOLE_H__

#define EC_COMMANDMAXSIZE 80
#define EC_COMMANDMAXCOUNT 30

typedef int(*eC_commandHandler)(void *args);

int eC_AddCommand(char *Label, eC_commandHandler Handler);
int eC_ProcessCommandLine(char *commandLine);
long eC_Arg2Int(void *arg);
double eC_Arg2Double(void *arg);
char* eC_CommandComplete(char *curCommandLine);

int eC_LineAddChar(char ch);
int eC_LineDelChar(void);
int eC_LineProcess(void);
char* eC_LineComplete(void);
void eC_LineClear(void);

extern char lineBuf[EC_COMMANDMAXSIZE+1];
extern int linePos;

#endif /* __ECONSOLE_H__ */
