class MyHero {
  int x, y;
  
  MyHero() {}
  
  void drawSuperhero(int x, int y) {
    this.x = x;
    this.y = y;
    
    colorMode(RGB, 255, 255, 255);
    background(0,0,0);
    
    print(x);
    print(y);
    drawHead();
    drawArmsLegs();
    drawBody();
    
  }
  
  void drawHead() {
    stroke(255);
    strokeWeight(3);
    fill(255, 255, 255, 100);
    circle(width * 0.5 + x * 0.1, height * 0.3 + y * 0.1, height * 0.2); 
  }
  
  void drawBody() {
    stroke(255);
    strokeWeight(3);
    fill(0, 0, 0, 100);
    rect(width * 0.4 + x * 0.1, height * 0.4 + y * 0.1, width * 0.2, height * 0.2); 
  }
  
  void drawArmsLegs() {
    stroke(255, 0, 0);
    strokeWeight(3);
    noFill();
    bezier(width * 0.1, height * 0.1, x, y, width - x, height - y, width * 0.9, height * 0.9);
    bezier(width * 0.9, height * 0.1, x, y, width - x, height - y, width * 0.1, height * 0.9);
   }
}
