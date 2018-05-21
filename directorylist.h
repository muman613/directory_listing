//
// Created by muman on 5/19/2018.
//

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
#include <time.h>
#include <stdint.h>


class directoryentry {
public:
    directoryentry(const std::string & name, mode_t mode,
                   uid_t uid, gid_t gid, off_t size, const timestruc_t & atime,
                   const timestruc_t & mtime, const timestruc_t & ctime);
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
    const timestruc_t & atime() const;
    const timestruc_t & mtime() const;
    const timestruc_t & ctime() const;
    const std::string   atime_str() const;
    const std::string   mtime_str() const;
    const std::string   ctime_str() const;

protected:
    friend std::ostream & operator << (std::ostream & out, const directoryentry & entry);
    
    std::string     time_t_to_string(time_t t) const;

    std::string     entry_name;
    mode_t          entry_mode; // One of
    uid_t           entry_uid;
    gid_t           entry_gid;
    off_t           entry_size;
    timestruc_t     entry_atime; // Last access time
    timestruc_t     entry_mtime; // Last modification time
    timestruc_t     entry_ctime; // Last status change time
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
    void            get_count(int* files, int* dirs = nullptr);

    bool            add_entry(const std::string & name, mode_t mode,
                              uid_t uid, gid_t gid, off_t size, const timestruc_t & atime,
                              const timestruc_t & mtime, const timestruc_t & ctime);

    using entry_handler = std::function<bool(const shared_direntry_ptr &, void*)>;
    using compare_handler = std::function<bool(shared_direntry_ptr, shared_direntry_ptr)>;

    bool            foreach_direntry(entry_handler callback, void* ptr = nullptr);
    bool            sort(compare_handler compare);

    bool            calculate_column_widths();

protected:
    direntry_vec    directory_vec;
    uint            count_files = 0;
    uint            count_dirs  = 0;
    size_t_vec      column_widths = { 0, 0, 0, 0, 0, 0, 0 };
};

#endif //DIRLIST_DIRECTORYLIST_H
