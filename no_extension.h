#ifndef CLEANING_SW_NO_EXTENSION_H
#define CLEANING_SW_NO_EXTENSION_H

#include "type.h"

namespace cleaning_sw {
    class NoExtension : public Type
    {
    public:
        NoExtension() {}

        NoExtension* create() const override {
            return new NoExtension();
        }

        NoExtension* clone() const override {
            return new NoExtension(*this);
        }

        virtual ~NoExtension() {}

        std::string directory() const override {
            return std::string("No Extension");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_NO_EXTENSION_H
