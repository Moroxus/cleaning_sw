#ifndef CLEANING_SW_PACKAGE_H
#define CLEANING_SW_PACKAGE_H

#include "type.h"

namespace cleaning_sw {
    class Package : public Type
    {
    public:
        Package() {}

        Package* create() const override {
            return new Package();
        }

        Package* clone() const override {
            return new Package(*this);
        }

        virtual ~Package() {}

        std::string directory() const override {
            return std::string("Package");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_PACKAGE_H
