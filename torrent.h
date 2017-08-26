#ifndef CLEANING_SW_TORRENT_H
#define CLEANING_SW_TORRENT_H

#include "type.h"

namespace cleaning_sw {
    class Torrent : public Type
    {
    public:
        Torrent() {}

        Torrent* create() const override {
            return new Torrent();
        }

        Torrent* clone() const override {
            return new Torrent(*this);
        }

        virtual ~Torrent() {}

        std::string directory() const override {
            return std::string("Torrent");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_TORRENT_H
