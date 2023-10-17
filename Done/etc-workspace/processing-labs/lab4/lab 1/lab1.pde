// Add your code for this task below
int x, y;

void setup() {
  size(width, height);
}

void draw() {
  x = mouseX;
  y = mouseY;

  colorMode(RGB, 255, 255, 255);
  background(0,0,0);
  
  stroke(width * 0.5);
  strokeWeight(3);
  noFill();
  circle(width * 0.5 + x * 0.1, height * 0.3 + y * 0.1, height * 0.2); 
  
  stroke(width * 0.5);
  strokeWeight(3);
  noFill();
  bezier(width * 0.1, height * 0.1, x, y, width - x, height - y, width * 0.9, height * 0.9);
  bezier(width * 0.9, height * 0.1, x, y, width - x, height - y, width * 0.1, height * 0.9);
 
  noStroke();
 
  fill(255, x, y, 100);
  circle(x, y, width * 0.75);
  fill(255, x, y, 100);
  circle(width - x, height -y, width * 0.75);

  fill(x, y, 255, 100);
  circle(width - x, y, width * 0.75);
  fill(x, y, 255, 100);
  circle(x, height -y, width * 0.75);
}
