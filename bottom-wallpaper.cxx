#define WINVER 0x0601
#include <cstdio>
#include <iostream>
#include <string>
#include "comdef.h"
#include "windows.h"
#include "utils.h"
#include <functional>
#include <cstdlib>

using namespace std;

void startBottom()
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));
  char cmd[] = "wt.exe -p Bottom";
  auto res = CreateProcess(NULL,  // No module name (use command line)
                           cmd,   // Command line
                           NULL,  // Process handle not inheritable
                           NULL,  // Thread handle not inheritable
                           FALSE, // Set handle inheritance to FALSE
                           0,     // No creation flags
                           NULL,  // Use parent's environment block
                           NULL,  // Use parent's starting directory
                           &si,   // Pointer to STARTUPINFO structure
                           &pi);
  if (!res)
  {
    cout << Utils::GetLastErrorAsString() << endl;
    exit(1);
  }
  Sleep(1000);
}

struct WtWindow
{
  HWND main_handle;
  HWND content_handle;
  WtWindow()
  {
    main_handle = FindWindowW(L"CASCADIA_HOSTING_WINDOW_CLASS", L"Bottom");
    content_handle = FindWindowExW(main_handle, nullptr, L"Windows.UI.Composition.DesktopWindowContentBridge", nullptr);
  }
};


int main()
{
  // FreeConsole();
  startBottom();
  WtWindow w;
  RECT sz = Utils::GetExpectedSize(w.content_handle);
  Utils::HideWindow(w.main_handle);
  SetParent(w.content_handle, Utils::GetProgman());
  SetWindowPos(w.content_handle, HWND_BOTTOM, 0, -36, sz.right - sz.left, sz.bottom - sz.top, SWP_SHOWWINDOW);
}
