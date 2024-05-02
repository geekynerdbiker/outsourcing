MyHero hero = new MyHero();

void setup() {
  size(400, 400);
  hero.drawSuperhero((int)random(0, 200), (int)random(0, 200));
}

void draw() {
  
}

void keyPressed() {
  if (key == 's')
    hero.drawSuperhero((int)random(0, 200), (int)random(0, 200));
}
