/**
 * Module for automatical determining intended keyboard layout/language
 *
 */

#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

typedef int Lang;

#define EN 0
#define CS 1

extern void LangChange(Lang);
extern void ToggleAutoLang();
extern bool IsAutoLangEnabled();

void SetLangHook(bool);
