void setup() {
  size(width, height);
}

void draw() {
  background(255);

  float diam = min(width, height) / 2;
  float x = width / 2;
  float y = height / 2;

  line(0, 0, width, height);
  line(width, 0, 0, height);
  
  ellipse(x, y, diam, diam);
  float sSize = diam / 8;
  float sDist = diam / 2 + sSize * 2;
  rect(x - sDist, y - sSize / 2, sSize, sSize);
  rect(x + sDist, y - sSize / 2, sSize, sSize);
}
