class red_light extends traffic_light {
  red_light(float x, float y) {
    super(x, y);
    red_on();
    draw_light(red, yellow, green);
  }
  
  void red_on() {
    this.red = 255;
  }
  
  void red_off() {
    this.red = 50;
  }
}
