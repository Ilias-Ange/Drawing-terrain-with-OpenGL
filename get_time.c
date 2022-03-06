#include <stdio.h>
#define gpx_point_num 7311
int main(){
    float gpx_location[gpx_point_num*3]={0}; //latitude,longtitude,altitude
    int gpx_time[gpx_point_num*3]={0};       //hour,min,sec
    char time[gpx_point_num][9];             //文字列として時間を格納

    FILE* fq = fopen("oku_gpx.txt","r");
    for (int i=0;i<gpx_point_num*6;i++){
        fscanf(fq,"%f %f %f %d %d %d",&gpx_location[3*i],&gpx_location[3*i+1],&gpx_location[3*i+2],&gpx_time[3*i],&gpx_time[3*i+1],&gpx_time[3*i+2]);
    }
    fclose(fq);

    FILE* fr = fopen("gpx_time.txt","w");
    for (int i=0;i<gpx_point_num;i++){
        fprintf(fr,"%02d%c%02d%c%02d ",gpx_time[3*i]+12,':',gpx_time[3*i+1],':',gpx_time[3*i+2]);
    }
    fclose(fr);

    return 0;
}