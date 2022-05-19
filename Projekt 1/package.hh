#ifndef PACKAGE_HH
#define PACKAGE_HH


/*!
*   \brief Shapes the concept of received packages from Internet
*
*   Created to be used in bidirectional list
*/

class package{
private:
    package* prev;      // pointer to previous pack
    package* next;      // pointer to next pack
    int id;             // unique id of pack. Set in order.

public:

/*!
*   \brief Two constructors. Default value - 0
*/
    package(): id(0) {}
    package(int num){id=num;}

/*!
*   Functions to menage private data. 
*   GETTERS / SETTERS
*/
    void set_next(package* pack);
    package* get_next() const;

    void set_previous(package* pack);
    package* get_previous() const;

    void set_id(int num) {id=num;}
    int get_id() const {return id;}
};





#endif