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

/*
  struct stat {
    _dev_t st_dev;
    _ino_t st_ino;
    unsigned short st_mode;
    short st_nlink;
    short st_uid;
    short st_gid;
    _dev_t st_rdev;
    _off_t st_size;
    time_t st_atime;
    time_t st_mtime;
    time_t st_ctime;
  };
*/

#ifdef __MINGW32__
typedef short           uid_t;
typedef short           gid_t;
typedef unsigned short  mode_t;
typedef unsigned int    uint;
#endif

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

    void            set_line_length(size_t value);
    void            set_show_hidden(bool value);
    void            set_long_format(bool value);

    static bool     is_dot_or_dotdot(const std::string & name);
    static bool     is_space_in_name(const std::string & name);

protected:
    friend std::ostream & operator << (std::ostream & out, directoryvec & entry);

    void            update_column_widths(const shared_direntry_ptr & entry);

    direntry_vec    directory_vec;
    uint            count_files     = 0;
    uint            count_dirs      = 0;
    uint            count_hidden    = 0;
    bool            show_hidden     = false;
    bool            long_format     = false;
    bool            enable_color    = true;
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
