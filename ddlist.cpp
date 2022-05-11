#include "ddlist.hh"
#include <iostream>
using namespace std;

bool ddlist::is_empty() const{
    if(head==nullptr)
        return true;
    return false;
}


void ddlist::add_front(package* n){
    if(is_empty()){
        head=n;
        tail=n;
        n->set_previous(nullptr);
        n->set_next(nullptr);
        size++;
    } else {
        n->set_next(head);
        head->set_previous(n);
        head=n;
        n->set_previous(nullptr);
        size++;
    }
}

void ddlist::add_end(package* n){
    if(is_empty()){
        head=n;
        tail=n;
        n->set_previous(nullptr);
        n->set_next(nullptr);
        size++;
    } else {
        n->set_previous(tail);
        tail->set_next(n);
        tail=n;
        n->set_next(nullptr);
        size++;
    }

}

void ddlist::show_list() const{
    package*tmp = head;
    while(tmp){
        cout << tmp->get_id() << " ";
        tmp=tmp->get_next();
    }

}

void ddlist::add_after(package* goal, package* purp){
    purp->set_previous(goal);
    purp->set_next(goal->get_next());
    if(goal->get_next()!=nullptr)
        (goal->get_next())->set_previous(purp);
    else tail=purp;
    goal->set_next(purp);
    size++;
}



package* ddlist::find_good_place(package* purp) const{
    package* tmp=head;
    while( (tmp->get_id()) < purp->get_id()){
        if(tmp->get_next()==nullptr){
            return tmp;
        }
        tmp=tmp->get_next();
    }
    if(tmp==head){
        return nullptr;
    }

    return tmp->get_previous();
}



void ddlist::add_and_sort(package* pack){
    if(is_empty())
        add_front(pack);
    else {
        package* tmp = find_good_place(pack);
        if(tmp!=nullptr)
            add_after(tmp, pack);
        else add_front(pack);
    }
}