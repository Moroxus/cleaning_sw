#ifndef CLEANING_SW_IMAGE_H
#define CLEANING_SW_IMAGE_H

#include "type.h"

namespace cleaning_sw {
    class Image : public Type
    {
    public:
        Image() {}

        Image* create() const override {
            return new Image();
        }

        Image* clone() const override {
            return new Image(*this);
        }

        virtual ~Image() {}

        std::string directory() const override {
            return std::string("Image");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_IMAGE_H
