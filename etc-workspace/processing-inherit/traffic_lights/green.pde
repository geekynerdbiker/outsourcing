class green_light extends traffic_light {
  green_light(float x, float y) {
    super(x, y);
    green_on();
    draw_light(red, yellow, green);
  }
  
  void green_on() {
    this.green = 255;
  }
  
  void green_off() {
    this.green = 50;
  }
}
