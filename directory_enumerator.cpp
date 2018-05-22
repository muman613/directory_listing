//
// Created by muman on 5/19/2018.
//
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "directorylist.h"
#include "directory_enumerator.h"

using namespace std;

/**
 * Enumerate files in a directory using opendir()/readdir() and populate the directory vector.
 *
 * @param path
 * @param dirvec
 * @return
 */
bool enumerate_directory(const std::string& path, directoryvec & dirvec) {
    bool result = false;
    DIR * _dir  = nullptr;
    dirent* _entry = nullptr;

    _dir = opendir(path.c_str());
    if (_dir) {
        while ((_entry = readdir(_dir)) != nullptr) {
            std::string entry_name = _entry->d_name;
            std::string fullpath   = path + "/" + entry_name;

            struct stat st = {};
            if (stat(fullpath.c_str(), &st) == 0) {
                dirvec.add_entry(entry_name, st.st_mode, st.st_uid, st.st_gid,
                                 st.st_size, st.st_atim, st.st_mtim, st.st_ctim);
            }
        }
        closedir(_dir);
        result = true;
    }

    return result;
}