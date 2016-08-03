/**
 * Module for work with caps lock
 *
 * callback funciton void CapsLockChanged() has to be defined
 * and will be called whenever CapsLock is pressed
 */

#include <Windows.h>
#include <stdbool.h>

extern void CapsLockChanged();

void SetCapsLockHook(bool);
void PressCapsLock();
bool IsCapsLockOn();