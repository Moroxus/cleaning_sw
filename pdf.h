#ifndef CLEANING_SW_PDF_H
#define CLEANING_SW_PDF_H

#include "type.h"

namespace cleaning_sw {
    class Pdf : public Type
    {
    public:
        Pdf() {}

        Pdf* create() const override {
            return new Pdf();
        }

        Pdf* clone() const override {
            return new Pdf(*this);
        }

        virtual ~Pdf() {}

        std::string directory() const override {
            return std::string("PDF");
        }
    };
} /* cleaning_sw */

#endif //CLEANING_SW_PDF_H
