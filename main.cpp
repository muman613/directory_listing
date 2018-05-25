#include <iostream>
#include <fstream>
#include <strings.h>
#include <cstring>
#include "directorylist.h"
#include "directory_enumerator.h"

using namespace std;



static bool parse_args(int argc, char* argv[], std::string & path, bool & show_hidden, bool & long_format) {
    if (argc >= 2) {
        int i;

        for (i = 1 ; i < argc ; i++) {
            if (strcmp(argv[i], "-h") == 0) {
                show_hidden = true;
            } else if (strcmp(argv[i], "-l") == 0) {
                long_format = true;
            } else {
                path = argv[i];
            }
        }
        if (path.empty()) {
            cout << argv[0] << " [-h] <path>" << endl;
            return false;
        }
    } else {
        cout << argv[0] << " [-h] <path>" << endl;
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
    bool show_hidden = false,
         long_format = false;

    if (parse_args(argc, argv, scan_path, show_hidden, long_format)) {
        cout << "Scanning directory " << scan_path << endl;

        directoryvec        dirvec;
        enumerate_directory(scan_path, dirvec);
        dirvec.sort([](shared_direntry_ptr a, shared_direntry_ptr b) {
            return (strcasecmp(a->name().c_str(), b->name().c_str()) < 0);
        });

        dirvec.set_line_length(132);
        dirvec.set_show_hidden(show_hidden);
        dirvec.set_long_format(long_format);
        dirvec.set_flags(sync_ls_flag_all);

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