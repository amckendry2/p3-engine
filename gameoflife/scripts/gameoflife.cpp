#include "game.h"
#include <math.h>
#include <vector>

Color black{0,0,0};
Color white{255,255,255};
int selx = 0;
int sely = 0;

int t = 0;

vector<int> grid{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,
    0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void _init(P3& p3){
}

void _update(P3& p3, double fdt){
    t+=1;
    if(t%60 == 0){
	vector<int> newGrid(256);
    }
}

void _draw(P3& p3, double){
    p3.clearScreen(white);
    for(int i = 0; i < grid.size(); i++){
	int x = i % 16 * 8;
	int y = floor(i/16) * 8;
	if(grid[i] == 1)
	    p3.rectFill(x, y, 8, 8, black);
    }

}



int getGridVal(int x, int y){
    if(x < 0 || x > 15 || y < 0 || y > 15){
	return 0;
    }
    return x*16 + y;
}

void setGridVal(int x, int y, int val, vector<int>& gridBuf){
    gridBuf[x*16 + y] = val;
}

int countNeighbors(int x, int y){
    int count = 0;
    for (int xi = x - 1; xi <= x + 1; xi++){
	for (int yi = y - 1; yi <= y + 1; yi++){
	    if(xi != x && yi != y){
	        count += getGridVal(xi, yi);		
	    }
	}
    }
    return count;
}
