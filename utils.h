#ifndef UTILS_H
#define UTILS_H
#include <Windows.h>
#include <string>
#include <iostream>
#include <cinttypes>

namespace Utils
{

  HWND GetWorkerW();
  HWND GetFolderView();
  RECT GetExpectedSize(HWND wt_handle);
  void HideWindow(HWND h);
  std::string GetLastErrorAsString();
}
#endif // UTILS_H
