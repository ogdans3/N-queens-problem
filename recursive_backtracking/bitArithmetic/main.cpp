#include <iostream>
#include <vector>
#include <cmath>

int size;
int size_m1;
int solutions;
unsigned int endMarker;
unsigned int filled;
unsigned int q;
unsigned int t;
unsigned int bit;

std::vector<unsigned int> bits;
std::vector<int> positions;

void drawBoard(){
    std::cout << "[ ";
    for(int i = 0; i < bits.size(); i++){
        bit = bits[i];
        bit = (filled & ~bit);
        for(int q = 0; q < size; q++){
            if(positions[q] == bit){
                std::cout << q + 1;
                break;
            }
        }
        std::cout << " ";
    }
    std::cout << "]" << "       # of solutions: " << solutions << "\n";
}

bool solve(int queenIndex, unsigned int firstRow){
    unsigned int steps[size];
    unsigned int tmpLeft[size];
    unsigned int tmpRight[size];
    unsigned int tmpRow[size];

    tmpRow[0] = filled;
    tmpLeft[0] = filled;
    tmpRight[0] = filled;
    int n = 0;
    unsigned int lsb;
    t = filled;
    for(;;){
        if(t != 0){
            lsb = filled & ~(t & -t);
            steps[n] = t;
            n++;
//            std::cout << "****************** Added T ******************" << "\n";
//            std::cout << "T: " << t << "\n";

//            std::cout << tmpRow[n - 1] << ", " << tmpLeft[n - 1] << ", " << tmpRight[n - 1] << "\n";
            //Set the queens position to zero
            tmpRow[n] = tmpRow[n - 1] & lsb;
            tmpLeft[n] = tmpLeft[n - 1] & (filled & lsb);
            tmpLeft[n] = filled & (tmpLeft[n] << 1 | (1 << 0));

            tmpRight[n] = tmpRight[n - 1] & (filled & lsb);
            tmpRight[n] = filled & (tmpRight[n] >> 1 | (1 << size_m1));

            t = tmpRow[n] & tmpLeft[n] & tmpRight[n];
//            std::cout << tmpRow[n] << ", " << tmpLeft[n] << ", " << tmpRight[n] << "\n";
//            std::cout << "t: " << t << "\n";
        }else{
            if(n == 0)
                return true;
//            std::cout << "================== T is zero ==================" << "\n";
//            std::cout << "T: " << t << "\n";
            n --;
            t = steps[n];
            lsb = filled & ~(t & -t);
//            std::cout << "T before lsb: " << t << "\n";
            t &= lsb;
//            std::cout << "T is now: " << t << "\n";
        }

        if(n == size){
            bits.clear();
            for(int i = 0; i < n; i++){
                t = steps[i];
                lsb = filled & ~(t & -t);
                bits.push_back(lsb);
            }
            drawBoard();
            solutions ++;

            n --;
            lsb = filled & ~(t & -t);
            t &= lsb;
        }
//        std::cout << "N: " << n << "\n";
    }
}


int main(int argc, char* argv[]){
    sscanf(argv[1], "%d", &size);
    size_m1 = size - 1;
    filled = (1 << size) - 1;
    endMarker =  filled >> 1;

    for(int i = 0; i < size; i++){
//        bits.push_back(filled);
        positions.push_back(pow(2, i));
//        std::cout << pow(2, i) << "\n";
    }

    std::cout << "Begin" << "\n";
    solve(0, filled);

    std::cout << "Backtracking: " << size << " queens" << "\n";
    std::cout << "Number of solutions: " << solutions << "\n";
    return 0;
}
