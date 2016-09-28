#include <iostream>
#include <vector>
#include <cmath>

int size;
int size_m1;
int half;
int solutions;
int n = 0;
int n_m1 = -1;

unsigned int filled;
unsigned int lsb;
unsigned int t;
unsigned int first = (1 << 0);
unsigned int last;
unsigned int endMarker;


bool solveEven(){
    unsigned int steps[size];
    unsigned int tmpLeft[size];
    unsigned int tmpRight[size];
    unsigned int tmpRow[size];

    tmpRow[0] = filled;
    tmpLeft[0] = filled;
    tmpRight[0] = filled;
    t = filled;
    for(;;){
        lsb = filled & ~(t & -t);
        if(n == 0 && lsb == endMarker)
            return true;
        if(t != 0){
            steps[n] = t;
            n ++;
            n_m1 ++; //Variable to speed up processing

            tmpRow[n] = tmpRow[n_m1] & lsb;
            tmpLeft[n] = (tmpLeft[n_m1] & lsb) << 1 | first;
            tmpRight[n] = (tmpRight[n_m1] & lsb) >> 1 | last;

            t = tmpRow[n] & tmpLeft[n] & tmpRight[n];
        }else{
            //We did not find a new position

            //We are at the first queen
            //This means that we have completed the search, return

            //We count down, this is basically the same as backtracking.
            n --;
            n_m1 --; //Variable to speed up processing

            t = steps[n];
            //Simply toggle the bit it was currently on as off
            //so that we start the search on the next row
            lsb = filled & ~(t & -t);
            t &= lsb;
        }

        if(n == size){
            solutions ++;
            solutions ++;

            t &= lsb;
            n --;
            n_m1 --;
        }
    }
}

bool solveOdd(){
    unsigned int steps[size];
    unsigned int tmpLeft[size];
    unsigned int tmpRight[size];
    unsigned int tmpRow[size];

    tmpRow[0] = filled;
    tmpLeft[0] = filled;
    tmpRight[0] = filled;
    t = filled;
    for(;;){
        lsb = filled & ~(t & -t);
        if(n == 0 && lsb == endMarker)
            return true;
        if(t != 0){
            steps[n] = t;
            n ++;
            n_m1 ++; //Variable to speed up processing

            tmpRow[n] = tmpRow[n_m1] & lsb;
            tmpLeft[n] = (tmpLeft[n_m1] & lsb) << 1 | first;
            tmpRight[n] = (tmpRight[n_m1] & lsb) >> 1 | last;

            t = tmpRow[n] & tmpLeft[n] & tmpRight[n];
        }else{
            //We did not find a new position

            //We are at the first queen
            //This means that we have completed the search, return

            //We count down, this is basically the same as backtracking.
            n --;
            n_m1 --; //Variable to speed up processing

            t = steps[n];
            //Simply toggle the bit it was currently on as off
            //so that we start the search on the next row
            lsb = filled & ~(t & -t);
            t &= lsb;
        }

        if(n == size){
            solutions ++;
            solutions ++;

            t &= lsb;
            n --;
            n_m1 --;
        }
    }
}

int main(int argc, char* argv[]){
    sscanf(argv[1], "%d", &size);
    size_m1 = size - 1;
    half = size / 2;
    filled = (1 << size) - 1;
    last = (1 << size_m1);
    endMarker = filled & ~(1 << (half));

    if(size % 2 == 0)
        solveEven();
    else
        solveOdd();

    std::cout << "Backtracking: " << size << " queens" << "\n";
    std::cout << "Number of solutions: " << solutions << "\n";
    return 0;
}
