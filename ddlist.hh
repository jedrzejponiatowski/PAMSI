#ifndef DDLIST_HH
#define DDLIST_HH

#include "package.hh"

/*!
*   \brief Create a Double-Direction List (bidirectional list)
*          Container - ADT
*/


class ddlist{
private:
    package* head;          // pointer to head/front of list
    package* tail;          // pointer to tail/end of list
    long size;              // number of elements on list

public:
/*!
*   Constructor. Create an empty list.
*/
    ddlist() : head(nullptr), tail(nullptr), size(0) {}

/*!
*   \brief Check if list is empty
*   \return True if empty. False if there's something
*/
    bool is_empty() const;

/*!
*   \brief Adds package to appropriate order.
*   Sorted in way: from the smallest to the largest
*   \param pack - package to add
*/
    void add_and_sort(package* pack);

/*!
*   \brief Adds a package on the front of the list
*   \param pack - package to add
*/
    void add_front(package* pack);

/*!
*   \brief Adds a package on the end/tail of the list
*   \param pack - package to add
*/
    void add_end(package* pack);

/*!
*   \brief Adds a pack in order after indicated pack  
*   \param goal - value after which we insert the package
*   \param purp - purpose/target do insert
*/
    void add_after(package* goal, package* purp);

/*!
*   \brief Show the list from head to tail
*/
    void show_list() const;

/*!
*   \brief Function connected to add_after(). Finds a place to insert next pack
*   \param purp - value/target to insert
*   \return a pointer to preceding pack 
*/
    package* find_good_place(package* purp) const;

/*!
*   \brief Check number of packs on the list
*   \return size of list
*/
    long size_of_list() const {return size;}
    
};






#endif