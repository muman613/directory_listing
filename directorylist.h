/**
 * @file    directorylist.h
 * @author  Michael A. Uman
 * @date    May 20, 2018
 */

#ifndef DIRLIST_DIRECTORYLIST_H
#define DIRLIST_DIRECTORYLIST_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <dirent.h>
#include <ctime>
#include <cstdint>

class directoryvec;

class directoryentry {
public:
    directoryentry(const std::string & name, mode_t mode,
                   uid_t uid, gid_t gid, off_t size, const timespec & atime,
                   const timespec & mtime, const timespec & ctime);
    virtual ~directoryentry();

    const std::string&  name() const;
    mode_t              mode() const;
    std::string         mode_str() const;
    uid_t               uid() const;
    std::string         uid_str() const;
    gid_t               gid() const;
    std::string         gid_str() const;
    off_t               size() const;
    std::string         size_str() const;
    const timespec &    atime() const;
    const std::string   atime_str() const;
    const timespec &    mtime() const;
    const std::string   mtime_str() const;
    const timespec &    ctime() const;
    const std::string   ctime_str() const;

protected:
    friend class directoryvec;

    friend std::ostream & operator << (std::ostream & out, const directoryentry & entry);
    
    std::string     time_t_to_string(time_t t) const;

    std::string     entry_name;
    mode_t          entry_mode; // One of
    uid_t           entry_uid;
    gid_t           entry_gid;
    off_t           entry_size;
    timespec        entry_atime; // Last access time
    timespec        entry_mtime; // Last modification time
    timespec        entry_ctime; // Last status change time
};

using shared_direntry_ptr = std::shared_ptr<directoryentry>;
using direntry_vec = std::vector<shared_direntry_ptr>;
using size_t_vec = std::vector<size_t>;

class directoryvec {
public:
    directoryvec();
    virtual ~directoryvec();

    size_t          size() const;
    void            clear();
    void            get_count(int* files, int* dirs = nullptr, int * hidden = nullptr);

    bool            add_entry(const std::string & name, mode_t mode,
                              uid_t uid, gid_t gid, off_t size, const timespec & atime,
                              const timespec & mtime, const timespec & ctime);

    using entry_handler = std::function<bool(const shared_direntry_ptr &, void*)>;
    using compare_handler = std::function<bool(shared_direntry_ptr, shared_direntry_ptr)>;

    bool            foreach_direntry(entry_handler callback, void* ptr = nullptr);
    bool            sort(compare_handler compare);

    void            set_line_length(size_t value);
    void            set_show_hidden(bool value);
    void            set_long_format(bool value);

protected:
    friend std::ostream & operator << (std::ostream & out, directoryvec & entry);

    void            update_column_widths(const shared_direntry_ptr & entry);

    direntry_vec    directory_vec;
    uint            count_files     = 0;
    uint            count_dirs      = 0;
    uint            count_hidden    = 0;
    //size_t_vec      column_widths   = { 0, 0, 0, 0, 0, 0, 0 };
    bool            show_hidden     = false;
    bool            long_format     = false;
    size_t          mode_width      = 0;
    size_t          uid_width       = 0;
    size_t          gid_width       = 0;
    size_t          size_width      = 0;
    size_t          time_width      = 0;
    size_t          reg_fname_width = 0;
    size_t          hid_fname_width = 0;
    size_t          line_length     = 80;
};

#endif //DIRLIST_DIRECTORYLIST_H
