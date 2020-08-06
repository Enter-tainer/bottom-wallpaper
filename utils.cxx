#include "utils.h"
using namespace std;

HWND _workerw = nullptr;

inline BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle)
{
  HWND defview = FindWindowExW(tophandle, 0, L"SHELLDLL_DefView", nullptr);
  if (defview != nullptr)
  {
    _workerw = FindWindowExW(0, tophandle, L"WorkerW", 0);
  }
  return true;
}

HWND Utils::GetWorkerW()
{
  uint64_t result;
  HWND windowHandle = FindWindowW(L"Progman", L"Program Manager");
  SendMessageTimeoutW(windowHandle, 0x052c, 0, 0, SMTO_NORMAL, 0x3e8, (PDWORD_PTR)&result);
  EnumWindows(EnumWindowsProc, (LPARAM) nullptr);
  ShowWindow(_workerw, SW_HIDE);
  return windowHandle;
}

HWND Utils::GetFolderView()
{
  HWND dwndparent;
  HWND dwndviem = NULL;
  HWND dwdesktopicon;
  dwndparent = FindWindowExW(0, 0, L"WorkerW", L"");
  //获得第一个WorkerW类的窗口，
  while ((!dwndviem) && dwndparent)
  //因为可能会有多个窗口类名为“WorkerW”的窗口存在，所以只能依次遍历
  {
    dwndviem = FindWindowExW(dwndparent, 0, L"SHELLDLL_DefView", 0);
    dwndparent = FindWindowExW(0, dwndparent, L"WorkerW", L"");
  }
  dwdesktopicon = FindWindowExW(dwndviem, 0, L"SysListView32", L"FolderView");
  return dwdesktopicon;
}

RECT Utils::GetExpectedSize(HWND wt_handle)
{
  HWND res = Utils::GetFolderView();
  RECT rec;
  auto err = GetWindowRect(res, &rec);
  if (err == 0)
  {
    cout << Utils::GetLastErrorAsString() << endl;
    exit(1);
  }
  MapWindowPoints(res, wt_handle, LPPOINT(&rec), 2);
  return rec;
}

void Utils::HideWindow(HWND h)
{
  ShowWindow(h, SW_HIDE);
}

std::string Utils::GetLastErrorAsString()
{
  //Get the error message, if any.
  DWORD errorMessageID = ::GetLastError();
  if (errorMessageID == 0)
    return std::string(); //No error message has been recorded

  LPSTR messageBuffer = nullptr;
  size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                               NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

  std::string message(messageBuffer, size);

  //Free the buffer.
  LocalFree(messageBuffer);

  return message;
}
