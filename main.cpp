#include "raylib.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Function to check if a point is inside a rectangle
bool IsPointInsideRectangle(Vector2 point, Rectangle rect) {
    return (point.x >= rect.x && point.x <= rect.x + rect.width &&
            point.y >= rect.y && point.y <= rect.y + rect.height);
}

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Simons memory game");
    vector<int> vect;
    Texture2D background = LoadTexture("resources/background.png");
    Font font = LoadFontEx("resources/JokermanFont.ttf", 150,0,250);
    Font font1 = LoadFontEx("resources/BlackadderITC.otf", 150,0,250);
    // if(font.baseSize>0){
    //     cout<<"pic not found ";
    //     return -1;
    // }
    // Box variables
    Rectangle boxes[4] = {
        {150, 100, 150, 100},
        {450, 100, 150, 100},
        {150, 300, 150, 100}, 
        {450, 300, 150, 100}
    };
    
    Color boxColors[4] = {RED, GREEN, BLUE, YELLOW};
    Color boxHoverColors[4] = {MAROON, DARKGREEN, DARKBLUE, GOLD};
    Color boxClickColors = PURPLE;
    Color boxblinkColors = WHITE;

    float clickTimers[4] = {0.0f, 0.0f, 0.0f, 0.0f}; // Timers for each box
    float blinkTimers[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    SetTargetFPS(60); // Set the frame rate
      int level =0; 
      bool out = false;
      int *answer = new int[100];
      int *userInput = new int[level];
      int flag = 0;
      float startTimer=0.500f;
      bool startCond=true;
      int prevRandom = -1;
      bool check=true;
    
      //bool out1=true;
    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
      
         while(!out){
            level++;
           if(WindowShouldClose()){
                CloseWindow(); // Close window and OpenGL context
                 return 0;
            } 
            int randomNumber;
            flag=0;
              while(flag == 0){
                 randomNumber = (rand() % 4);
                 flag =1;
            }
            
            // DrawText(TextFormat("number: %d", randomNumber), 100, 50, 20, BLACK);
            //  DrawText(TextFormat("Level: %d", level), 10, 100, 20, BLACK);
             blinkTimers[randomNumber]=0.450f;
            // Vector2 mousePoint = GetMousePosition();
             //float deltaTime = GetFrameTime(); // Get time elapsed between frames
        //         for (int i = 0; i < 4; i++) {
        //     if (clickTimers[i] > 0) {
        //         clickTimers[i] -= deltaTime; // Decrease timer
        //     }
        //     if (IsPointInsideRectangle(mousePoint, boxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        //         clickTimers[i] = 0.250f; // Set timer to 0.250 second when clicked    
        //     }
        // }
               BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawText(TextFormat("number: %d", randomNumber), 100, 50, 20, BLACK);
             DrawText(TextFormat("Level: %d", level), 10, 100, 20, BLACK);
    for (int i = 0; i < 4; i++) {
            // if (clickTimers[i] > 0) { 
            //    if(clickTimers[0]>0) {out=true;}
            //  DrawRectangleRec(boxes[i], boxClickColors);
            // } else
            //  if (IsPointInsideRectangle(mousePoint, boxes[i])) {
            //     DrawRectangleRec(boxes[i], boxHoverColors[i]);
            // } 
            //else {
                DrawRectangleRounded((Rectangle)boxes[i], 0.5f, 10, boxColors[i]);
                // DrawRectangleRec(boxes[i], boxColors[i]);
            //
        }
        EndDrawing();
        // while(startCond){
        //     float deltaTime2=GetFrameTime();
        //     if(startTimer>0){
        //         startTimer-=deltaTime2;
        //      DrawText("Game starting", 200, 50, 40, RED);
        //      }
        //    if(startTimer<=0.0f){
        //       out1 = false;
        //    }
           
        // }
       bool out1=false;
         check=true;
        while(!out1){
            startCond=false;
            // check =true;
             Vector2 mousePoint = GetMousePosition();
             if(WindowShouldClose()){
                CloseWindow(); // Close window and OpenGL context
                 return 0;
            }
            float deltaTime1 = GetFrameTime();
            if(blinkTimers[randomNumber] > 0){
            blinkTimers[randomNumber] -= deltaTime1; // Decrease timer
            }
            for(int i=0;i<4;i++){
                 if (clickTimers[i] > 0) {
                clickTimers[i] -= deltaTime1; // Decrease timer
            }
            if (IsPointInsideRectangle(mousePoint, boxes[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                clickTimers[i] = 0.250f; // Set timer to 0.250 second when clicked    
            }
            }
            // DrawText(TextFormat("number: %d", randomNumber), 100, 50, 20, BLACK);
            //  DrawText(TextFormat("Level: %d", level), 10, 100, 20, BLACK);
                     BeginDrawing();
        ClearBackground(RAYWHITE);
       DrawTexture(background, 0, 0, WHITE);
        DrawText(TextFormat("number: %d", randomNumber), 100, 50, 20, BLACK);
             DrawText(TextFormat("Level: %d", level), 10, 100, 20, BLACK);
    for (int i = 0; i < 4; i++) {
       //we can add timer here maybe
           
            if (blinkTimers[i] > 0) { 
                DrawRectangleRounded((Rectangle)boxes[i], 0.5f, 10, boxblinkColors);
             //DrawRectangleRec(boxes[i], boxblinkColors);
            }else if (clickTimers[i] > 0) { 
                
               if(clickTimers[randomNumber]>0){ 
                // check=false;
                clickTimers[randomNumber]=0.0f;
                out1=true;
               }
            // }else if (clickTimers[randomNumber]==0){
            //     out1=true;
            //     out=true;
            // }
            else{
                out1=true;
                out=true;
            }
            DrawRectangleRounded((Rectangle)boxes[i], 0.5f, 10, boxClickColors);
             //DrawRectangleRec(boxes[i], boxClickColors);
            }else if (IsPointInsideRectangle(mousePoint, boxes[i])) {
                DrawRectangleRounded((Rectangle)boxes[i], 0.5f, 10, boxHoverColors[i]);
                // DrawRectangleRec(boxes[i], boxHoverColors[i]);
            } else {
                DrawRectangleRounded((Rectangle)boxes[i], 0.5f, 10, boxColors[i]);
                //DrawRectangleRec(boxes[i], boxColors[i]);
            }
            
        }
    // DrawText("Waiting", 300, 200, 40, RED);
        EndDrawing();
        }
        prevRandom = randomNumber;
        }
           BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawTextEx(font1, TextFormat("Game Over"), (Vector2){ screenWidth/7.5, screenHeight/2.5 }, 150, 1, BLACK);
        //DrawText("Game Over", screenWidth/5.5, screenHeight/3, 100, RED);
        EndDrawing();
    }
        UnloadTexture(background);
        CloseWindow(); // Close window and OpenGL context
     return 0;
}

