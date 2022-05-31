#include "film.hh"



bool film::operator > (const int k) const{
    if(this->value() > k)
        return true;
    else return false;
}


bool film::operator < (const int k) const{
    if(this->value() < k)
        return true;
    else return false;
}


bool film::operator <= (const int k) const{
    if(this->value() <= k)
        return true;
    else return false;
}

bool film::operator <= (const film& f1) const{
        if(this->value() <= f1.value())
            return true;
        else return false;
    }

ostream& operator << (ostream& wyj, film& f1){
        wyj.precision(2);
        wyj << fixed;
       
        wyj.flush();
        wyj << setw(7) << f1.value() << "   " << f1.name() << endl;
      
        return wyj;
    }

