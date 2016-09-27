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
    std::cout << "]" << "\n";
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
    unsigned int tmp;
    for(;;){
        if(t != 0){
            lsb = filled & ~(t & -t);
            steps[n] = t;
            n++;
            std::cout << "****************** Added T ******************" << "\n";
            std::cout << "T: " << t << "\n";

            std::cout << tmpRow[n - 1] << ", " << tmpLeft[n - 1] << ", " << tmpRight[n - 1] << "\n";
            //Set the queens position to zero
            tmpRow[n] = tmpRow[n - 1] & lsb;
            tmpLeft[n] = tmpLeft[n - 1] & (filled & lsb);
            tmpLeft[n] = filled & (tmpLeft[n] << 1 | (1 << 0));

            tmpRight[n] = tmpRight[n - 1] & (filled & lsb);
            tmpRight[n] = filled & (tmpRight[n] >> 1 | (1 << size_m1));

            t = tmpRow[n] & tmpLeft[n] & tmpRight[n];
            std::cout << tmpRow[n] << ", " << tmpLeft[n] << ", " << tmpRight[n] << "\n";
            std::cout << "t: " << t << "\n";
        }else{
            std::cout << "================== T is zero ==================" << "\n";
            std::cout << "T: " << t << "\n";
            n --;
            t = steps[n];
            lsb = filled & ~(t & -t);
            std::cout << "T before lsb: " << t << "\n";
            t &= lsb;
            std::cout << "T is now: " << t << "\n";
        }

        if(n == size){
            std::cout << "Solution has been found" << "\n";
            for(int i = 0; i < n; i++){
                t = steps[i];
                lsb = filled & ~(t & -t);
                bits.push_back(lsb);
            }
            drawBoard();
            break;
        }
        std::cout << "N: " << n << "\n";
    }
/*
int row = collision(queenIndex, firstRow);
if(row == -1)
    return false;
bits[queenIndex] = row;

if(queenIndex == size_m1){
    return false;
}

if(solve(queenIndex + 1, filled))
    return true;

if(bits[queenIndex] == endMarker){
    return queenIndex == 0;
}

//Shift the position by 1 and set the pushed position to 1
firstRow = bits[queenIndex] << 1 | 1;
//Set every position above the shifted position to 1 and everything else to 0
//e.g: Position: 11101 becomes: 11011 which becomes 11000
firstRow = filled - ((~firstRow & -firstRow) - 1);

return solve(queenIndex, firstRow);


*/

}


int main(int argc, char* argv[]){
    sscanf(argv[1], "%d", &size);
    size_m1 = size - 1;
    filled = (1 << size) - 1;
    endMarker =  filled >> 1;

    for(int i = 0; i < size; i++){
//        bits.push_back(filled);
        positions.push_back(pow(2, i));
        std::cout << pow(2, i) << "\n";
    }

    solve(0, filled);

    std::cout << "Backtracking: " << size << " queens" << "\n";
    std::cout << "Number of solutions: " << solutions << "\n";
    return 0;
}
