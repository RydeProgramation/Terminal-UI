﻿#include <iostream>
#include <stdio.h>     
#include <stdlib.h>   
#include <Windows.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <fcntl.h>
#include <string>
#include <optional>
#include <conio.h> 
#include <limits>
#include <random>
#include <sstream>
#include <io.h>
#include <mutex>
#include <thread>
#include <algorithm>
#include <functional>
#include <locale>
#include <codecvt>
#include <memory>
#include <map>
#include <unordered_map>

// ───────────── LETTRES ─────────────
#define KEY_A 'A'
#define KEY_B 'B'
#define KEY_C 'C'
#define KEY_D 'D'
#define KEY_E 'E'
#define KEY_F 'F'
#define KEY_G 'G'
#define KEY_H 'H'
#define KEY_I 'I'
#define KEY_J 'J'
#define KEY_K 'K'
#define KEY_L 'L'
#define KEY_M 'M'
#define KEY_N 'N'
#define KEY_O 'O'
#define KEY_P 'P'
#define KEY_Q 'Q'
#define KEY_R 'R'
#define KEY_S 'S'
#define KEY_T 'T'
#define KEY_U 'U'
#define KEY_V 'V'
#define KEY_W 'W'
#define KEY_X 'X'
#define KEY_Y 'Y'
#define KEY_Z 'Z'

// ───────────── CHIFFRES ─────────────
#define KEY_0 '0'
#define KEY_1 '1'
#define KEY_2 '2'
#define KEY_3 '3'
#define KEY_4 '4'
#define KEY_5 '5'
#define KEY_6 '6'
#define KEY_7 '7'
#define KEY_8 '8'
#define KEY_9 '9'

// ───────────── TOUCHES SPÉCIALES ─────────────
#define KEY_ENTER        VK_RETURN
#define KEY_BACKSPACE    VK_BACK
#define KEY_TAB          VK_TAB
#define KEY_SHIFT        VK_SHIFT
#define KEY_CONTROL      VK_CONTROL
#define KEY_ALT          VK_MENU
#define KEY_CAPSLOCK     VK_CAPITAL
#define KEY_ESC          VK_ESCAPE
#define KEY_SPACE        VK_SPACE
#define KEY_DELETE       VK_DELETE
#define KEY_INSERT       VK_INSERT
#define KEY_HOME         VK_HOME
#define KEY_END          VK_END
#define KEY_PAGE_UP      VK_PRIOR
#define KEY_PAGE_DOWN    VK_NEXT
#define KEY_LEFT_ARROW   VK_LEFT
#define KEY_RIGHT_ARROW  VK_RIGHT
#define KEY_UP_ARROW     VK_UP
#define KEY_DOWN_ARROW   VK_DOWN
#define KEY_PAUSE        VK_PAUSE
#define KEY_PRINTSCREEN  VK_SNAPSHOT
#define KEY_NUMLOCK      VK_NUMLOCK
#define KEY_SCROLLLOCK   VK_SCROLL

// ───────────── CLAVIER NUMÉRIQUE (NUMPAD) ─────────────
#define KEY_NUMPAD0   VK_NUMPAD0
#define KEY_NUMPAD1   VK_NUMPAD1
#define KEY_NUMPAD2   VK_NUMPAD2
#define KEY_NUMPAD3   VK_NUMPAD3
#define KEY_NUMPAD4   VK_NUMPAD4
#define KEY_NUMPAD5   VK_NUMPAD5
#define KEY_NUMPAD6   VK_NUMPAD6
#define KEY_NUMPAD7   VK_NUMPAD7
#define KEY_NUMPAD8   VK_NUMPAD8
#define KEY_NUMPAD9   VK_NUMPAD9
#define KEY_DECIMAL   VK_DECIMAL
#define KEY_ADD       VK_ADD
#define KEY_SUBTRACT  VK_SUBTRACT
#define KEY_MULTIPLY  VK_MULTIPLY
#define KEY_DIVIDE    VK_DIVIDE

// ───────────── TOUCHES FONCTIONS (F1 → F24) ─────────────
#define KEY_F1   VK_F1
#define KEY_F2   VK_F2
#define KEY_F3   VK_F3
#define KEY_F4   VK_F4
#define KEY_F5   VK_F5
#define KEY_F6   VK_F6
#define KEY_F7   VK_F7
#define KEY_F8   VK_F8
#define KEY_F9   VK_F9
#define KEY_F10  VK_F10
#define KEY_F11  VK_F11
#define KEY_F12  VK_F12
#define KEY_F13  VK_F13
#define KEY_F14  VK_F14
#define KEY_F15  VK_F15
#define KEY_F16  VK_F16
#define KEY_F17  VK_F17
#define KEY_F18  VK_F18
#define KEY_F19  VK_F19
#define KEY_F20  VK_F20
#define KEY_F21  VK_F21
#define KEY_F22  VK_F22
#define KEY_F23  VK_F23
#define KEY_F24  VK_F24

// ───────────── TOUCHES SYMBOLES COURANTS ─────────────
// (NB : Ces touches dépendent aussi du clavier physique)
#define KEY_SEMICOLON     VK_OEM_1     // ;
#define KEY_PLUS          VK_OEM_PLUS  // =
#define KEY_COMMA         VK_OEM_COMMA // ,
#define KEY_MINUS         VK_OEM_MINUS // -
#define KEY_PERIOD        VK_OEM_PERIOD // .
#define KEY_SLASH         VK_OEM_2     // /
#define KEY_TILDE         VK_OEM_3     // `
#define KEY_LEFT_BRACKET  VK_OEM_4     // [
#define KEY_BACKSLASH     VK_OEM_5     // "\"
#define KEY_RIGHT_BRACKET VK_OEM_6     // ]
#define KEY_APOSTROPHE    VK_OEM_7     // '

