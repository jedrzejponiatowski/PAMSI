#include <fstream>
#include <iomanip>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include "film.hh"
#include "sorts.hh"

#define MAX_FILMS 405365

using namespace std;
using namespace std::chrono;

long filtering_data(fstream& f1, fstream& f2);
void reading_data(fstream& file, film array[], int how_many);
int do_sort(film sorted[],const film original[], const int which_sort, const int how_many_films);

double average;
int median;

int main(){

    int how_many_films;
    long number_of_films;
    int64_t ms1, ms2;

    fstream file("projekt2_dane.csv", ios::in);
    fstream output_tmp("projekt2_dane_tmp.txt", ios::out);
    fstream input_tmp("projekt2_dane_tmp.txt", ios::in);  
    fstream output1("Results_merge.txt", ios::out);
    fstream output2("Results_quick.txt", ios::out);
    fstream output3("Results_bucket.txt", ios::out);

    if(file.is_open()){
        ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        number_of_films = filtering_data(file, output_tmp);
        ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        output_tmp.close();
    }
    else {
        cerr << "Can't open a file!" << endl;
        return 0;
    }

    cout << "\tFiltering the films..." << endl << 
        "\n\tBefore:   " << MAX_FILMS <<
        "\n\tNow:      " << number_of_films << 
        "\n\tRejected: " << MAX_FILMS-number_of_films <<
        "\n\tOperation time: " << ms2-ms1 << "ms." << endl << endl;
    

    cout << "\tHow many films do you want to sort? > ";
    cin >> how_many_films;
    while(how_many_films > number_of_films || how_many_films <1){
        cout << "\tOut of range. Please type number between 1 - " << number_of_films << "  > ";
        cin >> how_many_films;
    }
    cout << endl << endl;


    film* collection_original= new film[how_many_films];
    film* collection_sorted =new film[how_many_films];

    reading_data(input_tmp, collection_original, how_many_films);
    
    for(int i=0; i<3; i++){
        ms1=do_sort(collection_sorted, collection_original, i, how_many_films);
        switch(i){
            case 0:
                cout << "\tMerge Sort:  " << ms1 << "ms." << endl << endl;
                for(int i=0; i<how_many_films; i++)
                    output1 << collection_sorted[i];
                break;
            case 1:
                cout << "\tQuick Sort:  " << ms1 << "ms." << endl << endl;
                for(int i=0; i<how_many_films; i++)
                    output2 << collection_sorted[i];
                break;
            case 2:
                cout << "\tBucket Sort:  " << ms1 << "ms." << endl << endl;
                for(int i=0; i<how_many_films; i++)
                    output3 << collection_sorted[i];
                break;
        }
    }


    for(int i=0; i<how_many_films; i++){
        average+=collection_sorted[i].value();
    }
    average=average/how_many_films;
    median=collection_sorted[how_many_films/2].value();

    cout << endl << "\tAverage:   " << setprecision(3) <<  average << endl;
    cout <<         "\tMedian:    " << median << endl;

    system("rm -rf projekt2_dane_tmp.txt");

    cout << "Do you want to remove result files? <y/n>  : ";
    char answer;
    cin >> answer;
    if(answer=='y'){
        system("rm -rf Results_merge.txt");
        system("rm -rf Results_quick.txt");
        system("rm -rf Results_bucket.txt");
    }

    return 0;
}
 
/****************************************************************************/


long filtering_data(fstream& f1, fstream& f2){
    string line;
    string linetmp;
    string rate;
    double digit;
    size_t left_coma;
    size_t right_coma;
    int counter=0;

    getline(f1,linetmp);
    
    for(int i=0;i<MAX_FILMS ;i++){
        if(f1.is_open() && f2.is_open()){
            getline(f1,linetmp);
            left_coma=linetmp.find_first_of(",");
            right_coma=linetmp.find_last_of(",");
            line=linetmp.substr(left_coma+1,right_coma-left_coma-1);
        
            if(!isdigit(linetmp[right_coma+1])) {
                counter++;
                continue;
            }
            rate=linetmp.substr(right_coma+1);
            digit=stod(rate);
            f2 << line << "|" << digit << endl; 
        }
    }

    return MAX_FILMS-counter;
}


void reading_data(fstream& file, film array[], int how_many){
    string line;
    string linetmp;
    string rate;
    double digit;
    size_t left_coma;
    size_t right_coma;
   
    
    for(int i=0;i<how_many && file.is_open();i++){
        getline(file,linetmp);
        auto coma=linetmp.find_first_of("|");
        line=linetmp.substr(0,coma);
        rate=linetmp.substr(coma+1);
        digit=stod(rate);
        
        array[i]=film(line,digit); 
    }
}


int do_sort(film sorted[], const film original[], const int which_sort, const int how_many_films){

    for(int i=0;i<how_many_films;i++)
        sorted[i]=original[i];

    int64_t ms1,ms2;
    

    switch(which_sort){
        case 0:
            ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            mergeSort(sorted,0,how_many_films-1);
            ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            sorted[0]=film("---Merge Sort---", -99);
            return ms2-ms1;
            break;
        case 1:
            ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            quickSort(sorted,0,how_many_films-1);
            ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
             sorted[0]=film("---Quick Sort---", -99);
            return ms2-ms1;
            break;
        case 2:
            ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            bucketSort(sorted,how_many_films);
            ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            sorted[0]=film("---Bucket Sort---", -99);
            return ms2-ms1;
            break;
        default: cerr << "Wrong number of sort. Please type 0-2." << endl;
            return 0;
    }
}

