#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <boost/filesystem.hpp>
#include "Environment.h"


/**********************************************************************
 * To add directory to structure, you need to add
 * next element to dir enum, string in function directoryStructure
 * and function to detect files supposed to be in this directory
 **********************************************************************/

using namespace std;
using namespace boost::filesystem;
enum dir { MUSIC, VIDEO, TORRENT, TXT, DOC, PACKAGE, OTHER, NO_EXTENSION, PDF, IMAGE };

/**
 * @brief directoryStructure contains list of directories to be created
 * @return vector of directories
 */
vector<string> directoryStructure();

vector<path> createDirectories( vector<string>& directories, string root );

void clean( string root, vector<path>& paths );

void moveFile( directory_iterator &item, vector<path> &paths);

bool move(const path &source, path &destination );

path renameFile( path &fullpath );

bool isMusic( directory_iterator &item );

bool isVideo( directory_iterator &item );

bool isTorrent( directory_iterator &item );

bool isTxt( directory_iterator &item );

bool isDoc( directory_iterator &item );

bool isPackage( directory_iterator &item );

bool isNoExtension( directory_iterator &item );

bool isPdf( directory_iterator &item );

bool isImage( directory_iterator &item );

path createName( path& folder, directory_iterator &item );

string extension( directory_iterator &item );

int main(int argc, char *argv[])
{
    vector<string> directories = directoryStructure();
    string root;

    if ( argc > 1 ) {
        root = argv[1];
    } else {
        root = "/home/" + Environment::getUserName() + "/Downloads";
    }

    vector<path> paths = createDirectories( directories, root );

    clean( root, paths );

    return 0;
}

vector<string> directoryStructure()
{
    vector<string> directories = { "Music",
                                   "Videos",
                                   "Torrents",
                                   "TXT",
                                   "Docs",
                                   "Packages",
                                   "Others",
                                   "No Extension",
                                   "PDF",
                                   "Images"};
    return directories;
}

vector<path> createDirectories( vector<string>& directories , string root )
{
    if ( !exists( root ) ) {
        cout << "Directory " << root << " does not exists\n";
        exit( 1 );
    } else if ( !is_directory( root ) ) {
        cout << root << " is not a directory\n";
        exit( 1 );
    }
    vector<path> paths;
    for ( auto directory = directories.begin(); directory != directories.end(); ++directory )
    {
        path p( root + string("/") + *directory );
        if ( !exists( p ) ) {
            if ( !create_directories( p ) ) {
                cout << "Directory " << p << " was not created successfully\n";
                exit(1);
            }
        }

        paths.push_back( p );
    }
    return paths;
}

void clean( string root, vector<path> &paths )
{
    path rootDir( root );

    if ( !exists( rootDir ) ) {
        cout << "Directory " << root << " does not exists\n";
        exit( 1 );
    } else if ( !is_directory( rootDir ) ) {
        cout << rootDir << " is not a directory\n";
        exit( 1 );
    }

    for( directory_iterator item = directory_iterator( rootDir ); item != directory_iterator(); ++item )
    {
        if ( is_regular_file( item->path() ) ) {
            cout << "moving file " << item->path() << endl;
            moveFile( item, paths );
        }
    }
}

void moveFile( directory_iterator &item, vector<path> &paths )
{
    path destination;

    if ( isMusic( item ) ) {
        destination = createName( paths[ MUSIC ], item);
    } else if ( isVideo( item ) ) {
        destination = createName( paths[ VIDEO ], item );
    } else if ( isTorrent( item ) ) {
        destination = createName( paths[ TORRENT ], item);
    } else if ( isTxt( item ) ) {
        destination = createName( paths[ TXT ], item);
    } else if ( isDoc( item ) ) {
        destination = createName( paths[ DOC ], item);
    } else if ( isPackage( item ) ) {
        destination = createName( paths[ PACKAGE ], item);
    } else if ( isNoExtension( item ) ) {
        destination = createName( paths[ NO_EXTENSION ], item);
    } else if ( isPdf( item ) ) {
        destination = createName( paths[ PDF ], item);
    } else if ( isImage( item ) ){
        destination = createName( paths[ IMAGE ], item);
    } else {
        destination = createName( paths[ OTHER ], item);
    }

    if ( move( item->path(), destination ) ) {
        cout << "file moved to " << destination << endl;
    } else {
        cout << "error moving file " << item->path() << endl;
    }
}

bool move( const path &source, path &destination )
{
    try {
        rename( source, destination );
    }
    catch (...)
    {
        return false;
    }

    return exists( destination );
}

path renameFile(path &fullpath )
{
    path filename = fullpath.stem();
    path newPath = fullpath.parent_path();
    newPath += "/";
    newPath += filename;
    newPath += "_1";
    return newPath;
}


bool isMusic( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "flac" || ext == "mp3" );
}

bool isVideo( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "mkv" || ext == "avi" || ext == "mp4" || ext == "ts" );
}

bool isTorrent( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "torrent" );
}

bool isTxt( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "txt" );
}

bool isDoc( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "doc" || ext == "docx") ;
}

bool isPackage( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "rar" || ext == "zip" || ext == "iso" || ext == "jar" || ext == "gz" || ext == "deb");
}

bool isNoExtension( directory_iterator &item )
{
    return !item->path().has_extension();
}

bool isPdf( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "pdf" );
}

bool isImage( directory_iterator &item )
{
    string ext = extension( item );
    return ( ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "gif" || ext == "tiff" );
}

path createName( path& folder, directory_iterator &item )
{
    path destination = folder;
    destination += '/';
    destination += item->path().filename();
    while( exists( destination ) ) {
        destination = renameFile( destination );
    }
    return destination;
}

string extension( directory_iterator &item )
{
    string extension = item->path().extension().string();
    extension.erase(0,1);
    transform( extension.begin(), extension.end(), extension.begin(), ::tolower );
    return extension;
}
