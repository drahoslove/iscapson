#include "caps.h"

extern void CapsLockChanged();

static LRESULT keyHookProc(int nCode, WPARAM wParam, LPARAM lParam){
	if (nCode >= 0) {
		KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
		if (kbdStruct.vkCode == VK_CAPITAL) {
			CapsLockChanged();
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void PressCapsLock(){
	INPUT ip;
	ip.type = INPUT_KEYBOARD;

	ip.ki.wVk = VK_CAPITAL;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.dwFlags = 0; //kedown
	SendInput(1, &ip, sizeof(INPUT));
	
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void SetCapsLockHook(bool startLoop){
	CapsLockChanged();
	if (!SetWindowsHookExW(WH_KEYBOARD_LL, keyHookProc, NULL, 0)) {
		exit(1);
	}
	MSG msg;
	while (startLoop && !GetMessage(&msg, NULL, 0, 0)) { 
		//
	}
}

inline bool IsCapsLockOn(){
	SHORT state = GetKeyState(VK_CAPITAL);
	return ((state & 1) == 1);
}

