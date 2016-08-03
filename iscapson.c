/**
 * Is caps on?
 *
 * with auto switch
 * 
 * by Drahoslav Bednář
 * github.com/drahoslav7
 */

#include <stdio.h>
#include "tray.h"
#include "caps.h"
#include "lang.h"


enum {
	MAIN = -1,
	EXIT = 0,
	LANG,
	ABOUT,
	DELIM,
} itemIds;

enum {
	ICON_OFF = 1,
	ICON_ON = 2,
} iconIds;

// required by caps module
void CapsLockChanged(){
	if(IsCapsLockOn()){
		printf("caps is ON\n");
		fflush(stdout);
		set_tray_icon(ICON_ON);
	} else {
		printf("caps is OFF\n");
		fflush(stdout);
		set_tray_icon(ICON_OFF);
	}
}

// required by lang module
void LangChange(Lang lang){
	switch (lang) {
		case EN:
			IsCapsLockOn() && (PressCapsLock(), 1);
			break;
		case CS:
			!IsCapsLockOn() && (PressCapsLock(), 1);
			break;
	}
}

// required by tray module
void tray_callback(int itemId) {
	switch (itemId) {
		case MAIN:
			PressCapsLock();
			break;
		case EXIT:
			exit_loop();
			break;
		case LANG:
			ToggleAutoLang();
			if (IsAutoLangEnabled()){
				set_tray_menu_item(LANG, (char*) L"disable autoswitch", false);
			} else {
				set_tray_menu_item(LANG, (char*) L"enable autoswitch", false);
			}
			break;

	}	
}

int main(int argc, char const *argv[]) {


	// init tray
	init_tray((char*) L"IsCapsOn?+");
	set_tray_menu_item(ABOUT, (char*) L"by yo2.cz", true);
	set_tray_menu_item(LANG, (char*) L"disable autoswitch", false);
	set_tray_menu_item(DELIM, (char*) L"", true);
	set_tray_menu_item(EXIT, (char*) L"exit", false);

	SetCapsLockHook(false);
	SetLangHook(false);
	native_loop();
	return 0;
}
