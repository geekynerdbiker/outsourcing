// Add your code for this task below
int x= -width * 6;
int y= -height * 6;

void setup() {
  size(600, 600);
  frameRate(30);
}

void draw(){
  background(51);
  colorMode(RGB);
  
  rotate(PI);
  
  x+=10; y+=10;
  translate(x, y);

  fill(255, 255, 255, 100);
  ellipse(100, 50, 50, 50);
  
  fill(255, 255, 255, 100);
  rect(75, 85, 50, 70);
  
  translate(random(10),random(10));
  fill(255, 100, 0, 100);
  ellipse(50, 50, 30, 30);
 
  line(72, 85, 35, 45);
  line(130, 90, 150, 135);
  line(88, 165, 65, 200);
  line(113, 165, 125, 200);
  
}
