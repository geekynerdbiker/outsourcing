// Add your code for this task below
int radius = 255;
int opacity = 0;
int x = 300;

int rgb = 0;

void setup() {
  size(700, 200);
  background(0);
}

void draw() {

  noStroke();

  while (radius > 0) {
    fill(0, 0, 255, opacity++);
    circle(100+35, 100, radius);
    radius -= 10;
  }
  
  while (x < 300 + 360) {
    colorMode(HSB, 360, 100, 100);
    stroke(rgb++, 100, 100);
    line(x, 40, x++, 160);
  }
}
