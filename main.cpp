#include <iostream>
#include <strings.h>
#include "directorylist.h"
#include "directory_enumerator.h"

using namespace std;

bool simple_callback(const shared_direntry_ptr & entry, void* ptr) {
    cout << "name " << entry->name() << " mode " << entry->mode() << endl;
    return true;
}
/**
 *
 * @return
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Must specify path to list" << endl;
        return 10;
    }

    std::string scan_path = argv[1];

    cout << "Scanning directory " << scan_path << endl;

    directoryvec        dirvec;
    enumerate_directory(scan_path, dirvec);
    dirvec.sort([](shared_direntry_ptr a, shared_direntry_ptr b) {
        return (strcasecmp(a->name().c_str(), b->name().c_str()) == -1);
    });

    dirvec.calculate_column_widths();

    //dirvec.set_show_hidden(true);
    cout << dirvec  ;

    int file_cnt, dir_cnt;
    dirvec.get_count(&file_cnt, &dir_cnt);
    cout << "count: files = " << file_cnt << " dirs = " << dir_cnt << endl;


    return 0;
}

#if 0
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