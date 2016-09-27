#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>


std::vector<std::vector<int> > solutions;
std::vector<int> queens;

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
            if(queens[i] == j || abs(queens[i] - j) == abs(queenIndex - i)){
                avail = false;
                break;
            }
        }
        if(avail)
            return j;
    }
    return -1;
}

bool place(int queenIndex, int row){
    int r = nextRow(queenIndex, row);
    if(r == -1)
        return false;

    queens[queenIndex] = r;
    return true;
}

void backtrack(int queenIndex){
    queens[queenIndex] = -1;
}

bool solve(int queenIndex){
    int row = 0;
    while(true){
        //Try to place the queen on the next available row, from the variable row
        bool placed = place(queenIndex, row);
        //We were unable to place the queen, i.e: no available rows.
        if(!placed)
            return false;

        //If we were able to place the queen and it is the last queen
        if(queenIndex == queens.size() - 1){
            //Then add it to the solutions
            solutions.push_back(queens);
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
                return true;
            }
            backtrack(queenIndex);
            return false;
        }

        //Increase the row variable
        row = queens[queenIndex] + 1;
        backtrack(queenIndex);
    }

    return true;
}

int main(int argc, char* argv[]){
    int number_of_queens;
    sscanf(argv[1], "%d", &number_of_queens);

    //We need "number_of_queens" number of those rows
    for(int i = 0; i < number_of_queens; i++){
        queens.push_back(-1);
    }
    //Solve the initial board
    solve(0);
    std::cout << "Total number of solutions: " << solutions.size() << "\n";
    return 0;
}
