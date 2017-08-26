#ifndef CLEANING_SW_TXT_H
#define CLEANING_SW_TXT_H

#include "type.h"

namespace cleaning_sw {
    class Txt : public Type
    {
    public:
        Txt() {}

        Txt* create() const override {
            return new Txt();
        }

        Txt* clone() const override {
            return new Txt(*this);
        }

        virtual ~Txt() {}

        std::string directory() const override {
            return std::string("TXT");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_TXT_H
