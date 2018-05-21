//
// Created by muman on 5/19/2018.
//

#ifndef DIRLIST_DIRECTORY_ENUMERATOR_H
#define DIRLIST_DIRECTORY_ENUMERATOR_H

/**
 * Iterate through all files & directories in the specified path collecting
 * the directoryentry's in the vector.
 *
 * @param path
 * @param dirvec
 * @return
 */
bool enumerate_directory(const std::string& path, directoryvec & dirvec);

#endif //DIRLIST_DIRECTORY_ENUMERATOR_H
