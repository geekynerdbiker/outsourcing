class MyHero {
  int x, y;
  int mx, my;
  
  MyHero() {}
  
  void drawSuperhero(int x, int y) {
    this.x = x;
    this.y = y;
    
    colorMode(RGB, 255, 255, 255);
    background(0,0,0);
    
    drawHead();
    drawArmsLegs();
    drawBody();
    
  }
  
  void drawHead() {
    stroke(255);
    strokeWeight(3);
    fill(255, 255, 255, 100);
    circle(x, y, height * 0.2); 
  }
  
  void drawBody() {
    stroke(255);
    strokeWeight(3);
    fill(0, 0, 0, 100);
    rect(x - width * 0.2, y + height * 0.1, width * 0.4, height * 0.3); 
  }
  
  void drawArmsLegs() {
    stroke(255, 0, 0);
    strokeWeight(3);
    noFill();
    bezier(width * 0.1, height * 0.1, x, y, width - x, height - y, width * 0.9, height * 0.9);
    bezier(width * 0.9, height * 0.1, x, y, width - x, height - y, width * 0.1, height * 0.9);
   }
   
   void onLight() {
    fill(255, mx, my, 100);
    circle(mx, my, width * 0.75);
    fill(255, mx, my, 100);
    circle(width - mx, height - my, width * 0.75);
  
    fill(mx, my, 255, 100);
    circle(width - mx, my, width * 0.75);
    fill(mx, my, 255, 100);
    circle(mx, height -my, width * 0.75);
   }
   
void offLight() {
    fill(255, mx, my, 0);
    circle(mx, my, width * 0.75);
    fill(255, mx, my, 0);
    circle(width - mx, height - my, width * 0.75);
  
    fill(mx, my, 255, 0);
    circle(width - mx, my, width * 0.75);
    fill(mx, my, 255, 0);
    circle(mx, height -my, width * 0.75);
   }
}
