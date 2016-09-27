#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>


std::vector<std::vector<std::vector<int> > > solutions;
std::vector<std::vector<int> > queens;
std::vector<int> emptyRow;

void drawBoard(std::vector<std::vector<int> > board){
    for(int i = 0; i < board.size(); i++){
        for(int q = 0; q < board.size(); q++){
            std::cout << board[q][i];
        }
        std::cout << "\n";
    }
}

int nextRow(int queenIndex, int row){
    for(int j = row; j < queens.size(); j++){
        bool avail = true;
        for(int i = 0; i < queenIndex; i++){
            for(int q = 0; q < queens.size(); q++){
                if(queens[i][q] == 1){
/*
                    std::cout << "run" << "\n";
                    std::cout << j << "\n";
                    std::cout << q << ", " << j << "\n";
                    std::cout << abs(q - j) << ", " << abs(queenIndex - i) << "\n";
*/
                    if(q == j || abs(q - j) == abs(queenIndex - i)){
                        avail = false;
                        break;
                    }
                }
            }
            if(!avail)
                break;
        }
        if(avail)
            return j;
    }
    return -1;
}

int place(int queenIndex, int row){
    int r = nextRow(queenIndex, row);
    if(r != -1)
        queens[queenIndex][r] = 1;
    return r;
}

void backtrack(int queenIndex){
    queens[queenIndex] = emptyRow;
}

bool solve(int queenIndex){
    int row = 0;
    while(true){
        //Try to place the queen on the next available row, from the variable row
        int placedAt = place(queenIndex, row);
        //We were unable to place the queen, i.e: no available rows.
        if(placedAt == -1)
            return false;

        //If we were able to place the queen and it is the last queen
        if(queenIndex == queens.size() - 1){
            //Then add it to the solutions
            solutions.push_back(queens);
            std::cout << "# of solutions found so far: " << solutions.size() << "\n";
            //Backtrack
            backtrack(queenIndex);
            //Return false, this will allow us to find as many solutions as possible
            //Return true here if you only want to find one solution
            return false;
        }

        //Recursively try the next queen
        if(solve(queenIndex + 1))
            return true;

        //Is it the final row that we can try?
        if(row == queens.size() - 1){
            //Is it the "first" queen
            if(queenIndex == 0){
                //Then we have found all solutions that we can, return true HerE
                //to exit
                std::cout << "# of solutions: " << solutions.size() << "\n";
                return true;
            }
            backtrack(queenIndex);
            return false;
        }

        //Increase the row variable
        row = placedAt + 1;
        backtrack(queenIndex);
    }

    return true;
}

int main(int argc, char* argv[]){
    int number_of_queens;
    sscanf(argv[1], "%d", &number_of_queens);

    //We need one row of size "number_of_queens"
    for(int i = 0; i < number_of_queens; i++){
        emptyRow.push_back(0);
    }
    //We need "number_of_queens" number of those rows
    for(int i = 0; i < number_of_queens; i++){
        queens.push_back(emptyRow);
    }
    //Solve the initial board
    solve(0);
    return 0;
}
