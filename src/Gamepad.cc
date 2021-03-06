#include "Gamepad.h"
#include <windows.h>

Gamepad::Gamepad() {
    /* create the path to xinput1_4.dll standard install location */
    char xinput_dll_path[MAX_PATH];
    memset(xinput_dll_path, 0, MAX_PATH);
    GetSystemDirectory(xinput_dll_path, sizeof(xinput_dll_path));
    memcpy(xinput_dll_path + strlen(xinput_dll_path), "\\xinput1_4.dll", 14);

    /* load the dll at runtime */
    xinput_dll = LoadLibrary(xinput_dll_path);

    /* load ordinal 100 */
    XInputGetState = (XINPUT_GET_STATE) GetProcAddress(xinput_dll, (LPCSTR)100); 

    for (int i = 0; i < MAX_PLAYERS; i++) {
        connected_list[i] = false;
    }
}

Gamepad::~Gamepad() {
    /* unload the dll */
    FreeLibrary(xinput_dll);
}

void Gamepad::update() {
    /* update all controller states */
    for (int i = 0; i < MAX_PLAYERS; i++) {
        connected_list[i] = XInputGetState(i, &state[i]) ?
        false : true;
    }   
}

bool Gamepad::connected(int player) {
    return VALID_PLAYER(player) ?
    connected_list[player] :
    false;
}

unsigned long Gamepad::eventCount(int player) {
    return VALID_PLAYER(player) ?
    state[player].eventCount : 0;
}

unsigned short Gamepad::buttons(int player) {
    return VALID_PLAYER(player) ?
    state[player].buttons : 0;

}

unsigned char Gamepad::leftTrigger(int player) {
    return VALID_PLAYER(player) ?
    state[player].leftTrigger : 0;
}

unsigned char Gamepad::rightTrigger(int player) {
    return VALID_PLAYER(player) ?
    state[player].rightTrigger : 0;
}

short int Gamepad::thumbLX(int player) {
    return VALID_PLAYER(player) ?
    state[player].thumbLX : 0;
}

short int Gamepad::thumbLY(int player) {
    return VALID_PLAYER(player) ?
    state[player].thumbLY : 0;
}

short int Gamepad::thumbRX(int player) {
    return VALID_PLAYER(player) ?
    state[player].thumbRX : 0;
}

short int Gamepad::thumbRY(int player) {
    return VALID_PLAYER(player) ?
    state[player].thumbRY : 0;
}
