class traffic_light {
  float red, yellow, green;
  float coor_x, coor_y;
  
  traffic_light(float x, float y) {
    coor_x = x;
    coor_y = y;
    
    red = 50;
    yellow = 50;
    green = 50;
    
    fill(0,0,0);
    rect(coor_x, coor_y, 200, 300,28);
    
    draw_light(red, yellow, green);
  }
  
  
  void on() {
    this.red = 255;
    this.yellow = 255;
    this.green = 255;
  }
  
  void off() {
    this.red = 50;
    this.yellow = 50;
    this.green = 50;
  }
  
  void draw_light(float r, float y, float g) {
    fill(r,0,0);
    circle(coor_x+100,coor_y+50,80);
   
    fill(y,y,0);
    circle(coor_x+100,coor_y+150,80);
    
    fill(0,g,0);
    circle(coor_x+100,coor_y+250,80);
  }
}
