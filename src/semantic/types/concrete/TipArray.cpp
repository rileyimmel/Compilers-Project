#include "TipArray.h"
#include "TipTypeVisitor.h"

#include <sstream>

TipArray::TipArray(std::shared_ptr<TipType> type):
    TipCons(std::vector<std::shared_ptr<TipType>>(1, type)) {}

//might be wrong
std::ostream &TipArray::print(std::ostream &out) const {
    out << "[";
    for (auto &init : arguments) {
        out << *init;
        if(init != arguments.back()){
            out << ",";
        }
    }
    out << "]";
    return out;
}

// This does not obey the semantics of alpha init values
bool TipArray::operator==(const TipType &other) const {
    auto otherArray = dynamic_cast<const TipArray *>(&other);
    if(!otherArray){
        return false;
    }

    if(*(arguments.at(0)) != *(otherArray->arguments.at(0))){
        return false;
    }
    return true;
}

bool TipArray::operator!=(const TipType &other) const {
    return !(*this == other);
}

std::vector<std::shared_ptr<TipType>> TipArray::getElems() const {
    std::vector<std::shared_ptr<TipType>> elems(arguments.begin(), arguments.end());
    return elems;
}

void TipArray::accept(TipTypeVisitor *visitor) {
    if (visitor->visit(this)) {
        for (auto a : arguments) {
            a->accept(visitor);
        }
    }
    visitor->endVisit(this);
}
