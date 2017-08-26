#ifndef CLEANING_SW_MUSIC_H
#define CLEANING_SW_MUSIC_H

#include "type.h"

namespace cleaning_sw {
    class Music : public Type
    {
    public:
        Music() {}

        Music* create() const override {
            return new Music();
        }

        Music* clone() const override {
            return new Music(*this);
        }

        virtual ~Music() {}

        std::string directory() const override {
            return std::string("Music");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_MUSIC_H
