#include<iostream>
#include<windows.h>
#include<time.h>
#include<bits/stdc++.h>
#include<queue>

const int gridsize = 10; 
int iA =0, jA =0 ;//The index of an apple 

using namespace std;

void printGrid(char grid[gridsize][gridsize]);
void RandomPlaceApple(char grid[gridsize][gridsize]);
void Movement(char grid[gridsize][gridsize]);
void MoveTail(char grid[gridsize][gridsize], int ibefore, int jbefore);
void AppleEat(char grid[gridsize][gridsize], int ibefore, int jbefore, bool &apple);
bool GameOver(char grid[gridsize][gridsize]);

struct coordinates {
   int x;
   int y;
};

queue<coordinates> tail;
bool STOPGAME=true;

int main()
{
    bool GAMELOSE = true;
    setlocale(LC_ALL, "CYP");
    srand ((unsigned) time(NULL));

    char grid[gridsize][gridsize];

    for(int i = 0; i < gridsize; i++)
    {
        for(int j = 0; j < gridsize; j++)
        {
            grid[i][j] = ' ' ;
        }
    }

    cout << "The game start " << endl;
    grid[3][2] = 'o' ;
    
    do
    {
        printGrid(grid);
        Movement(grid); 
        Sleep(100);  
        system("cls");   
        
    }while(GameOver(grid) && STOPGAME);

    if(!STOPGAME)
        cout << "YOU EAT YOUR TAIL STUPID " << endl;
    
    return 0;
}

void RandomPlaceApple(char grid[gridsize][gridsize]){

    coordinates chek[gridsize*gridsize];
    int a=0, CheckIndex=0, c;

    for(int i = 0; i < gridsize; i++){
        for(int j = 0; j < gridsize; j++){
            if(grid[i][j] == ' '){
                chek[a] = {i , j};
                a++;
                CheckIndex++; //how many times this if was true
            } 
        }
    }
    
    c = 0 + (rand()%CheckIndex); //Generate the random posion of the empty arr

    grid[chek[c].x][chek[c].y] = 'a'; 
    iA = chek[c].x;
    jA = chek[c].y;

}
int x = 0;
void printGrid(char grid[gridsize][gridsize]){

    for(int i =0; i < gridsize; i++){
        grid[0][i] = '#';
        grid[gridsize-1][i] = '#';
        grid[i][0] = '#';
        grid[i][gridsize-1] = '#';
    }

    if(x == 0){
        RandomPlaceApple(grid);
        x++;
    }

    for(int i = 0; i < gridsize; i++)
    {
        for(int j = 0; j < gridsize; j++)
        {
            cout << grid[i][j] << " " ;
        }
        cout << endl;
    }

}

void Movement(char grid[gridsize][gridsize]){
    char move;
    int i, j ;
    bool tail = false, apple = false;

    cout << "Make Your move  w/s/a/d " << endl;
    cin >> move ;
    
    for(i = 0; i < gridsize; i++)
    {
        for(j = 0; j < gridsize; j++)
        {
            if(grid[i][j] == 'o')
            {
                goto Theend;
            }
        }
    }
    Theend:
    int ii, jj;
    for(ii = 0; ii < gridsize; ii++)
    {
        for(jj = 0; jj < gridsize; jj++)
        {
            if(grid[ii][jj] == '*')
            {
                tail = true;
                goto Thefinalend;
            }
        }
    }
    Thefinalend:
    int countertail = 0;
    for(int l =0 ; l < gridsize; l++){
        for(int ll=0; ll < gridsize; ll++){
            if(grid[l][ll] == '*')
                countertail++;
        }
    }

    switch (move)
    {
    case 'w':
        grid[i-1][j] = 'o';
        break;
    case 'a':
        grid[i][j-1] = 'o';
        break;
    case 's':
        grid[i+1][j] = 'o';
        break;
    case 'd':
        grid[i][j+1] = 'o';
        break;
    default:
        cout << "Not correct input " << endl;
        break;
    }
    
    grid[i][j] = ' ';

    int countertailAfter = 0;
    for(int l =0 ; l < gridsize; l++){
        for(int ll=0; ll < gridsize; ll++){
            if(grid[l][ll] == '*')
                countertailAfter++;
        }
    }

    if(countertailAfter < countertail){
        STOPGAME = false;
    }

    AppleEat(grid, i, j, apple);
    if(tail == true && apple == false)
        MoveTail(grid, i , j);

    
}

void AppleEat(char grid[gridsize][gridsize], int ibefore, int jbefore, bool &apple)
{
    int i, j;
    for(i = 0; i < gridsize; i++)
    {
        for(j = 0; j < gridsize; j++)
        {
            if(grid[i][j] == 'o')
            {
                goto Theend;
            }
        }
    }
    Theend:
    if(iA == i && jA == j){
        RandomPlaceApple(grid);
        grid[ibefore][jbefore] = '*';
        tail.push({ibefore, jbefore});
        apple = true;
    }
    
}

void MoveTail(char grid[gridsize][gridsize], int ibefore, int jbefore)
{
    coordinates last = tail.front();
    
    swap(grid[last.x][last.y] , grid[ibefore][jbefore]);
    last.x = ibefore ;
    last.y = jbefore;
    
    tail.pop();
    tail.push({last.x , last.y});
    
}

bool GameOver(char grid[gridsize][gridsize]){
    
    int n = 0, p=0;
    for(int ii = 0; ii < gridsize; ii++)
    {
        for(int jj = 0; jj < gridsize; jj++)
        {
            if(grid[ii][jj] == '#'){
                n++;
            }  
        }
    }

    int a = (gridsize*4) - 4;
    if(n < a){
        cout << "GAME OVER YOU LOSE " << endl;
        return false;
    }
    

}
