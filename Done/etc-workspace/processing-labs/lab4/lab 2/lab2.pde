// Add your code for this task below
int x, y;

void setup() {
  size(600, 600);
  frameRate(30);
}

void draw() {
  x = mouseX;
  y = mouseY;
  
  background(0, 0, 0);
  
  pushMatrix();

  stroke(0, 0, 255);
  strokeWeight(1);
  fill(0, 0, 255, 50);
  circle(width * 0.6, height * 0.6, 150);
  
  translate(width * 0.6, height * 0.6);
  rotate(PI / 4);
  noFill();
  
  arc(0, 0, width * 0.083, width * 0.5, -PI / 1.18, PI / 1.18);
  arc(0, 0, width * 0.116, width * 0.63, -PI / 1.13, PI / 1.13);
  noCursor();
  
  popMatrix();
  
  pushMatrix();
  translate(x - width * 0.5, y - height * 0.5);
  stroke(255);
  strokeWeight(1);

  colorMode(RGB, 255, 255, 255);
  fill(255, 255, 255, 100);
  
  triangle(width * 0.3, height * 0.2, width * 0.3 + 20, height * 0.3 + 10, width * 0.3 - 20, height * 0.3 + 10);
  fill(0, 200, 150, 100);
  ellipse(width * 0.3, height * 0.28, width * 0.03, width * 0.05);
  
  strokeWeight(8);
  strokeCap(SQUARE);
  line(width * 0.3 + 20, height * 0.3 + 10, width * 0.3 + 20, height * 0.3 - 20);
  line(width * 0.3 - 20, height * 0.3 + 10, width * 0.3 - 20, height * 0.3 - 20);
 
  popMatrix();
}
