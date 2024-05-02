float x, y;
traffic_light [] tl;

void setup() {
  size(900, 600);
  x = 100;
  y = 200;
  tl = new traffic_light[3];
  tl[0] = new red_light(x, y);
  tl[1] = new yellow_light(x+250, y);
  tl[2] = new green_light(x+500, y);
}

void draw() {
}
