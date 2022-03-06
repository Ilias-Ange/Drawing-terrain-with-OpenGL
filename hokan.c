#include <stdio.h>
#define TIME 25 //end-start 分割数　書く点は-1
int main(){
    float la_start=35.7810960;
    float la_end=35.7816250;

    float lon_start=139.0180720;
    float lon_end=139.0213480;
    float alt_start=538.1;
    float alt_end=537.0;
    for (int i=1;i<TIME;i++){
        printf("    %.7f %.7f\n    %.1f\n   %02d %d ",la_start+(la_end-la_start)*i/TIME,lon_start+(lon_end-lon_start)*i/TIME,alt_start+(alt_end-alt_start)*i/TIME,5,42);
        printf("%d\n\n",i+17);
    }
    return 0;

    /*
35.7960010 139.0745240
    406.5
   06 27 14
   
    35.7978470 139.0780050
    387.6
   06 27 53
    */
   /*
   35.7981510 139.0790570
    386.3
   06 39 14
   
    35.7992160 139.0812830
    374.2
   06 39 35*/
   /*
   35.7835140 139.0309520
    541.1
   05 45 36
   
    35.7848200 139.0332060
    540.7
   05 46 01*/

   /*
   35.7810960 139.0180720
    538.1
   05 42 17
   
    35.7816250 139.0213480
    537.0
   05 42 42
   
   */
   
}