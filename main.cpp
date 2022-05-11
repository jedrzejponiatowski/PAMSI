#include <iostream>
#include "package.hh"
#include "ddlist.hh"
#include <chrono>
#include <sys/time.h>
#include <ctime>
using namespace std;
using namespace chrono;


bool check_if_exist(int* array, int value, int how_many);


int main(){
    ddlist DDL;
    
    
    cout << "\tEnter the number of packages: ";
    int number_of_packs;
    cin >> number_of_packs;

   
    /*create an array of IDs*/
    int* used_rand = new int[number_of_packs];
    for(int i=0; i<number_of_packs;i++)
        used_rand[i]=-1;
    
    /* randomization */
    for(int i=0; i<number_of_packs; i++){
        int rand_id = ( rand() % number_of_packs);
        while(check_if_exist(used_rand, rand_id, number_of_packs)){
            rand_id = ( rand() % number_of_packs);
        }
        used_rand[i]=rand_id;
    }
    
    cout << "\n\tOrder of arrival: " << endl;
    for(int i=0; i<number_of_packs;i++)
    cout << used_rand[i] << " ";

//**********************************************

    auto ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    for(int i=0; i<number_of_packs; i++){
        package* tmp = new package(used_rand[i]);
        DDL.add_and_sort(tmp);
    }

    auto ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

//**********************************************



    cout << endl;
    cout << "\n\n\tMessage ready to open. ";
    cout << endl <<  "\tsize: " << DDL.size_of_list() << endl;
    cout << "\tOrder of packages: " << endl;

    DDL.show_list();

    cout << endl;
    cout << "\tOperation time:  " << (ms2-ms1) << " ms."<< endl;
    cout << endl;
    
    return 0;
}




bool check_if_exist(int *arr, int value, int how_many){
    for(int i=0;i<how_many;i++){
        if(arr[i] == value)
        return true;
    }
    return false;
}