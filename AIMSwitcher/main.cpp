#include <iostream>
#include <string>

#include <Windows.h>

#pragma comment(lib, "imm32.lib")

#define IMC_GETCONVERSIONMODE 0x01
#define IMC_SETCONVERSIONMODE 0x02

int GetCurrentInputMethod() {
    HWND hWnd = GetForegroundWindow();
    DWORD threadId = GetWindowThreadProcessId(hWnd, nullptr);
    HKL hKL = GetKeyboardLayout(threadId);
    uintptr_t langId = reinterpret_cast<uintptr_t>(hKL) & 0xFFFF;
    return static_cast<int>(langId);
}

void SwitchInputMethod(int langId) {
    HWND hWnd = GetForegroundWindow();
    PostMessage(hWnd, WM_INPUTLANGCHANGEREQUEST, 0, static_cast<LPARAM>(langId));
}

int GetCurrentInputMethodMode() {
    HWND hWnd = GetForegroundWindow();
    HWND hIMEWnd = ImmGetDefaultIMEWnd(hWnd);
    LRESULT mode = SendMessage(hIMEWnd, WM_IME_CONTROL, IMC_GETCONVERSIONMODE, 0);
    return static_cast<int>(mode);
}

void SwitchInputMethodMode(int mode) {
    HWND hWnd = GetForegroundWindow();
    HWND hIMEWnd = ImmGetDefaultIMEWnd(hWnd);
    SendMessage(hIMEWnd, WM_IME_CONTROL, IMC_SETCONVERSIONMODE, static_cast<LPARAM>(mode));
}

void ShowUsage() {
    std::cout
        << "AIMSwitcher, An Input Method Switcher\n"
        << "Usage: AIMSwitcher [OPTION]... [ARG]...\n"
        << "\n"
        << "  --im [INPUTMETHOD]      show the current input method if INPUTMETHOD is omitted,\n"
        << "                          otherwise switch to the specified input method\n"
        << "  --imm [INPUTMETHODMODE] show the current input method mode if INPUTMETHODMODE is omitted,\n"
        << "                          otherwise switch to the specified input method mode\n"
        << std::endl;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        ShowUsage();
    }
    else if (strcmp(argv[1], "--im") == 0) {
        if (argc == 2)
            std::cout << GetCurrentInputMethod() << std::endl;
        else
            SwitchInputMethod(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "--imm") == 0) {
        if (argc == 2)
            std::cout << GetCurrentInputMethodMode() << std::endl;
        else
            SwitchInputMethodMode(atoi(argv[2]));
    }
    else {
        ShowUsage();
    }
    return 0;
}
