#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

void displayGrid(int xRange, int yRange, string a[yRange][xRange]);

int main()
{
    const int gridX = 15;
    const int gridY = 10;

    string Axis[gridY][gridX];

    for(int i = 0; i < gridY; i++){
        for(int j = 0; j < gridX; j++){
            Axis[i][j] = '$';
            
        }
    }
    displayGrid(gridX, gridY,Axis[gridY][gridX]);

    return 0;
}

void displayGrid(int xRange, int yRange, string a[yRange][xRange]){
    int xCount = 0;
    int yCount = -1;

    //xRange += 1;
    yRange += 1;

    for(int i = 0; i < yRange; i++)
    {
        if (i > 0){
            if (yCount < 10){

                cout << " " << yCount << "  ";
            }
            else{
                cout << yCount << "  ";
            }
        }
        
        
        if (i == 0){
            for (int n = 0; n < xRange; n++)
            {
                if (xCount == 0){
                    cout << "    " << xCount;
                }
                else if (xCount < 10 ){
                    cout << "  " << xCount;
                }else{
                    cout << " " << xCount;
                }
                
                xCount += 1;
            }
            
        }else{
            for (int j = 0; j <xRange; j++)
            {
                cout << a[i][j] << "  ";
            }
        }
        

        cout << "" << endl;
        yCount += 1;
    }


}
