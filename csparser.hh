#ifndef H_GUARD_CSPARSER_H
#define H_GUARD_CSPARSER_H

#include <iostream>
#include <string>
#include <vector>

struct DefMsg {
    std::string             fileName;
    int                     line;
    int                     column;
    std::string             msg;
};

struct Defect {
    std::string             defClass;
    std::vector<DefMsg>     msgs;
};

std::ostream& operator<<(std::ostream &str, const Defect &def);

class Parser {
    public:
        Parser(std::istream &input, std::string fileName);
        ~Parser();
        bool getNext(Defect *);
        bool hasError() const;

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_CSPARSER_H */
