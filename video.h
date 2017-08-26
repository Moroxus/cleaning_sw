#ifndef CLEANING_SW_VIDEO_H
#define CLEANING_SW_VIDEO_H

#include "type.h"

namespace cleaning_sw {
    class Video : public Type
    {
    public:
        Video() {}

        Video* create() const override {
            return new Video();
        }

        Video* clone() const override {
            return new Video(*this);
        }

        virtual ~Video() {}

        std::string directory() const override {
            return std::string("Video");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_VIDEO_H
