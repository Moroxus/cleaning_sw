#include <iostream>
#include <queue>
#include "environment.h"
#include "file.h"

using namespace cleaning_sw;
using namespace boost::filesystem;
using namespace std;

int main(int argc, char* argv[])
{
    std::string root;
    if (argc > 1) {
        root = argv[1];
    } else {
        root = "/home/" + Environment::getUserName() + "/Downloads";
    }

    if ( !exists( root ) ) {
        cout << "Directory " << root << " does not exists\n";
        exit( 1 );
    } else if ( !is_directory( root ) ) {
        cout << root << " is not a directory\n";
        exit( 1 );
    }

    queue<File> files;
    for (directory_iterator item = directory_iterator(path(root)); item != directory_iterator(); ++item) {
        if (is_regular_file(item->path())) {
            files.push(File(item->path()));
        }
    }

    while (!files.empty()) {
        files.front().move(root);
        files.pop();
    }

    return 0;
}
