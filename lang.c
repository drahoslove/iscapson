#include "lang.h"
#include "buffer.h"

const int BUFF_SIZE = 25;

bool autoChangeEnabled;
Buffer buffer;
long int lastTime;

/**
 * return number determining (guessing) if user intended to write numeric or diacritics
 * @param  buffer   cyclic buffer of few last typed character
 * @return          probability
 *                  1.0 = definitely diacritics
 *                  0.0 = absolutely not
 *                  0.5 = maybe
 */
float getProbabilityOfDiacritics(Buffer* buffer){
	float probability = 0.5;

	// TODO improve!
	
	if(isalpha(getNthInbuffer(buffer, 1))){
		probability += (1-probability) * 0.5;
		if(isalpha(getNthInbuffer(buffer, 2))){
			probability *= (1-probability) * 0.5;
			if(isalpha(getNthInbuffer(buffer, 3))){
				probability += (1-probability) * 0.5;
			}
		}
	} else if (
		isdigit(getNthInbuffer(buffer, 0)) &&
		isdigit(getNthInbuffer(buffer, 1)) &&
		isdigit(getNthInbuffer(buffer, 2)) &&
		isdigit(getNthInbuffer(buffer, 3))
	){
		probability *= 0;
	}
	return probability;
}

static LRESULT keyHookProc(int code, WPARAM wParam, LPARAM lParam){
	KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
	if (code >= 0) {
		if (wParam == WM_KEYDOWN && kbdStruct.vkCode != VK_CAPITAL) {
			if(
				1 || // save all
				kbdStruct.vkCode >= '0' && kbdStruct.vkCode <= '9' ||
				kbdStruct.vkCode >= 'A' && kbdStruct.vkCode <= 'Z' ||
				kbdStruct.vkCode == ' '
			){
				if (kbdStruct.time - lastTime > 320) { // too long iddle, forgot eveything
					emptyBuffer(&buffer);
				}

				pushBuffer(&buffer, kbdStruct.vkCode);

				if (autoChangeEnabled && kbdStruct.vkCode >= '0' && kbdStruct.vkCode <= '9') {
					float diacritics = getProbabilityOfDiacritics(&buffer);
					if (diacritics >= 0.75) {
						LangChange(CS);
					}
					if (diacritics <= 0.0) {
						LangChange(EN);
					}
				}

				lastTime = kbdStruct.time; 
			}
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}


void SetLangHook(bool startLoop){
	initBuffer(&buffer, BUFF_SIZE);
	lastTime = 0;
	autoChangeEnabled = true;
	if (!SetWindowsHookExW(WH_KEYBOARD_LL, keyHookProc, NULL, 0)) {
		exit(1);
	}
	MSG msg;
	while (startLoop && GetMessage(&msg, NULL, 0, 0)) { 
		TranslateMessage(&msg);
        DispatchMessage(&msg);
	}
}


void ToggleAutoLang(){
	autoChangeEnabled = !autoChangeEnabled;
}

bool IsAutoLangEnabled(){
	return autoChangeEnabled;
}