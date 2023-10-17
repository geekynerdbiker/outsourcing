void setup() {
  size(400, 400);
}

void draw() {
  drawHead();
  drawArmsLegs();
  drawBody();
}

void drawHead() {
  stroke(255);
  strokeWeight(3);
  fill(255, 255, 255, 100);
  circle(width * 0.5 , height * 0.3, height * 0.2); 
}

void drawBody() {
  stroke(255);
  strokeWeight(3);
  fill(0, 0, 0, 100);
  rect(width * 0.4, height * 0.4, width * 0.2, height * 0.2); 
}

void drawArmsLegs() {
  stroke(255, 0, 0);
  strokeWeight(3);
  noFill();
  bezier(width * 0.1, height * 0.1, 0, 0, width, height, width * 0.9, height * 0.9);
  bezier(width * 0.9, height * 0.1, 0, 0, width, height, width * 0.1, height * 0.9);
 }
