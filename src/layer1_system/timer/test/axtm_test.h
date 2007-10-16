/**
* @file
* Axe 'timer' test header
*/

// ---------------------------
#pragma once
#define WIN32_LEAN_AND_MEAN

// ---------------------------
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// ---------------------------
void error(int num, const char *file, long line);
int check_versions();
int main();

/* $Id: axtm_test.h,v 1.1 2004/05/02 16:32:32 doneval Exp $ */
