#ifndef CLEANING_SW_DOC_H
#define CLEANING_SW_DOC_H

#include "type.h"

namespace cleaning_sw {
    class Doc : public Type
    {
    public:
        Doc() {}

        virtual ~Doc() {}

        Doc* create() const override {
            return new Doc();
        }

        Doc* clone() const override {
            return new Doc(*this);
        }

        std::string directory() const override {
            return std::string("Doc");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_DOC_H
