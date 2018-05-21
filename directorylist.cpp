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
#include <sstream>
#include <iomanip>
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

gid_t  directoryentry::gid() const {
    return entry_gid;
}

uid_t  directoryentry::uid() const {
    return entry_uid;
}

off_t  directoryentry::size() const {
    return entry_size;
}

/**
 * Return a string representation of the mode in 'ls' style.
 *
 * @return  std::string
 */
 
string directoryentry::mode_str() const {
    string smode;

    if (S_ISREG(entry_mode)) {
        smode += "-";
    } else if (S_ISDIR(entry_mode)) {
        smode += "d";
    } else if (S_ISLNK(entry_mode)) {
        smode += "l";
    }

    smode += (entry_mode & S_IRUSR)?"r":"-";
    smode += (entry_mode & S_IWUSR)?"w":"-";
    smode += (entry_mode & S_IXUSR)?"x":"-";
    smode += (entry_mode & S_IRGRP)?"r":"-";
    smode += (entry_mode & S_IWGRP)?"w":"-";
    smode += (entry_mode & S_IXGRP)?"x":"-";
    smode += (entry_mode & S_IROTH)?"r":"-";
    smode += (entry_mode & S_IWOTH)?"w":"-";
    smode += (entry_mode & S_IXOTH)?"x":"-";

    return smode;
}


ostream & operator << (ostream & out, const directoryentry & entry) {
    out << entry.mode_str() << " " << entry.entry_uid << " " <<
        entry.entry_gid << " " << std::setw(12) << entry.entry_size << " " <<
        entry.mtime_str() << " " << entry.entry_name;
    return out;
}

std::string directoryentry::uid_str() const {
    std::ostringstream uid_str;
    uid_str << entry_uid;
    return uid_str.str();
}

std::string directoryentry::gid_str() const {
    std::ostringstream gid_str;
    gid_str << entry_gid;
    return gid_str.str();
}

std::string directoryentry::size_str() const {
    std::ostringstream size_str;
    size_str << entry_size;
    return size_str.str();
}

const timestruc_t &directoryentry::atime() const {
    return entry_atime;
}

const timestruc_t &directoryentry::mtime() const {
    return entry_mtime;
}

const timestruc_t &directoryentry::ctime() const {
    return entry_ctime;
}

std::string directoryentry::time_t_to_string(time_t t) const {
    char buf[64];
    strftime(buf, 64, "%b %e %H:%M", localtime(&t));
    return string(buf);
}

const std::string directoryentry::atime_str() const {
    return time_t_to_string(entry_atime.tv_sec);
}

const std::string directoryentry::mtime_str() const {
    return time_t_to_string(entry_mtime.tv_sec);
}

const std::string directoryentry::ctime_str() const {
    return time_t_to_string(entry_ctime.tv_sec);
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
 *
 * @todo    Adjust column widths on the fly as the entries are being added.
 *
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

/**
 * Call function (or lambda) passing each directory entry in the vector.
 *
 * @param callback
 * @param ptr
 * @return
 */
bool directoryvec::foreach_direntry(directoryvec::entry_handler callback, void* ptr) {
    for (auto const & entry : directory_vec) {
        callback(entry, ptr);
    }
    return true;
}

/**
 * Sort directory using callback or lambda function.
 *
 * @param compare
 * @return
 */
bool directoryvec::sort(directoryvec::compare_handler compare) {

    std::sort(directory_vec.begin(), directory_vec.end(), compare);

    return false;
}

/**
 * Clear the directoryvec object to initial state.
 */

void directoryvec::clear() {
    directory_vec.clear();
    count_files = count_dirs = 0;
    column_widths = { 0, 0, 0, 0, 0, 0, 0 };
}

void directoryvec::get_count(int *files, int *dirs) {
    if (files) {
        *files = count_files;
    }
    if (dirs) {
        *dirs = count_dirs;
    }
}

/**
 * Calculate the widths of each field in the output.
 *
 * @return true
 */

bool directoryvec::calculate_column_widths() {
    column_widths = { 0, 0, 0, 0, 0, 0, 0 };

    foreach_direntry([=](const shared_direntry_ptr & entry, void * ptr) {
        column_widths[0] = std::max(entry->mode_str().length(), column_widths[0]);
        column_widths[1] = std::max(entry->uid_str().length(), column_widths[1]);
        column_widths[2] = std::max(entry->gid_str().length(), column_widths[2]);
        column_widths[3] = std::max(entry->size_str().length(), column_widths[3]);
        column_widths[4] = std::max(entry->atime_str().length(), column_widths[4]);
        column_widths[5] = std::max(entry->name().length(), column_widths[5]);

        return false;
    }, nullptr);

    for (const auto col : column_widths) {
        cout << col << " ";
    }
    cout << endl;

    return true;
}

void directoryvec::set_show_hidden(bool value) {
    show_hidden = value;
}

std::ostream &operator<<(std::ostream &out,  directoryvec &dirvec) {
    dirvec.foreach_direntry([&](const shared_direntry_ptr & a, void* ptr) {
        if (dirvec.show_hidden || (a->name()[0] != '.')) {
            out << a->mode_str() << " " << a->uid() << " " <<
                a->gid() << " " << std::setw(dirvec.column_widths[3]) << a->size() << " " <<
                a->mtime_str() << " " << a->name() << endl;
            //out << *a << endl;
        }
        return true;
    }, nullptr);

    return out;
}
