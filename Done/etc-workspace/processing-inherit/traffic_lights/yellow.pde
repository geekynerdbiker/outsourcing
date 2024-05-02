class yellow_light extends traffic_light {
  yellow_light(float x, float y) {
    super(x, y);
    yellow_on();
    draw_light(red, yellow, green);
  }
  
  void yellow_on() {
    this.yellow = 255;
  }
  
  void yellow_off() {
    this.yellow = 50;
  }
}
