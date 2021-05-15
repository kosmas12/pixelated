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
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>

void initFiles() {
    files = (char **) calloc(50, sizeof(char));
}

int listDir() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./")) != NULL) {
        int i = 0;
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            files[i] = ent->d_name;
            ++i;
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return 0;
    }
}
