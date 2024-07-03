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
bool IsAnyKeyPressed() {
    for (int key = 32; key < 349; key++) { // 32 to 348 are the key codes in raylib
        if (IsKeyPressed(key)) {
            return true;
        }
    }
    return false;
}
 
int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Simons memory game");
    InitAudioDevice();
     Sound beepSound = LoadSound("resources/wrongAnswerSound.wav");
     
    vector<int> gameSeq;
    // vector<int> playerSeq;
    int *playerSeq = new int[0];
    Texture2D background = LoadTexture("resources/background1.png");
    Texture2D startBg = LoadTexture("resources/startBg.png");
    Font font = LoadFontEx("resources/JokermanFont.ttf", 150,0,250);
    Font font1 = LoadFontEx("resources/PressStart2p.ttf", 150,0,250);
    // if(font.baseSize>0){
    //     cout<<"pic not found ";
    //     return -1;
    // }
    // Box variables
    Rectangle boxes[4] = {
        {225, 175, 150, 100},
        {425, 175, 150, 100},
        {225, 325, 150, 100}, 
        {425, 325, 150, 100}
    };
    
    Color boxColors[4] = {RED, GREEN, BLUE, YELLOW};
    Color boxHoverColors[4] = {MAROON, DARKGREEN, DARKBLUE, GOLD};
    Color boxClickColors = PURPLE;
    Color boxblinkColors = WHITE;

    float clickTimers[4] = {0.0f, 0.0f, 0.0f, 0.0f}; // Timers for each box
    float blinkTimers[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    SetTargetFPS(60); // Set the frame rate
      int level =0; 
      int highscore=0;
      bool out = true;
      bool play = false;
      
    //   float startTime=2.50f;
    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
   bool keySpacePressed = IsKeyPressed(KEY_SPACE);
      while(!play){
          BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(startBg, 0, 0, WHITE);
        if(WindowShouldClose()){
                CloseWindow(); // Close window and OpenGL context
                 return 0;
            } 
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsAnyKeyPressed()){
             out=false;
            play=true;
//          UnloadTexture(startBg);
           }
           EndDrawing();
      }
         while(!out){
            level++;
            if(level>highscore){
                highscore=level;
            }
            playerSeq= new int[level];
            for(int i=0;i<level;i++){
                playerSeq[i]=-1;
            }
           if(WindowShouldClose()){
                CloseWindow(); // Close window and OpenGL context
                 return 0;
            } 
            int randomNumber = (rand() % 4);
            gameSeq.push_back(randomNumber);
            for(int j=0;j<gameSeq.size();j++){
                cout<<gameSeq[j];
            }
            cout<<" ";
             blinkTimers[randomNumber]=0.450f;
               BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        //DrawText(TextFormat("number: %d", randomNumber), 100, 50, 20, BLACK);
            DrawTextEx(font1, TextFormat("Level: %d", level), (Vector2){ screenWidth/80, screenHeight/7 }, 18, 1, DARKGRAY);
    for (int i = 0; i < 4; i++) {
                DrawRectangleRounded((Rectangle)boxes[i], 0.5f, 10, boxColors[i]);
             
        }
        EndDrawing();
       bool out1=false;
         int j=0,k=0;
        while(!out1){
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
        //DrawText(TextFormat("number: %d", randomNumber), 100, 50, 20, BLACK);
            DrawTextEx(font1, TextFormat("Level: %d", level), (Vector2){ screenWidth/80, screenHeight/7 }, 18, 1, DARKGRAY);
             DrawTextEx(font1, TextFormat("Highest Score: %d", highscore), (Vector2){ screenWidth/2, screenHeight/7 }, 18, 1, DARKGRAY);
             //DrawText(TextFormat("Level: %d", level), 10, 100, 20, BLACK);

    for (int i = 0; i < 4; i++) {
       //we can add timer here maybe
           
            if (blinkTimers[i] > 0) { 
                DrawRectangleRounded((Rectangle)boxes[i], 0.5f, 10, boxblinkColors);
            }else if (clickTimers[i] > 0) { 
                playerSeq[j++]=i;
                
                    bool mainloop=true; 
                    while(mainloop){
                    if(gameSeq[gameSeq.size()-1]==playerSeq[level-1]){
                       mainloop=false;
                        out1=true;
                    }
                    else if(gameSeq[k]==playerSeq[k]){
                       mainloop=false;  
                    k++;
                    }else{
                        PlaySound(beepSound);
                        mainloop=false;
                        out1=true;
                        out=true;
                    }
                }
                clickTimers[i]=0.0f;
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
        //prevRandom = randomNumber;
        }
           BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawTextEx(font1, TextFormat("Game Over"), (Vector2){ screenWidth/8.5, screenHeight/2.5 }, 75, 1, BLACK);
        //DrawText("Game Over", screenWidth/5.5, screenHeight/3, 100, RED);
         DrawTextEx(font1, TextFormat("press Esc To exit the game,\n\n space to play again.."), (Vector2){ screenWidth/9, screenHeight/1.5 }, 25, 1, BLACK);
         if(keySpacePressed){
         level =0; 
       play = false;
       gameSeq.clear();
           }
        EndDrawing();
    }
    UnloadSound(beepSound); // Unload sound
    CloseAudioDevice();
        UnloadTexture(startBg);
        UnloadTexture(background);
        CloseWindow(); // Close window and OpenGL context
     return 0;
}

