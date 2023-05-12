#include <iostream>
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

//https://stackoverflow.com/questions/57425730/how-to-use-c-to-control-the-display-and-shutdown-of-the-tabtip-keyboard

BOOL GetPidByProcessName(TCHAR *pProcess, DWORD *dwPid)
{
    HANDLE hSnapshot;
    PROCESSENTRY32 lppe;
    hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (hSnapshot == NULL)
        return FALSE;
    lppe.dwSize = sizeof(lppe);
    if (!::Process32First(hSnapshot, &lppe))
        return FALSE;
    do
    {
        if (_tcscmp(lppe.szExeFile, pProcess) == 0)
        {
            *dwPid = lppe.th32ProcessID;
        }
    } while (::Process32Next(hSnapshot, &lppe));

    return TRUE;
}

BOOL KillProcess(DWORD ProcessId)
{
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
    if (hProcess == NULL)
        return FALSE;
    if (!TerminateProcess(hProcess, 0))
        return FALSE;
    return TRUE;
}

int main()
{
    cout << "Hello world!" << endl;
    HWND TabTip = FindWindow("IPTip_Main_Window", 0);
    if (!TabTip)
    {
        ShellExecute(NULL, "open", "C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe", NULL, NULL, SW_SHOW);
    }
    else
    {
        TCHAR a[256] = _T("TabTip.exe");
        DWORD b = 0;
        GetPidByProcessName(a, &b);
        KillProcess(b);
        ShellExecute(NULL, "open", "C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe", NULL, NULL, SW_SHOW);
    }

    return 0;
}
