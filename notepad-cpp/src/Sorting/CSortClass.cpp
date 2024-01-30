#include "CSortClass.h"


CSortClass::CSortClass(std::vector<std::shared_ptr<CSorting>> & sorts) : sorts_vector(sorts){
}



bool CSortClass::operator()(const std::shared_ptr<CNote> &first, const std::shared_ptr<CNote> &second,size_t index) const{
    if(index == this->sorts_vector.size()) return true;

    if(sorts_vector[index]->isSame(first,second)) return operator()(first,second,index + 1);
    else return sorts_vector[index]->sortNotes(first,second);


}