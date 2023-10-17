float theta;
int second;

void setup() {
  size(width, height);
  frameRate(1);
  theta = 0;
  second = 0;
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
  second++;
  theta = second * (PI / 30) - PI/2;
  
  float r = 40;
  float x = r * cos((theta));
  float y = r * sin((theta));
  line(0, 0, x, y);
}
