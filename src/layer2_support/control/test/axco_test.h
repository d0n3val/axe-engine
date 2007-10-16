/**
* @file
* Axe 'control' test header
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

/* $Id: axco_test.h,v 1.2 2004/07/21 22:08:52 doneval Exp $ */
