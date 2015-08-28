/**
 * Is caps on?
 * 
 * by Drahoslav Bednář
 * github.com/drahoslav7
 */

#include <stdio.h>
#include "tray.h"
#include "caps.h"


enum {
	MAIN = -1,
	EXIT = 0,
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
		set_icon(ICON_ON);
	} else {
		printf("caps is OFF\n");
		set_icon(ICON_OFF);
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
	}	
}

int main(int argc, char const *argv[]) {

	init((char*) L"IsCapsOn?");
	set_menu_item(ABOUT, (char*) L"by yo2.cz", true);
	set_menu_item(DELIM, (char*) L"", true);
	set_menu_item(EXIT, (char*) L"exit", false);

	SetCapsLockHook(false);
	native_loop();	
	return 0;
}
