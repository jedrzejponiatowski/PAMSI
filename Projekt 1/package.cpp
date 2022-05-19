#include "package.hh"



void package::set_next(package* pack){
    this->next=pack;
}


package* package::get_next() const{
    return next;
}


void package::set_previous(package* pack){
    this->prev=pack;
}


package* package::get_previous() const{
    return prev;
}
