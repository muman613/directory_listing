//
// Created by muman on 5/19/2018.
//

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>
#include <memory>
#include <algorithm>
#include "directorylist.h"

using namespace std;

/**
 *
 * @param name
 * @param type
 * @param mode
 * @param uid
 * @param gid
 * @param size
 * @param atime
 * @param mtime
 * @param ctime
 */
directoryentry::directoryentry(const std::string & name, mode_t mode, uid_t uid, gid_t gid, off_t size,
                               const timestruc_t &  atime, const timestruc_t &  mtime, const timestruc_t &  ctime)
{
    entry_name      = name;
    entry_mode      = mode;
    entry_uid       = uid;
    entry_gid       = gid;
    entry_size      = size;
    entry_atime     = atime;
    entry_mtime     = mtime;
    entry_ctime     = ctime;
}

directoryentry::~directoryentry() {
    // dtor
#ifdef _DEBUG
    cout << "destroying entry for file '" << entry_name << "'..." << endl;
#endif
}

const std::string &directoryentry::name() const {
    return entry_name;
}

mode_t directoryentry::mode() const {
    return entry_mode;
}

/**
 * Directory vector.
 */
directoryvec::directoryvec() {
    // ctor
}

directoryvec::~directoryvec() {
#ifdef _DEBUG
    cout << "at time of destruction directoryvec contains " << size() << " items" << endl;
#endif
}

size_t directoryvec::size() const {
    return directory_vec.size();
}

/**
 * Add an entry to the directory.
 *
 * @param name      File name
 * @param mode      stat's mode value
 * @param uid       Files owner
 * @param gid       Files group
 * @param size      File size
 * @param atime     Last access time
 * @param mtime     Last modify time
 * @param ctime     Last change time
 * @return          true
 */
bool directoryvec::add_entry(const std::string & name, mode_t mode, uid_t uid, gid_t gid, off_t size,
                             const timestruc_t & atime, const timestruc_t & mtime, const timestruc_t &  ctime) {
    shared_direntry_ptr entry(new directoryentry(name, mode, uid, gid, size, atime, mtime, ctime));
    if (entry) {
        count_dirs += (S_ISDIR(mode))?1:0;
        count_files += (S_ISREG(mode))?1:0;

        directory_vec.push_back(entry);
        return true;
    }

    return false;
}

bool directoryvec::foreach_direntry(directoryvec::entry_handler callback, void* ptr) {
    for (auto const & entry : directory_vec) {
        callback(entry, ptr);
    }
    return true;
}

bool directoryvec::sort(directoryvec::compare_handler compare) {

    std::sort(directory_vec.begin(), directory_vec.end(), compare);

    return false;
}

void directoryvec::clear() {
    directory_vec.clear();
    count_files = count_dirs = 0;
}

void directoryvec::get_count(int *files, int *dirs) {
    if (files) {
        *files = count_files;
    }
    if (dirs) {
        *dirs = count_dirs;
    }
}