/*
This file is part of Pixelated - a cross platform image viewer
Copyright (C) 2021 Kosmas Raptis

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "files.h"
#if defined(NXDK)
#include <hal/debug.h>
#endif
#include <windows.h>
#include <malloc.h>

void initFiles() {
    files = (char **) calloc(50, sizeof(char));
}

int listDir() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    hFind = FindFirstFile("D:\\*", &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        debugPrint("FindFirstHandle() failed!\n");
        Sleep(5000);
        return 0;
    }

    int i = 0;

    do {
        files[i] = findFileData.cFileName;
        ++i;
    } while (FindNextFile(hFind, &findFileData) != 0);

    return 1;

}

