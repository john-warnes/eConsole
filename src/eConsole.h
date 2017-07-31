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

#define MAXCOMMANDSIZE 80
#define MAXCOMMANDCOUNT 10

typedef int(*command_handler)(void *args);

int Console_Add_Command(char *Label, command_handler Handler);
int Console_Process(char *command_line);
long Console_Process_Arg_As_Int(void *arg);
double Console_Process_Arg_As_Double(void *arg);


#endif /* __ECONSOLE_H__ */
