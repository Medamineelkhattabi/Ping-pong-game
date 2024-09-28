#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SDA A4
#define SCL A5

// Button Pins
#define Joueur_1_bouton_bas 10
#define Joueur_1_bouton_haut 5
#define Joueur_2_bouton_bas 2
#define Joueur_2_bouton_haut 3

// LCD Definitions
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 20
#define LCD_ROWS 4

// Game constants
#define PADDLE_SIZE 1
#define INITIAL_BALL_SPEED 1.0
#define PADDLE_SPEED 1

int paddle1Position = 0;
int paddle2Position = 0;
int ballPositionX = LCD_COLUMNS / 2;
int ballPositionY = LCD_ROWS / 2;
float ballDirectionX = INITIAL_BALL_SPEED;
float ballDirectionY = INITIAL_BALL_SPEED;
int player1Score = 0;
int player2Score = 0;
float ballSpeed = INITIAL_BALL_SPEED;
bool gamePaused = false;

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.backlight();

  pinMode(Joueur_1_bouton_haut, INPUT_PULLUP);
  pinMode(Joueur_1_bouton_bas, INPUT_PULLUP);
  pinMode(Joueur_2_bouton_haut, INPUT_PULLUP);
  pinMode(Joueur_2_bouton_bas, INPUT_PULLUP);
}

void loop() {
  if (gamePaused) {
    displayGameOver();
    return;
  }

  // Update game states
  updatePaddles();
  updateBall();

  // Clear LCD to redraw
  lcd.clear();

  // Draw game objects
  drawPaddles();
  drawBall();

  // Update score display
  updateScoreDisplay();

  delay(100);  // Adjust game speed
}

void MovePaddleUp(int &paddlePosition) {
  if (paddlePosition > 0) {
    paddlePosition -= PADDLE_SPEED;
  }
}

void MovePaddleDown(int &paddlePosition) {
  if (paddlePosition < (LCD_ROWS - PADDLE_SIZE)) {
    paddlePosition += PADDLE_SPEED;
  }
}

void updatePaddles() {
  // Player 1 controls
  if (digitalRead(Joueur_1_bouton_haut) == LOW) {
    MovePaddleUp(paddle1Position);
  } else if (digitalRead(Joueur_1_bouton_bas) == LOW) {
    MovePaddleDown(paddle1Position);
  }

  // Player 2 controls
  if (digitalRead(Joueur_2_bouton_haut) == LOW) {
    MovePaddleUp(paddle2Position);
  } else if (digitalRead(Joueur_2_bouton_bas) == LOW) {
    MovePaddleDown(paddle2Position);
  }

  // Ensure paddles remain in bounds
  paddle1Position = constrain(paddle1Position, 0, LCD_ROWS - PADDLE_SIZE);
  paddle2Position = constrain(paddle2Position, 0, LCD_ROWS - PADDLE_SIZE);
}

void updateBall() {
  // Update ball position based on its direction
  ballPositionX += ballDirectionX;
  ballPositionY += ballDirectionY;

  // Ball collision with paddles
  if (ballPositionX == 1 && ballPositionY >= paddle1Position && ballPositionY <= paddle1Position + PADDLE_SIZE) {
    ballDirectionX = ballSpeed;  // Bounce off player 1's paddle
    increaseBallSpeed();  // Gradually increase speed after each hit
  } else if (ballPositionX == LCD_COLUMNS - 2 && ballPositionY >= paddle2Position && ballPositionY <= paddle2Position + PADDLE_SIZE) {
    ballDirectionX = -ballSpeed;  // Bounce off player 2's paddle
    increaseBallSpeed();
  }

  // Ball collision with vertical boundaries
  if (ballPositionY <= 0 || ballPositionY >= LCD_ROWS - 1) {
    ballDirectionY = -ballDirectionY;  // Bounce off top or bottom wall
  }

  // Check if a player scored
  if (ballPositionX <= 0) {
    player2Score++;
    resetBall();
  } else if (ballPositionX >= LCD_COLUMNS - 1) {
    player1Score++;
    resetBall();
  }

  // End game condition
  if (player1Score >= 10 || player2Score >= 10) {
    gamePaused = true;
  }
}

void increaseBallSpeed() {
  ballSpeed += 0.1;  // Increase ball speed over time
}

void resetBall() {
  // Reset ball to the center of the screen
  ballPositionX = LCD_COLUMNS / 2;
  ballPositionY = LCD_ROWS / 2;
  ballDirectionX = ballSpeed;
  ballDirectionY = ballSpeed;
}

void drawPaddles() {
  // Draw player 1's paddle
  for (int i = 0; i < PADDLE_SIZE; i++) {
    lcd.setCursor(0, paddle1Position + i);
    lcd.write(byte(255));
  }

  // Draw player 2's paddle
  for (int i = 0; i < PADDLE_SIZE; i++) {
    lcd.setCursor(LCD_COLUMNS - 1, paddle2Position + i);
    lcd.write(byte(255));
  }
}

void drawBall() {
  lcd.setCursor(ballPositionX, ballPositionY);
  lcd.write(byte(255));
}

void updateScoreDisplay() {
  lcd.setCursor(LCD_COLUMNS / 2 - 2, 0);
  lcd.print(player1Score);
  lcd.setCursor(LCD_COLUMNS / 2 + 1, 0);
  lcd.print(player2Score);
}

void displayGameOver() {
  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("Game Over!");
  lcd.setCursor(3, 2);
  if (player1Score >= 10) {
    lcd.print("Player 1 Wins!");
  } else {
    lcd.print("Player 2 Wins!");
  }
  delay(2000);  // Pause to display game over message
  resetGame();  // Reset game after showing message
}

void resetGame() {
  player1Score = 0;
  player2Score = 0;
  ballSpeed = INITIAL_BALL_SPEED;
  gamePaused = false;
  resetBall();
}
