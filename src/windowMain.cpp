#include "raylib.h"
#include <iostream>
#include <string>
#include <queue>
using namespace std;

int windowWidth=1000;//variables for window width and length 
int windowLength=1000;
float circleRadius=35;//set circle radius

queue<int> headTrack; //use queue to track the amount of heads one collects

class dragonHead { //this is the class that will be used for the dragon heads the player can collect
    public:

    Vector2 position; 

    dragonHead() {
        position = GenerateRandomPos();
    };

    Vector2 GenerateRandomPos() {
        float x=GetRandomValue(0, windowWidth - 35);
        float y=GetRandomValue(0, windowWidth - 35);
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

    //Vector2 circlePos = {};//checks circle movement
   

    Color backgroundColour { 0, 25, 25}; //estalblishes window 
    Color wallColour {0,0,0};//establishes colour of the wall

    //int xPosition;//the variables that will control dragon movement
    //int yPosition; 

    float  barrierWidth=250;
    float  barrierLength=150;

    Rectangle barrier = {0, 100, barrierWidth, barrierLength}; //set barrier for rectangle

    bool barrierIsColliding;//checks if the dragon is colliding with box
    bool headIsColliding; //check if dragon collides with head
    

    while (!WindowShouldClose()) {        
        ClearBackground(backgroundColour);
        //xPosition=GetMouseX();//get position
        //yPosition=GetMouseY();
        Vector2 circlePos=GetMousePosition();//get postion
    
        barrierIsColliding = CheckCollisionCircleRec(circlePos, circleRadius, barrier); //checks if rectangle and circle collide
        headIsColliding = CheckCollisionCircles(circlePos, circleRadius, obj.position, circleRadius); 

        BeginDrawing();

        DrawCircleV(circlePos, circleRadius, YELLOW); //using vector to draw circle given radius
        DrawRectangleRec(barrier, BLUE);
        
        obj.Draw();//calls draw function from dragonHead class
        

        EndDrawing();

        if (barrierIsColliding){
            DrawText("COLLISION!", 10, 40, 20, RED); 
        }

        if (headIsColliding) {
            headTrack.push(1);
        }

        for (int i; i<headTrack.size(); i++) {
            DrawCircle(circlePos.x, circlePos.y + circleRadius + 10, circleRadius, YELLOW);
        }
    }
CloseWindow();
}