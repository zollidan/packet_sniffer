#include <windows.h>
#include <stdio.h>
#include <tchar.h>

ULONGLONG convertToMb(const ULONGLONG size) {
    return size / 1048576;
}

void ListFolders(const TCHAR* directoryPath, int depth) {
    WIN32_FIND_DATA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    TCHAR szDir[MAX_PATH];
    TCHAR newPath[MAX_PATH];

    _stprintf_s(szDir, MAX_PATH, TEXT("%s\\*"), directoryPath);
    hFind = FindFirstFile(szDir, &ffd);

    if (INVALID_HANDLE_VALUE == hFind) {
        return;
    }

    do {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (_tcscmp(ffd.cFileName, TEXT(".")) != 0 &&
                _tcscmp(ffd.cFileName, TEXT("..")) != 0) {

                for (int i = 0; i < depth; i++) {
                    _tprintf(TEXT("  "));
                }
                _tprintf(TEXT("> %s\\\n"), ffd.cFileName);

                _stprintf_s(newPath, MAX_PATH, TEXT("%s\\%s"), directoryPath, ffd.cFileName);

                ListFolders(newPath, depth + 1);
                }
        }
    } while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);
}

int main() {
    ListFolders(TEXT("F:\\torrents"), 0);
    return 0;
}