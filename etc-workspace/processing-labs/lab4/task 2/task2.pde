float theta;

void setup() {
  size(width, height);
  frameRate(1);
  theta = -90;
}

void draw() {
  background(255);
  
  translate(width/2, height/2);
  fill(255, 255, 255);
  ellipse(0, 0, width, height);
  
  fill(0, 0, 0);
  textSize(13);
  textAlign(CENTER, CENTER);
  for (int i = 1; i <= 12; i++) {
    float ang = radians(30 * (i+9));
    float x = 40 * cos(ang);
    float y = 40 * sin(ang);
    text(str(i), x, y);
  }
  
  float r = 40;
  float x = r * cos(radians(theta));
  float y = r * sin(radians(theta));
  line(0, 0, x, y);
  
  theta = theta + 6;
}
