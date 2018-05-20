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

protected:
    friend class directoryvec;

    std::string     entry_name;
    mode_t          entry_mode; // One of
    uid_t           entry_uid;
    gid_t           entry_gid;
    off_t           entry_size;
    timestruc_t     entry_atime; // Last access time
    timestruc_t     entry_mtime; // Last modification time
    timestruc_t     entry_ctime; // Last status change time
};

using shared_direntry = std::shared_ptr<directoryentry>;
using direntry_vec = std::vector<shared_direntry>;

class directoryvec {
public:
    directoryvec();
    virtual ~directoryvec();

    size_t          size() const;
    void            clear();

    bool            add_entry(const std::string & name, mode_t mode,
                              uid_t uid, gid_t gid, off_t size, const timestruc_t & atime,
                              const timestruc_t & mtime, const timestruc_t & ctime);

    using entry_handler = std::function<bool(const shared_direntry &, void*)>;
    using compare_handler = std::function<bool(shared_direntry, shared_direntry)>;

    bool            foreach_direntry(entry_handler callback, void* ptr = nullptr);
    bool            sort(compare_handler compare);

protected:
    direntry_vec    directory_vec;
};

bool enumerate_directory(const std::string& path, direntry_vec & dirvec);

#endif //DIRLIST_DIRECTORYLIST_H
