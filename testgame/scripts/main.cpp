#include "game.h"
#include <math.h>
using namespace std;

float x = 62;
float y = 62;
float xVel = 0;
float yVel = 0;
float speed = .2;
double angle = 0;
bool thrust = false;
int t = 0;

Color red {255, 0, 0};
Color green{0, 255, 0};
Color blue{0, 0, 255};
Color purple{255, 0, 255};
Color brown{255, 255, 0};

void _init(P3& p3){
    int testint = 100;
    Uint8 testint2 = (Uint8)testint;
    testint2 += 200;
    cout << testint << endl;
    cout << (int)testint2 << endl;
    p3.loadSpriteDirectory("sprites");
    p3.loadSFXDirectory("sfx");
    p3.loadMusicDirectory("music");
    p3.loadSpriteMapDirectory("maps");
    p3.setPalette({
	    {255, 0, 0},
	    green,
	    blue,
	    purple,
	    brown
	});
}

double smoothStep(double e0, double e1, double pt){
    double t = clamp((pt - e0) / (e1 - e0), 0.0, 1.0);
    return t * t * (3.0 - 2.0 * t);
}

int step(double e0, double pt){
    return pt > e0 ? 1 : 0;
}

void testShader(double x, double y, Uint32 u_time, Uint8* r, Uint8* g, Uint8* b, Uint8* a){
    double widthMod = abs((u_time % 2000) / 2000.0 - 0.5) * 1.0;
    double rMod = abs((u_time % 1000) / 1000.0 - 0.5) * 255.0;
    double gMod = abs(((u_time + 300) % 1000) / 1000.0 - 0.5) * 255.0;
    double bMod = abs(((u_time + 600) % 1000) / 1000.0 - 0.5) * 255.0;
    double dist = sqrt(pow((x - 0.5),2) + pow((y - 0.5),2));
    double cPct = step(dist, widthMod);
    *r = (Uint8)(rMod * cPct);
    *g = (Uint8)(gMod * cPct);
    if(x==.5 && y==.5)
	cout << "in shader before: " << (int)*b << endl;
    *b = (Uint8)(bMod * cPct);
    if(x==.5 && y==.5)
	cout << "in shader after:  " << (int)*b << endl;
}

void testShader2(double x, double y, Uint32 u_time, Uint8* r, Uint8* g, Uint8* b, Uint8* a){
    double widthMod = abs((u_time % 2000) / 2000.0 - 0.5) * 0.75;
    double rMod = abs((u_time % 1000) / 1000.0 - 0.5) * 100.0;
    double gMod = abs(((u_time + 300) % 1000) / 1000.0 - 0.5) * 100.0;
    double bMod = abs(((u_time + 600) % 1000) / 1000.0 - 0.5) * 100.0;
    // cout << width << endl;
    double cPct = smoothStep(.25 - widthMod, .25, x) - smoothStep(.25, .25 + widthMod, x);
    // int rPct = step(.5, x);
    *r = 100;//rMod * cPct;
    *g = 100;//gMod * cPct;
    *b = 100;//bMod * cPct;
}

void _update(P3& p3, double fdt){
    t++;
    thrust = false;
    if(p3.buttonDown("Up")){

	
	xVel+=sin(angle * M_PI / 180) * .05;
	yVel-=cos(angle * M_PI / 180) * .05;
	thrust = true;
    }
    if(p3.buttonDown("Down")){
	xVel-=sin(angle * M_PI / 180) * .05;
	yVel+=cos(angle * M_PI / 180) * .05;
	thrust = true;
    }
    if(p3.buttonDown("Left")){
        angle -= 3;
    }
    if(p3.buttonDown("Right")){
	angle += 3;
    }
    x+=xVel;
    y+=yVel;
    int sw = p3.getCanvasWidth();
    int sh = p3.getCanvasHeight();
    if(clamp((int)x, 0, sw-8) != (int)x){
	x-=xVel;
	xVel *= -.5;
	// p3.playSFX("boing", -1, (x/(sw-8))*2 - 1,(1-(y/(sh-8))) / 2);
    }
    if(clamp((int)y, 0, sh-8) != (int)y){
	y-=yVel;
	yVel *= -.5;
	// p3.playSFX("boing", -1, (x/(sw-8))*2 - 1, (1-(y/(sh-8))) / 2);
    }
}

void _draw(P3& p3, double){
    Color black{0,0,0};
    p3.clearScreen(black);
    // p3.drawMap("spriteMap", 0, 0, 16, 16, 0, 0);
    // p3.circleFill(64, 64, 60, 2);
    // p3.circle(64, 64, 20, 1);
    // p3.line(64, 64, 10, 10, 3);
    // p3.rectFill(80, 60, 20, 10, 4);
    // p3.rect(80, 60, 20, 10, 0);
    
    double rads = angle * (M_PI / 180);
    int sprite = thrust ? (t / 5) % 4 : 0;
    p3.drawRotatedSprite("pixelguysheet", sprite,  x, y, rads, false);
    p3.addShader(&testShader);
    // p3.addShader(&testShader2);
}


