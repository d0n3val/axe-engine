/**
* @file
* Axe 'input' test header
*/

// ---------------------------
#pragma once
#define WIN32_LEAN_AND_MEAN

// ---------------------------
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <MMSystem.h>

// ---------------------------
void error(int num, const char *file, long line);
int check_versions();
int main();
int start();
int loop();
int end();

/* $Id: axip_test.h,v 1.1 2004/06/09 18:23:57 doneval Exp $ */
