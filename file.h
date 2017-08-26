#ifndef CLEANING_SW_FILE_H
#define CLEANING_SW_FILE_H

#include "type.h"
#include <boost/filesystem.hpp>
#include <utility>
#include "types.h"

using namespace std;
using namespace boost::filesystem;

namespace cleaning_sw {
    class File
    {
    public:
        Type *type;
        path filePath;

        boost::filesystem::path createName(std::string &root) {
            boost::filesystem::path destination = root;
            destination += "/";
            destination += type->directory();
            destination += "/";
            destination += filePath.filename();
            while(exists(destination)) {
                destination = renameFile(destination);
            }
            return destination;
        }

        std::string extension() {
            std::string extension = filePath.extension().string();
            extension.erase(0,1);
            transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
            return extension;
        }

        boost::filesystem::path renameFile(boost::filesystem::path &fullpath ) {
            using boost::filesystem::path;
            path filename = fullpath.stem();
            path newPath = fullpath.parent_path();
            newPath += "/";
            newPath += filename;
            newPath += "_1";
            newPath += extension();
            return newPath;
        }

        void swap(File& other) {
            using std::swap;
            swap(type, other.type);

        }

        bool moveFile(boost::filesystem::path &destination) {
            try {
                rename( filePath, destination);
            } catch (...) {
                return false;
            }
            return exists( destination );
        }

        static string extension( path &item )
        {
            string extension = item.extension().string();
            extension.erase(0,1);
            transform( extension.begin(), extension.end(), extension.begin(), ::tolower );
            return extension;
        }

        static bool isMusic( path &item )
        {
            string ext = extension( item );
            return ( ext == "flac" || ext == "mp3" );
        }

        static bool isVideo( path &item )
        {
            string ext = extension( item );
            return ( ext == "mkv" || ext == "avi" || ext == "mp4" || ext == "ts" );
        }

        static bool isTorrent( path &item )
        {
            string ext = extension( item );
            return ( ext == "torrent" );
        }

        static bool isTxt( path &item )
        {
            string ext = extension( item );
            return ( ext == "txt" );
        }

        static bool isDoc( path &item )
        {
            string ext = extension( item );
            return ( ext == "doc" || ext == "docx") ;
        }

        static bool isPackage( path &item )
        {
            string ext = extension( item );
            return ( ext == "rar" || ext == "zip" || ext == "iso" || ext == "jar" || ext == "gz" || ext == "deb");
        }

        static bool isNoExtension( path &item )
        {
            return !item.has_extension();
        }

        static bool isPdf( path &item )
        {
            string ext = extension( item );
            return ( ext == "pdf" );
        }

        static bool isImage( path &item )
        {
            string ext = extension( item );
            return ( ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "gif" || ext == "tiff" );
        }

        static Type* identifyType(boost::filesystem::path& item) {
            if (isMusic(item))
               return new Music();
            if (isVideo(item))
               return new Video();
            if (isTorrent(item))
               return new Torrent();
            if (isTxt(item))
               return new Txt();
            if (isDoc(item))
               return new Doc();
            if (isPackage(item))
               return new Package();
            if (isNoExtension(item))
               return new NoExtension();
            if (isPdf(item))
               return new Pdf();
            if (isImage(item))
               return new Image();

            return new Other();
        }


    public:
        File(boost::filesystem::path filePath):type(identifyType(filePath)),
                                               filePath(filePath){}

        ~File() { delete type; }

        File(const File& other){
            type = other.type->clone();
            filePath = other.filePath;
        }

        File(File&& other) {
            type = other.type;
            filePath = other.filePath;
            other.type = nullptr;
        }

        File& operator=(File other) {
            swap(other);
            return *this;
        }

        void move(std::string root) {
            path p(root + string("/") + type->directory());
            if ( !exists( p ) ) {
                if ( !create_directories( p ) ) {
                    cout << "Directory " << p << " was not created successfully\n";
                    exit(1);
                }
            }
            boost::filesystem::path destination = createName(root);
            if (moveFile(destination)) {
                std::cout << filePath << std::endl << "moved to " << std::endl << destination << std::endl << std::endl;
            } else {
                std::cout << "error moving file " << filePath << std::endl;
            }
        }
    };
} /* cleaning_sw */


#endif //CLEANING_SW_FILE_H
