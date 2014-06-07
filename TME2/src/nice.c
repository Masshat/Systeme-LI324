#include <stdio.h>
#include <stdlib.h>

/* ==================================================
   Simple boucle effectuant 10 puissance 8 iterations
   ==================================================
*/
int main()
{
  int a,b,c,d,e,f,g,h;

  for (a=0;a < 10; a++)
    for (b=0;b < 10; b++)
      for (c=0;c < 10; c++)
	for (d=0;d < 10; d++)
	  for (e=0;e < 10; e++)
	    for (f=0;f < 10; f++)
	      for (g=0;g < 10; g++)
		for (h=0;h < 10; h++){}
	        
  return EXIT_SUCCESS;
}
