#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

BOOL canAccessFile(const wchar_t* path) {
    return _waccess(path, 0) == 0 ? TRUE : FALSE;
}

__declspec(dllexport) void RemoveUtf8Bom(const wchar_t* filePath) {
    char bom[4] = { '\xEF', '\xBB', '\xBF', '\0' };
    char buffer[4] = { 0 };
    wchar_t newName[MAX_PATH];

    char c;

    FILE* fileIn;
    FILE* fileOut;

    if (canAccessFile(filePath) == FALSE)
        return;

    wcscpy(newName, filePath);
    wcscat(newName, L"_tmp");

    DeleteFileW(newName);
    _wrename(filePath, newName);

    fileIn = _wfopen(newName, L"r");
    fread(buffer, sizeof(char), 3, fileIn);

    if (strcmp(buffer, bom) == 0) {
        fseek(fileIn, 3, SEEK_SET);

        fileOut = _wfopen(filePath, L"w");

        c = fgetc(fileIn);

        while (c != EOF) {
            fputc(c, fileOut);
            c = fgetc(fileIn);
        }

        fclose(fileIn);
        fclose(fileOut);
        _wremove(newName);
    } else {
        fclose(fileIn);
        _wrename(newName, filePath);
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
		DisableThreadLibraryCalls(hinstDLL);
	
    return TRUE;
}
