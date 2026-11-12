
// Wilhelm Malé (wilma870)
// Oscar Jansson (oscja211)

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>
using namespace std;

// calculates the amount of neighbors by checking for X in all adjacent squares with a double for loop.
int neighbor_count(const Grid <int> grid,int i, int j){
    int neighbors = 0;
    for (int a = i-1; a<=i+1; a++){
        for(int b = j-1; b<=j+1; b++){

            if (grid.inBounds(a,b) &&  !(a == i && b == j)){
                if(grid.get(a,b) == 88){
                    neighbors += 1;
                }
            }
        }
    }
    return neighbors;
}

// set new cells into the next grid based on the amount of neighbors it has.
// dead cell if <2 or >3, create cell if =3 and retain cell if =2.
void set_new(const Grid <int> grid,Grid <int>& new_grid,int i, int j,int neighbors){
    if(neighbors <= 1 || neighbors > 3){
        new_grid.set(i,j,45);
    }
    else if(neighbors == 3){
        new_grid.set(i,j,88);
    }else{
        new_grid.set(i,j,grid.get(i,j));
    }
}

// creates the first grid that the program then will use as a template for the game of life to start with.
Grid<int> create_grid(ifstream& given_file){
    int rows,columns;
    string text;

    getline(given_file, text);
    rows =  stoi(text);

    getline(given_file, text);
    columns = stoi(text);

    Grid<int>grid(rows, columns);
    for (int i = 0; i<rows; i++){
        getline(given_file, text);
        for(int a = 0;a<columns;a++){
        grid[i][a] = text[a];
        }
    }
    return grid;
}

// after every tick or animation you get the choice of animating, ticking or quiting.
int tick_options (){
    while(true){
        cout<<"a)nimate, t)ick, q)uit?" <<endl;
        string answer;

        cin >> answer;

        if (answer == "a"){
            return 20;
        }else if(answer == "t"){
             return 1;
        }else if(answer == "q"){
            //stänger av
            cout << "have a nice life!" << endl;
            return 0;
        }
    }
}

// program runs from main.
int main() {

    cout << "Welcome to the TDDD86 Game of Life, a simulation of the lifecycle of a bacteria colony.\n"
         << "Cells (X) live and die by the following rules:\n"
         << "- A cell with 1 or fewer neighbours dies.\n"
         << "- Locations with 2 neighbours remain stable.\n"
         << "- Locations with 3 neighbours will create life.\n"
         << "- A cell with 4 or more neighbours dies.\n"
         << endl;

    cout << "Grid input file name?";
    ifstream given_file;
    string filename;
    cin >> filename;
    given_file.open(filename);
    cout<<"" <<endl;

   Grid grid = create_grid(given_file);

   int antal;

   while(true){
       antal = tick_options();
       if (antal == 0){
           return 0;
       }
        while(antal > 0){
            antal--;
            pause(100);
            clearConsole();
            Grid new_grid = grid;
            for (int i = 0; i<grid.numRows(); i++){
                for(int j = 0;j<grid.numCols();j++){
                    cout <<(char)grid[i][j];
                    set_new(grid,new_grid,i,j,neighbor_count(grid,i,j));
                }
                cout<<"" <<endl;
            }
            grid = new_grid;
        }
   }
    return 0;
}








