# Arduino Ping Pong Game

## Overview
This Arduino project implements a simple ping pong game on an I2C LCD display, allowing two players to control paddles and compete to score points. The game incorporates features like adjustable ball speed, score tracking, and game-over conditions.

## Features
- **Two Player Mode**: Supports two players using buttons to control paddles.
- **Dynamic Ball Speed**: The ball speed increases gradually, enhancing gameplay difficulty.
- **Score Tracking**: Each player's score is displayed on the LCD, and the game ends when a player reaches 10 points.
- **Game Reset**: After a game-over, players can reset the game to start anew.
- **Simple Controls**: Easy button controls for paddle movement.

## Hardware Requirements
- Arduino board (e.g., Arduino Uno)<br>
<img src="https://github.com/user-attachments/assets/19d775dd-591b-4213-9fb4-46e64a035710" alt="Ping Pong Game" width="300" /><br>
- I2C LCD display (e.g., 20x4)<br>
<img src="https://github.com/user-attachments/assets/27685555-1894-4e65-8259-49b063b496fc" alt="I2C LCD Display" width="300" /><br>
- Push buttons (4 in total)<br>
<img src="https://github.com/user-attachments/assets/e1b2cb7a-1751-4d75-a84e-6144d75072ad" alt="Push Buttons" width="300" /><br>
- Breadboard and jumper wires<br>
<img src="https://github.com/user-attachments/assets/433e2928-560a-4429-a543-a697e1f78ff1" alt="Breadboard" width="300" />
<img src="https://github.com/user-attachments/assets/f3d9fb72-f04d-4151-8575-249e614ef931" alt="Jumper Wires" width="300" />

## Software Requirements
- Arduino IDE

## Installation
1. **Connect Hardware**: 
   - Connect the I2C LCD to the Arduino.
   - Connect the buttons to the specified digital pins.
   <img src="https://github.com/user-attachments/assets/07b4d66e-c21e-4b06-8c01-6a3b1398ee9b" alt="Wiring Diagram" width="300" />

2. **Install Libraries**:
   - Ensure the following libraries are installed in your Arduino IDE:
     - `Wire.h`
     - `LiquidCrystal_I2C.h`

3. **Upload the Code**:
   - Open the Arduino IDE.
   - Copy the code provided in `PingPongGame.ino` and paste it into a new sketch.
   - Save the sketch as `PingPongGame.ino`.
   - Connect your Arduino board to your computer and select the correct board and port in the IDE.
   - Click the upload button to compile and upload the code to your Arduino.

## Usage
- **Start the Game**: Once the code is uploaded, the game starts automatically.
- **Player Controls**:
  - **Player 1**:
    - Move Paddle Up: Button connected to pin 5
    - Move Paddle Down: Button connected to pin 10
  - **Player 2**:
    - Move Paddle Up: Button connected to pin 2
    - Move Paddle Down: Button connected to pin 3
- **Game Over**: The game will display "Game Over!" when a player reaches a score of 10. You can reset the game by pressing any button.
