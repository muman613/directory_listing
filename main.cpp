#include <iostream>
#include "directorylist.h"
#include "directory_enumerator.h"

using namespace std;

std::string get_mode_string(mode_t mode) {
    std::string smode;

    if (S_ISREG(mode)) {
        smode += "-";
    } else if (S_ISDIR(mode)) {
        smode += "d";
    } else if (S_ISLNK(mode)) {
        smode += "l";
    }

    smode += (mode & S_IRUSR)?"r":"-";
    smode += (mode & S_IWUSR)?"w":"-";
    smode += (mode & S_IXUSR)?"x":"-";
    smode += (mode & S_IRGRP)?"r":"-";
    smode += (mode & S_IWGRP)?"w":"-";
    smode += (mode & S_IXGRP)?"x":"-";
    smode += (mode & S_IROTH)?"r":"-";
    smode += (mode & S_IWOTH)?"w":"-";
    smode += (mode & S_IXOTH)?"x":"-";

    return smode;
}
bool simple_callback(const shared_direntry_ptr & entry, void* ptr) {
    cout << "name " << entry->name() << " mode " << entry->mode() << endl;
    return true;
}
/**
 *
 * @return
 */
int main() {
    directoryvec        dirvec;

    cout << "Hello, World!" << std::endl;

    timestruc_t t;

    dirvec.add_entry("Abracadabra", S_IFREG, 1000, 1000, 4096, t, t, t);
    dirvec.add_entry("File #1", S_IFREG, 1000, 1000, 2048, t, t, t);
    dirvec.add_entry("File #2", S_IFREG, 1000, 1000, 4096, t, t, t);
    dirvec.add_entry("Xasperation", S_IFREG, 1000, 1000, 4096, t, t, t);

    dirvec.foreach_direntry([](const shared_direntry_ptr & a, void* ptr) {
        cout << "name " << a->name() << " ptr " << ptr << endl;
        return true;
    }, (void *)0xdeadbeef);

    dirvec.sort([](shared_direntry_ptr a, shared_direntry_ptr b) {
        return (b->name() < a->name());
    });

    dirvec.foreach_direntry(simple_callback, nullptr);

    dirvec.clear();

    cout << "Scanning directory C:\\Users\\muman\\" << endl;

    enumerate_directory("C:\\Users\\muman\\", dirvec);
    dirvec.foreach_direntry([](const shared_direntry_ptr & a, void* ptr) {
        mode_t mode = a->mode();
#if 0
        string file_type;
        switch (mode & S_IFMT) {
            case S_IFREG:
                file_type = "regular file";
                break;
            case S_IFDIR:
                file_type = "directory";
                break;
            default:
                file_type = "unknown";
                break;
        }
#endif

        cout << get_mode_string(mode) << " " << a->name() << " ptr " << ptr << endl;

        return true;
    }, (void *)0xdeadbeef);

    int file_cnt, dir_cnt;
    dirvec.get_count(&file_cnt, &dir_cnt);
    cout << "count: files = " << file_cnt << " dirs = " << dir_cnt << endl;
    return 0;
}