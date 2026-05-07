#include "raylib.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>
using namespace std;

int windowWidth=1000;//variables for window width and length 
int windowLength=1000;
float circleRadius=35;//set circle radius

int headTrack; 

//vector<int> headTrack; //use queue to track the amount of heads one collects; used to detect collisions with walls later
deque<Vector2> tailPosition; //uses a deque to track position of head 
//int tailLength = 0; not needed

class barrier { //this is the class that I will use for the barrier that stand in the way of the dragon
    public:

    Color towerColor;   
    float  barrierWidth=250;
    float  barrierLength=150;
    Rectangle tower;
    int towerDamage;


    barrier() {
        //srand(time(0));
        towerDamage = 1;//rand() % 20;// this create a random amount of damage for the tower
        
        if (towerDamage<=5) {//if ladder determines colour of tower based on how much damage it does
            towerColor={21, 166, 191, 255};//must put in constructor because if statement will not work
        }
        else if (towerDamage>5 && towerDamage<=10){
            towerColor={51, 161, 212, 255};
        }
        else if (towerDamage>10 && towerDamage<=15) {
            towerColor={51, 121, 212, 255};
        }
        else {
            towerColor={51, 121, 212, 255};
        }
          
        tower = {0, 100, barrierWidth, barrierLength}; //set barrier for rectangle; we will have to create a variable for position of rectangle later
    };

  

    void drawTower() {
        DrawRectangleRec(tower, towerColor); //sets rectangle size with coloru 
        DrawText(TextFormat("%i",towerDamage), 100, 200, 20, BLACK);//draws text of the damage

    }

    
};

class dragonHead {//this is the class that will be used for the dragon heads the player can collect
    public:

    Vector2 position; 

    dragonHead() {
        position = GenerateRandomPos();
    };

    Vector2 GenerateRandomPos() {
        float x=GetRandomValue(0, windowWidth - 35);
        float y=GetRandomValue(0, windowWidth - 500);//generate position of food
        return Vector2{x, y};
    }

    void Draw() {
        DrawCircle(position.x, position.y, circleRadius, YELLOW); 
    }
    
};

int main() {

    InitWindow(windowWidth, windowLength, "Tail of the Dragon");//establishes window 
    SetTargetFPS(60);

    dragonHead obj;//object created for dragone heads to draw
    barrier obj2;

    Vector2 circlePos = {};//checks circle movement
   

    Color backgroundColour { 0, 25, 25}; //estalblishes window 
    

    //int xPosition;//the variables that will control dragon movement
    //int yPosition; 

    bool barrierIsColliding;//checks if the dragon is colliding with box
    bool headIsColliding; //check if dragon collides with head
    

    while (!WindowShouldClose()) {        
        ClearBackground(backgroundColour);
        //xPosition=GetMouseX();//get position
        //yPosition=GetMouseY();
        circlePos=GetMousePosition();//get postion based on mouse position
        tailPosition.push_front(circlePos); //stores position of player


        if (tailPosition.size() > headTrack*5) { //change later; checks if the amount of positions is larger than head and delete position or something like that
            tailPosition.pop_back(); 
        }

        barrierIsColliding = CheckCollisionCircleRec(circlePos, circleRadius, obj2.tower); //checks if barrier and collides with dragon
        headIsColliding = CheckCollisionCircles(circlePos, circleRadius, obj.position, circleRadius); //checks if the heads are colliding

        BeginDrawing();

        obj2.drawTower();//Draws the diagram
        DrawCircleV(circlePos, circleRadius, YELLOW); //using vector to draw circle given radius
        obj.Draw();//calls draw function from dragonHead class
        

        EndDrawing();

       /* if (body.size() > (tailLength + 1) * 10) { 
            body.pop_back(); 
        }*/

        if (barrierIsColliding){
            DrawText("COLLISION!", 10, 40, 20, RED); //testing collision
            //headTrack.resize(headTrack.size()-obj2.towerDamage);
            headTrack=headTrack-obj2.towerDamage;
            WaitTime(0.2);
            cout<<headTrack; 
        }

        if (headIsColliding) {
            //tailLength++;
            //headTrack.push_back(1);
            headTrack++;
            obj.position=obj.GenerateRandomPos();
            headIsColliding=false;
        }

        for (int i = 0; i <=headTrack; i++) {
            int index = i * 5;
            if (index < tailPosition.size()) {
                DrawCircleV(tailPosition[index], circleRadius, YELLOW);
            }
        }


        /*for (int i=0; i<headTrack.size(); i++) {
            DrawCircle(circlePos.x, circlePos.y + circleRadius + 10, circleRadius, YELLOW);
            //cout<<"added"; test for gaining heads; this keeps head collection stagnant however
        }*/

    }
    CloseWindow();
    /*for (int i = 0; i<=headTrack.size(); i++) {
        cout<<i;
    }This was used to check the size of the array given storing how many*/




}