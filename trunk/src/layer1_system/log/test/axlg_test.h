/**
* @file
* Axe 'log' test header
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

/* $Id: axlg_test.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
