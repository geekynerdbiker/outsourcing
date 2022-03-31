#include <stdio.h>

typedef struct  {
	float radius;
	float center_x;
	float center_y;
} circle;

#define PI 3.14
	

void print(circle c) {
   printf("radius = %f , x of center = %f , y of center = %f\n", c.radius, c.center_x, c.center_x);
}

float area(circle c) {
   return PI*c.radius*c.radius;
}

int equal(circle c1, circle c2) {
   if ( (c1.radius == c2.radius) && (c1.center_x == c2.center_x)  && (c1.center_y == c2.center_y) )
	  return 1;
   else
	  return 0;
}

float compare(circle c1, circle c2) {
   return area(c1) - area(c2);
}
	
void resize(circle *c, float ratio) {
   c->radius *= ratio;
}


int main()
{
	circle c1;
	circle c2 = {2.0, 0.0, 0.0};		   
	circle c3 = {1.0, 1.0, 1.0};

   	if ( equal(c2, c3) )
                printf("two circles are equal. \n");
   	else
                printf("two circles are different. \n");

   	if ( compare(c2, c3) > 0.0 )
                printf("the first is larger than the second. \n");
   	else if ( compare(c2, c3) < 0.0 )
                printf("the first is smaller than the second. \n");
   	else
                printf("two are the same in area. \n");

   	print(c3);
   	resize (&c3, 2.0);
   	print(c3);  
}	






	




