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
#include "colordefs.h"

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
                               const time_t &  atime, const time_t &  mtime, const time_t &  ctime)
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
    }
#ifdef __MINGW32__
    else {
        smode += "-";
    }
#else
    else if (S_ISLNK(entry_mode)) {
        smode += "l";
    }
#endif

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

const time_t & directoryentry::atime() const {
    return entry_atime;
}

const time_t & directoryentry::mtime() const {
    return entry_mtime;
}

const time_t & directoryentry::ctime() const {
    return entry_ctime;
}

std::string directoryentry::time_t_to_string(time_t t) const {
    char buf[64];
    strftime(buf, 64, "%b %e %H:%M", localtime(&t));
    return string(buf);
}

const std::string directoryentry::atime_str() const {
    return time_t_to_string(entry_atime);
}

const std::string directoryentry::mtime_str() const {
    return time_t_to_string(entry_mtime);
}

const std::string directoryentry::ctime_str() const {
    return time_t_to_string(entry_ctime);
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
 * Update column width vectors with sizes from the passed entry.
 *
 * @param entry Shared pointer to directory entry to add to column_widths vector
 */
void directoryvec::update_column_widths(const shared_direntry_ptr & entry) {
    mode_width = std::max(entry->mode_str().length(),  mode_width);
    uid_width  = std::max(entry->uid_str().length(),   uid_width);
    gid_width  = std::max(entry->gid_str().length(),   gid_width);
    size_width = std::max(entry->size_str().length(),  size_width);
    time_width = std::max(entry->atime_str().length(), time_width);

    std::string name    = entry->name();
    bool space_in_name  = is_space_in_name(name);
    size_t name_length  = name.length();
    // add 2 to the name width to account for the two "'" characters printed.
    if (space_in_name) {
        name_length += 2;
    }
    if ((name != "..") && (name != ".") && (name[0] == '.')) {
        hid_fname_width = std::max(name_length, hid_fname_width);
    } else {
        reg_fname_width = std::max(name_length, reg_fname_width);
    }
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
                             const time_t & atime, const time_t & mtime, const time_t &  ctime) {
    shared_direntry_ptr entry(new directoryentry(name, mode, uid, gid, size, atime, mtime, ctime));
    if (entry) {
        count_dirs   += (!is_dot_or_dotdot(name) && S_ISDIR(mode))?1:0;
//        if (S_ISDIR(mode)) {
//            cout << "identified '" << name << "' as a directory" << endl;
//        }
        count_files  += (S_ISREG(mode))?1:0;
        count_hidden += (!is_dot_or_dotdot(name) && (name[0] == '.'))?1:0;

        directory_vec.push_back(entry);
        update_column_widths(entry);
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
 * @param compare   Function or lambda taking two shared_direntry_ptr to compare
 *                  for sorting.
 * @return          true
 */
bool directoryvec::sort(directoryvec::compare_handler compare) {

    std::sort(directory_vec.begin(), directory_vec.end(), compare);

    return true;
}

/**
 * Clear the directoryvec object to initial state.
 */

void directoryvec::clear() {
    directory_vec.clear();
    count_files = count_dirs = count_hidden = 0;
    mode_width = uid_width = gid_width = size_width = time_width = reg_fname_width = hid_fname_width = 0;
}

void directoryvec::get_count(int *files, int *dirs, int *hidden) {
    if (files) {
        *files = count_files;
    }
    if (dirs) {
        *dirs = count_dirs;
    }
    if (hidden) {
        *hidden = count_hidden;
    }
}

void directoryvec::set_line_length(size_t value) {
    line_length = value;
}

void directoryvec::set_show_hidden(bool value) {
    show_hidden = value;
}

void directoryvec::set_long_format(bool value) {
    long_format = value;
}
/**
 * Output directory list to ostream
 *
 * @param out       ostream to display output on.
 * @param dirvec    directory vector to display
 * @return          ostream
 */
std::ostream &operator<<(std::ostream &out,  directoryvec &dirvec) {
    size_t name_size;
    string name;

    if (dirvec.show_hidden) {
        name_size = std::max(dirvec.reg_fname_width, dirvec.hid_fname_width);
    } else {
        name_size = dirvec.reg_fname_width;
    }

    if (dirvec.long_format) {
        dirvec.foreach_direntry([&](const shared_direntry_ptr &a, void *ptr) -> bool {
            if (dirvec.show_hidden || (a->name()[0] != '.')) {
                if (dirvec.enable_color) {
                    if (S_ISDIR(a->mode())) {
                        name = color::blue(a->name(), true);
                        //ns += 9;
                    } else {
                        name = a->name();
                    }
                } else {
                    name = a->name();
                }
                if (directoryvec::is_space_in_name(name)) {
                    name = "'" + name + "'";
                }

                out << a->mode_str() << " " <<
                    std::setw(dirvec.uid_width) << a->uid() << " " <<
                    std::setw(dirvec.gid_width) << a->gid() << " " <<
                    std::setw(dirvec.size_width) << a->size() << " " <<
                    std::setw(dirvec.time_width) << a->mtime_str() << " " <<
                    name << endl;
            }
            return true;
        });
    } else {

        int column_count = (int)(dirvec.line_length / name_size);
        int cur_col = 0;

        dirvec.foreach_direntry([&](const shared_direntry_ptr &a, void *ptr) -> bool {
            if (dirvec.show_hidden || (a->name()[0] != '.')) {
                int ns = name_size;

                if (dirvec.enable_color) {
                    if (S_ISDIR(a->mode())) {
                        name = color::blue(a->name(), true);
                        ns += 9;
                    } else {
                        name = a->name();
                    }
                } else {
                    name = a->name();
                }
                if (directoryvec::is_space_in_name(name)) {
                    name = "'" + name + "'";
                }

                out << std::left << std::setw(ns) << name << " ";
                cur_col++;
            }
            if (cur_col == column_count) {
                out << endl;
                cur_col = 0;
            }
            return true;
        });
        if (cur_col != 0) {
            out << endl;
        }
    }
    return out;
}

bool directoryvec::is_dot_or_dotdot(const std::string &name) {
    return ((name == ".") || (name == ".."));
}

bool directoryvec::is_space_in_name(const std::string &name) {
    return (name.find_first_of(' ') != std::string::npos);
}
