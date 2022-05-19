#ifndef FILM_HH
#define FILM_HH

using namespace std;
#include <string>
#include <iostream>
#include <iomanip>


/*!
*   \brief Create a class of film. Has a title and rate of the film.
*/

class film{
private:
    string _name;
    double _rate;
public:

/*
*   Constructors.
*/
    film(string nazwa, double ocena) : _name(nazwa), _rate(ocena) {}
    film() : _name(""), _rate(0) {}

/*
*   Getters. Return rate or title.
*/
    double value() const {return _rate;}
    string name() const {return _name;}

/*
*   True/false relations. Compare a rate of the film.
*/
    bool operator <= (const film& f1) const;
    bool operator <= (const int k) const;
    bool operator > (const int k) const;
    bool operator < (const int k) const;
};

ostream& operator << (ostream& wyj, film& f1);




#endif