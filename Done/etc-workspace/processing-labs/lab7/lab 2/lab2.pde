float Xb, Yb, r, speedX, speedY;    //ball location, size, and speed
float Xp, Yp, w, h;                 //paddle location, wdith and height 

boolean isGameOver = false;         // when true, just draw the GameOver message and stop the animation loop to end the game  
int score = 0;

void setup() {
  size(400, 400);

  // initialize ball attributes
  Xb = random(r, width-r);      
  Yb = 30;                         
  r = 15;
  speedX = int(random(2, 4));   
  speedY = int(random(2, 4));

  // initialize paddle attributes
  w = 30; 
  h = 8;
  Xp = width/2;  
  Yp = height - h;
  
  // hide mouse cursor
  noCursor();
}

void draw() {  
background(0);

if (!isGameOver) {              //play as long as it is not game over

// DRAW game elements
    // draw Ball
    fill(255);   noStroke();
    ellipse(Xb, Yb, 2*r, 2*r);
    // draw paddle
    stroke(0, 255, 0);  strokeCap(ROUND);  strokeWeight(h);
    line(Xp-w, Yp, Xp+w, Yp);
    // draw score
    fill(255, 0, 0); textAlign(LEFT);  textSize(16);
    text("Score: " + score, 5, 15);

// MOVE game elements
    // move Paddle
    Xp = mouseX;
    // move ball 
    Xb += speedX;
    Yb += speedY;

// CHECK for collisions
    // REQ1: Add code to bounce the ball off the two sides and the top edge        
    if (Xb + r >= width || Xb - r <= 0) {
    speedX *= -1;
    }
    if (Yb - r <= 0) {
      speedY *= -1;
    }
    // REQ2: Add code to check if ball lands on the paddle. Here is the pseudo-code:
    // if the ball is at the bottom edge (hint: check Yb)                         
    //     if ball lands on paddle (hint: see the assignment on how to check this) 
    //         increment score, bounce ball up, and increase speed by 10%         
    //     else                                                                    
    //         set isGameOver to true;                                           
    if (Yb + r >= height - h) {
      if (Xb >= Xp - w && Xb <= Xp + w) {
        score++;
        speedY *= -1.1;
      } else {
        isGameOver = true;
      }
  }
} else { // if game over
    //REQ3: Add code for putting the GameOver message and stoping the animation loop 
    textAlign(CENTER);
    textSize(30);
    fill(200, 0, 0);
    text("GAME OVER, TRY AGAIN", width/2, height/2);
    noLoop();
  }
}

//no other functions are required! (e.g. don't implement mousePressed, keyPressed, etc)
