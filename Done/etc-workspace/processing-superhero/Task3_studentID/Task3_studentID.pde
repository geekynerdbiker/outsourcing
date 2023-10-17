MyHero hero = new MyHero();

void setup() {
  size(400, 400);
  colorMode(RGB, 255, 255, 255);
  background(0,0,0);
  hero.drawSuperhero(200, 100);
}

void draw() {
  if (mouseX >= 300 && mouseY >= 300)
    hero.onLight();
  else {
    hero.offLight();
  }
}

void keyPressed() {
  if (key == 's') {
    hero.drawSuperhero((int)random(0, 200), (int)random(0, 200));
  } else if (key == 't') {
      background(0,0,0);
      delay(1000);
      hero.drawSuperhero(200, 100);
  } 
}

void mousePressed() {
  hero.drawSuperhero((int)mouseX, (int)mouseY);
}
