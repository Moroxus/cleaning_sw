#ifndef CLEANING_SW_OTHER_H
#define CLEANING_SW_OTHER_H

#include "type.h"

namespace cleaning_sw {
    class Other : public Type
    {
    public:
        Other() {}

        Other* create() const override {
            return new Other();
        }

        Other* clone() const override {
            return new Other(*this);
        }

        virtual ~Other() {}

        std::string directory() const override {
            return std::string("Other");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_OTHER_H
