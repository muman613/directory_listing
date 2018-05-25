#include <iostream>
#include <fstream>
#include <strings.h>
#include <cstring>
#include "directorylist.h"
#include "directory_enumerator.h"

using namespace std;


void show_help(const std::string& cmd) {
    cout << cmd << " [-h] [-l] [-R] <path>" << endl;
}

/**
 * Parse commandline arguments here.
 *
 * @param argc
 * @param argv
 * @param path
 * @param ls_format
 * @return  true if arguments parsed without trouble, otherwise false
 */
static bool parse_args(int argc, char* argv[], std::string & path, unsigned int & ls_format) {
    if (argc >= 2) {
        int i;

        ls_format = 0; // init format

        for (i = 1 ; i < argc ; i++) {
            if (strcmp(argv[i], "-h") == 0) {
                ls_format |= sync_ls_flag_all_no_dot;
            } else if (strcmp(argv[i], "-l") == 0) {
                ls_format |= sync_ls_flag_long;
            } else if (strcmp(argv[i], "-R") == 0) {
                ls_format |= sync_ls_flag_recursive;
            } else if (strcmp(argv[i], "-S") == 0) {
                ls_format |= sync_ls_flag_sort_size;
            } else if (strcmp(argv[i], "-t") == 0) {
                ls_format |= sync_ls_flag_sort_date;
            } else if (strcmp(argv[i], "-A") == 0) {
                ls_format |= sync_ls_flag_all_no_dot;
            } else if (strcmp(argv[i], "-a") == 0) {
                ls_format |= sync_ls_flag_all;
            } else {
                path = argv[i];
            }
        }
        // path MUST be specified
        if (path.empty()) {
            show_help(argv[0]);
            return false;
        }
    } else {
        show_help(argv[0]);
        return false;
    }

    return true;
}

/**
 *
 * @return
 */
int main(int argc, char* argv[]) {
    std::string scan_path; // = argv[1];
    unsigned int ls_format = 0;

    if (parse_args(argc, argv, scan_path, ls_format)) {
        cout << "Scanning directory " << scan_path << endl;

        directoryvec        dirvec;

        dirvec.set_flags(ls_format);
        enumerate_directory(scan_path, dirvec);
//        dirvec.sort([](shared_direntry_ptr a, shared_direntry_ptr b) {
//            return (strcasecmp(a->name().c_str(), b->name().c_str()) < 0);
//        });
        dirvec.sort();
        dirvec.set_line_length(132);

        cout << dirvec  ;

        int file_cnt   = 0,
            dir_cnt    = 0,
            hidden_cnt = 0;

        dirvec.get_count(&file_cnt, &dir_cnt, &hidden_cnt);
        cout << "count: files = " << file_cnt << " dirs = " << dir_cnt << " hidden = " << hidden_cnt << endl;

        fstream  os("listing.txt", ofstream::out);
        os << dirvec;
        os.close();
    }

    return 0;
}

#if 0
bool simple_callback(const shared_direntry_ptr & entry, void* ptr) {
    cout << "name " << entry->name() << " mode " << entry->mode() << endl;
    return true;
}

void test_directory_vec() {
    directoryvec dirvec;

    cout << "Hello, World!" << std::endl;

    timestruc_t t;

    dirvec.add_entry("Abracadabra", S_IFREG, 1000, 1000, 4096, t, t, t);
    dirvec.add_entry("File #1", S_IFREG, 1000, 1000, 2048, t, t, t);
    dirvec.add_entry("File #2", S_IFREG, 1000, 1000, 4096, t, t, t);
    dirvec.add_entry("Xasperation", S_IFREG, 1000, 1000, 4096, t, t, t);

    dirvec.foreach_direntry([](const shared_direntry_ptr & a, void* ptr) {
        cout << "name " << a->name() << " ptr " << ptr << endl;
        cout << *a << endl;
        return true;
    }, (void *)0xdeadbeef);

    dirvec.sort([](shared_direntry_ptr a, shared_direntry_ptr b) {
        return (b->name() < a->name());
    });

    dirvec.foreach_direntry(simple_callback, nullptr);

    dirvec.clear();
}
#endif