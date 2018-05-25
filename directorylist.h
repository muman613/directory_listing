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

#ifdef __MINGW32__
typedef short           uid_t;
typedef short           gid_t;
typedef unsigned short  mode_t;
typedef unsigned int    uint;

// these definitions are required for some MinGW compilers
#ifndef S_IRGRP
#define S_IRGRP     0040
#define S_IWGRP     0020
#define S_IXGRP     0010
#define S_IROTH     0004
#define S_IWOTH     0002
#define S_IXOTH     0001
#endif
#endif

// flags used to do_sync_ls
const unsigned int sync_ls_flag_long        = 0x001; // ls -l
const unsigned int sync_ls_flag_dir         = 0x002; // ls -d
const unsigned int sync_ls_flag_sort_size   = 0x004; // ls -S
const unsigned int sync_ls_flag_sort_date   = 0x008; // ls -t
const unsigned int sync_ls_flag_all         = 0x010; // ls -a
const unsigned int sync_ls_flag_all_no_dot  = 0x020; // ls -A
const unsigned int sync_ls_flag_recursive   = 0x040; // ls -R
const unsigned int sync_ls_flag_dir_slash   = 0x080; // ls -m (corresponds to -p on Linux, but -p is already used)
const unsigned int sync_ls_flag_color       = 0x100; // ls -C ??
class directoryvec;

class directoryentry {
public:
    directoryentry(const std::string & name, mode_t mode,
                   uid_t uid, gid_t gid, off_t size, const time_t & atime,
                   const time_t & mtime, const time_t & ctime);
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
    const time_t &      atime() const;
    const std::string   atime_str() const;
    const time_t &      mtime() const;
    const std::string   mtime_str() const;
    const time_t &      ctime() const;
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
    time_t          entry_atime; // Last access time
    time_t          entry_mtime; // Last modification time
    time_t          entry_ctime; // Last status change time
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
                              uid_t uid, gid_t gid, off_t size, const time_t & atime,
                              const time_t & mtime, const time_t  & ctime);

    using entry_handler = std::function<bool(const shared_direntry_ptr &, void*)>;
    using compare_handler = std::function<bool(shared_direntry_ptr, shared_direntry_ptr)>;

    bool            foreach_direntry(entry_handler callback, void* ptr = nullptr);
    bool            sort(compare_handler compare);
    bool            sort();

    void            set_line_length(size_t value);
    void            set_flags(unsigned int value);

    static bool     is_dot_or_dotdot(const std::string & name);
    static bool     is_space_in_name(const std::string & name);

protected:
    friend std::ostream & operator << (std::ostream & out, directoryvec & entry);

    void            update_column_widths(const shared_direntry_ptr & entry);

    direntry_vec    directory_vec;
    uint            count_files     = 0;
    uint            count_dirs      = 0;
    uint            count_hidden    = 0;
    unsigned int    flags           = 0;
    size_t          line_length     = 80; // default to 80 column width

    // 'ls' field widths
    size_t          mode_width      = 0;
    size_t          uid_width       = 0;
    size_t          gid_width       = 0;
    size_t          size_width      = 0;
    size_t          time_width      = 0;
    size_t          reg_fname_width = 0;
    size_t          hid_fname_width = 0;
};

#endif //DIRLIST_DIRECTORYLIST_H
