#ifndef CLEANING_SW_TYPE_H
#define CLEANING_SW_TYPE_H

#include <string>
namespace cleaning_sw {
    class Type
    {
    public:
        Type() {}

        virtual Type* create() const = 0;

        virtual Type* clone() const = 0;

        virtual ~Type() {}
        
        virtual std::string directory() const = 0;
    };
} /* cleaning_sw */

#endif //CLEANING_SW_TYPE_H
