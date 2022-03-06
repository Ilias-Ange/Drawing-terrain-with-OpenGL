/*
    地形描画プログラム
    2021.07.16

    数値標高モデル5mメッシュ　https://fgd.gsi.go.jp/download/ref_dem.html
    　奥多摩町 533950 のメッシュ20-27 ... 70-77を描画
*/

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//緯度(y方向)0.05度を1050分割、経度(x方向)0.1度を1800分割
#define latitude_north_max 35.81666667 //77 top
#define latitude_south_min 35.76666667 //20 down 原点
#define longtitude_east_max 139.1      //77 right
#define longitude_west_min 139.0       //20 left 原点
#define gpx_point_num 7335             //GPXデータの点の数
#define velocity_display_frequency 15  //速度・距離・勾配表示の更新頻度
#define place_num 12                   //地名描画点の数
#define Scroll_velocity 15             //sleep(Scroll_vellocity);

int winID[3];
const char *WindowName[3]={"Draw Terrain Program", "Parameters","Route Map"};

int mode;                                            //mode選択 display()内では変数lineを用いて判定
float height[1620000]={0};                           //標高値
float gpx_location[gpx_point_num*3]={0};             //latitude,longtitude,altitude
int gpx_time[gpx_point_num*3]={0};                   //hour,min,sec
float gpx_location_copy[gpx_point_num*3]={0};        //gpx_location[]のコピー
char gpx_time_char[gpx_point_num][9];                //時刻を文字列として格納
float distance_from_start[gpx_point_num];            //i=1000からのデータが有効
float view_x=3000,view_y=2000,view_z=1200,theta=180; //mode0 only,initial viewpoint

int line=1000;                                       //配列走査用
int draw_pattern;                                    //0:網目 1:埋める
double x,y,z;                                        //mode1 only,for viewpoint
float diff_time,distance_between,velocity,distance,gradient;
char buf[7][20];                                     //window parameter出力用

//地名データ
char place_name[place_num][40]={"Oku Village (Highest house in Tokyo)","Mine Village (Abondoned)","Mt.Takanosu"
                               ,"Lake Okutama","R411","Ogouchi dam","Lake Okutama","Tama River"
                               ,"Sakai spring","Okutama Sta.","Convenient store","Nippara River"};
float place_la_lo[place_num][2]={{35.8087153,139.0036281},{35.7983028,138.9918237},{35.8299788,139.0125079},{35.7790865,139.0249420}
                                ,{35.7815459,139.0225156},{35.7897178,139.0508487},{35.7904149,139.0462840},{35.7924391,139.0591904}
                                ,{35.7996679,139.0774660},{35.8093924,139.0967594},{35.8063865,139.0954290},{35.8096414,139.0956933}};
float place_alt[place_num]={937.7,961.3,1733.5,517.0,533.6,523.4,516.9,374.8,385.7,343.0,338.8,309.3};


//xミリ秒待機
int sleep(unsigned long x){
    clock_t c1=clock(),c2;
    do {
        if ((c2=clock())==(clock_t)-1) return (0);
    } while (1000.0 * (c2-c1) /CLOCKS_PER_SEC < x);
    return (1);
}

//地形描画のディスプレイリスト作成
void createdrawlist(){
    glNewList(1,GL_COMPILE_AND_EXECUTE);
    glColor3f(0,1,0);
    if (draw_pattern==1) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);
    for (int i=1;i<900;i++){
        for (int j=1;j<1800;j++){
            float m = height[1800*i+j];
            glColor3f((m<850) ? 0 : (m-850)/550.0 , -(m-500)*(m-1200)/(2*350*350) , (m>850) ? 0 : 1.0-(m-300)/550.0); //地形の色
            glVertex3f(5*j    ,5*i,    height[1800*(i-1)+j]);
            glVertex3f(5*(j+1),5*i,    height[1800*(i-1)+j+1]);
            glVertex3f(5*(j+1),5*(i+1),height[1800*i+1+j]);
            glVertex3f(5*j,    5*(i+1),height[1800*i+j]);
        }
    }
    glEnd();
    glEndList();
}

//GPXをウィンドウ座標に変換
void convert_la_lo_to_world(float t[]){
    for (int i=0;i<gpx_point_num;i++){
        t[3*i]=5+4495.0*(latitude_north_max-t[3*i])/(latitude_north_max-latitude_south_min); //y
        t[3*i+1]=5+8995.0*(t[3*i+1]-longitude_west_min)/(longtitude_east_max-longitude_west_min); //x
    }
}

//地名の緯度経度を変換
void convert_la_lo_to_world_place(float t[][2]){
    for (int i=0;i<place_num;i++){
        t[i][0]=5+4495.0*(latitude_north_max-t[i][0])/(latitude_north_max-latitude_south_min); //y
        t[i][1]=5+8995.0*(t[i][1]-longitude_west_min)/(longtitude_east_max-longitude_west_min); //x
    }
}

//文字列の描画
void drawBitmapString(float x,float y,float z,void *font,char *string){
    glPushAttrib(GL_CURRENT_BIT);
    glRasterPos3f(x,y,z);
    while (*string) glutBitmapCharacter(font, *string++);
    glPopAttrib();
}

//２点間の距離(距離のみ返却)
float just_distance_la_lo(float latitude1, float longitude1, float altitude1,float latitude2, float longitude2, float altitude2){
    float diff_la=latitude1-latitude2;
    float diff_lo=longitude1-longitude2;
    float diff_al=altitude1-altitude2;
    return sqrt(pow(111.955*diff_la , 2.0) + pow(111.111*cos((latitude1+latitude2)/2.0)*diff_lo , 2.0) + pow(pow(10,-3.0)*diff_al , 2.0));
}

//２点間の距離を求める
void distance_la_lo(float latitude1, float longitude1, float altitude1,float latitude2, float longitude2, float altitude2, float* distance_of_two, float* grad){
    float diff_la=latitude1-latitude2;
    float diff_lo=longitude1-longitude2;
    float diff_al=altitude1-altitude2;
    *distance_of_two = sqrt(pow(111.955*diff_la , 2.0) + pow(111.111*cos((latitude1+latitude2)/2.0)*diff_lo , 2.0) + pow(pow(10,-3.0)*diff_al , 2.0));
    *grad = diff_al / (10*sqrt(pow(111.955*diff_la , 2.0) + pow(111.111*cos((latitude1+latitude2)/2.0)*diff_lo , 2.0)));
}

//初期設定1、データ読み込み
void initialize1(){
    glClearColor(0.1,0.1,0.1,1);

    FILE* fp=fopen("whole_data.txt","r");
    for (int i=1;i<=1620000;i++){
        fscanf(fp,"%f ",&height[i]);
    }
    fclose(fp);

    FILE* fq = fopen("oku_gpx.txt","r");
    for (int i=0;i<gpx_point_num*6;i++){
        fscanf(fq,"%f %f %f %d %d %d",&gpx_location[3*i],&gpx_location[3*i+1],&gpx_location[3*i+2],&gpx_time[3*i],&gpx_time[3*i+1],&gpx_time[3*i+2]);
    }
    fclose(fq);
    for (int i=0;i<gpx_point_num*3;i++){
        gpx_location_copy[i]=gpx_location[i];
    }

    FILE* fs = fopen("gpx_time.txt","r");
    for (int i=0;i<gpx_point_num;i++){
        fscanf(fs,"%8s",gpx_time_char[i]);
    }
    fclose(fs);

    for (int i=1001;i<gpx_point_num;i++){
        distance_from_start[i] = distance_from_start[i-1] + just_distance_la_lo(gpx_location[3*i],gpx_location[3*i+1],gpx_location[3*i+2]
                        ,gpx_location[3*i-3],gpx_location[3*i-2],gpx_location[3*i-1]);
    }

    convert_la_lo_to_world(gpx_location);
    convert_la_lo_to_world_place(place_la_lo);

    createdrawlist();
}

//地名(文字)を描画
void draw_place(char t[place_num][40],float u[place_num][2],float v[place_num]){
    for (int i=0;i<place_num;i++){
        glColor3f(1,0.3,0.3);
        glBegin(GL_LINES);
        glVertex3f(u[i][1],u[i][0],v[i]);
        glVertex3f(u[i][1],u[i][0],v[i]+50.0);
        glEnd();
        drawBitmapString(u[i][1],u[i][0],v[i]+50.0,GLUT_BITMAP_TIMES_ROMAN_24,t[i]);
    }
}

//描画1
void display1(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (line==10000){ //mode0
        gluLookAt(view_x,view_y,view_z,view_x+300*sin(theta),view_y+300*cos(theta),900,0,0,1);
    } else {          //mode1
        gluLookAt(x+400*cos(theta),y+400*sin(theta),z+380,x,y,z,0,0,1);
    }

    //地形描画
    glCallList(1);

    //GPX描画
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    for (int i=1000;i<gpx_point_num;i++){
        glVertex3f(gpx_location[3*i+1],gpx_location[3*i],gpx_location[3*i+2]);
    }
    glEnd();

    //地名描画
    draw_place(place_name,place_la_lo,place_alt);

    if (line<gpx_point_num-1){ //以下mode1での処理 (* line<1000は描画していない)
        float tmp=0,tmp2=0;
        glBegin(GL_LINES);
        glColor3f(0.8,0.2,0);
        glVertex3f(gpx_location[3*line+1],gpx_location[3*line],gpx_location[3*line+2]); //現在位置を示す黒い棒
        glVertex3f(gpx_location[3*line+1],gpx_location[3*line],gpx_location[3*line+2]+300);
        glEnd();

        x=gpx_location[3*line+1]; y=gpx_location[3*line]; z=gpx_location[3*line+2]; //mode1視点用 ウィンドウ座標系の値であることに注意
        
        theta+=0.002; //一定速度で視点を回転

        glColor3f(1,1,0);

        if (line % velocity_display_frequency == 0){ //lineの初期値次第で配列外参照
        distance_la_lo(gpx_location_copy[3*line], gpx_location_copy[3*line+1], gpx_location_copy[3*line+2]
                               , gpx_location_copy[3*line-3*velocity_display_frequency], gpx_location_copy[3*line-3*velocity_display_frequency+1]
                               , gpx_location_copy[3*line-3*velocity_display_frequency+2], &distance_between,&gradient); //km単位
        diff_time=3600*(-gpx_time[3*line-3*velocity_display_frequency]+gpx_time[3*line])+60*(-gpx_time[3*line-3*velocity_display_frequency+1]
                        +gpx_time[3*line+1])+(-gpx_time[3*line-3*velocity_display_frequency+2]+gpx_time[3*line+2]);      //s単位
        velocity= 3600 * distance_between / diff_time;
        }

        distance_la_lo(gpx_location_copy[3*line],gpx_location_copy[3*line+1],gpx_location_copy[3*line+2]
                               ,gpx_location_copy[3*line-3],gpx_location_copy[3*line-2],gpx_location_copy[3*line-1],&tmp,&tmp2); //km単位
        distance += tmp;
        
        snprintf(buf[0],20,"%f",gpx_location_copy[3*line]);     //latitude
        snprintf(buf[1],20,"%f",gpx_location_copy[3*line+1]);   //longitude
        snprintf(buf[2],20,"%.1f",gpx_location_copy[3*line+2]); //altitude
        snprintf(buf[3],20,"%8s",gpx_time_char[line]);          //hour,min,sec
        snprintf(buf[4],20,"%.1f",velocity);                    //velocity
        snprintf(buf[5],20,"%.2f",distance);                    //total_distance
        snprintf(buf[6],20,"%.1f",gradient);                    //gradient

        line++;
        sleep(Scroll_velocity);
    } else if (line==gpx_point_num-1) { //loop
        line=1000;
        distance=0;
    } else {
        //mode0視点座標の位置表示:未実装
    }
    
    glutSwapBuffers();
}

void keyboard1(unsigned char c,int x,int y){
    switch (c) {
        case 27 : exit(0); break;
        case 'w' : view_x+=15; break;
        case 'a' : view_y+=15; break;
        case 's' : view_x-=15; break;
        case 'd' : view_y-=15; break;
        case 'q' : view_x+=21; view_y+=21; break;
        case 'e' : view_x-=21; view_y-=21; break;
        case 'r' : theta+=M_PI/180; break;
        case 'f' : theta-=M_PI/180; break;
        case 'z' : view_z+=10; break;
        case 'c' : view_z-=10; break;
    }
}

void reshape1(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45,1,1,1000);
    glMatrixMode(GL_MODELVIEW);
}

//パラメータ描画用ウィンドウ
void display2(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);
    glColor3f(167.0/255.0,31.0/255.0,65.0/255.0);
    glVertex2f(80,80);
    glVertex2f(80,-15);
    glVertex2f(-80,-15);
    glVertex2f(-80,80);
    glEnd();
    
    glBegin(GL_LINES); //y=gradient/10*x
    glColor3f(1,0,0);
    glVertex2f(100,100*gradient/10.0);
    glVertex2f(-100,-100*gradient/10.0);
    glEnd();

    glColor3f(0,0,0);
    drawBitmapString(-90,90,0,GLUT_BITMAP_TIMES_ROMAN_24,"clock");
    drawBitmapString(-66,90,0,GLUT_BITMAP_TIMES_ROMAN_24,buf[3]);
    glColor3f(0,1,0);
    drawBitmapString(-70,70,0,GLUT_BITMAP_TIMES_ROMAN_24,"latitude");
    drawBitmapString(-30,70,0,GLUT_BITMAP_TIMES_ROMAN_24,buf[0]);
    drawBitmapString(-70,60,0,GLUT_BITMAP_TIMES_ROMAN_24,"longitude");
    drawBitmapString(-30,60,0,GLUT_BITMAP_TIMES_ROMAN_24,buf[1]);
    drawBitmapString(-70,50,0,GLUT_BITMAP_TIMES_ROMAN_24,"altitude");
    drawBitmapString(-30,50,0,GLUT_BITMAP_TIMES_ROMAN_24,buf[2]);
    drawBitmapString(-70,20,0,GLUT_BITMAP_TIMES_ROMAN_24,"velocity");
    drawBitmapString(-30,20,0,GLUT_BITMAP_TIMES_ROMAN_24,buf[4]);
    drawBitmapString(-70,5 ,0,GLUT_BITMAP_TIMES_ROMAN_24,"distance");
    drawBitmapString(-30,5 ,0,GLUT_BITMAP_TIMES_ROMAN_24,buf[5]);
    drawBitmapString(-70,-10,0,GLUT_BITMAP_TIMES_ROMAN_24,"gradient");
    drawBitmapString(-30,-10,0,GLUT_BITMAP_TIMES_ROMAN_24,buf[6]);

    //グラフ描画 横200 距離　0-18.5　縦80　標高　970-350
    glBegin(GL_POINTS);
    glColor3f(0,0,0);
    for (int i=1000;i<gpx_point_num-1;i++){
        glVertex2f(200.0*(distance_from_start[i]/18.35)-100.0,-90.0+70.0*(gpx_location_copy[3*i+2]-350.0)/620.0);
    }
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1,0,0);
    for (int i=1000;i<line;i++){
        glVertex2f(200.0*(distance_from_start[i]/18.5)-100.0,-90.0+70.0*(gpx_location_copy[3*i+2]-350.0)/620.0);
        glVertex2f(200.0*(distance_from_start[i]/18.5)-100.0,-100);
    }
    glEnd();

    glutSwapBuffers();
}

void keyboard2(unsigned char c,int x,int y){
    switch (c) {
        case 27 : exit(0); break;
    }
}

void reshape2(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
    glMatrixMode(GL_MODELVIEW);
}

void initialize2(){
    glClearColor(157.0/255.0,157.0/255.0,224.0/255.0,1);
}

void display3(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    for (int i=1000;i<gpx_point_num;i++){
        glVertex2f((gpx_location_copy[3*i]-latitude_south_min)*200/0.05 -100.0,(gpx_location_copy[3*i+1]-longitude_west_min)*400/0.1 -200.0);
        glVertex2f((gpx_location_copy[3*i-3]-latitude_south_min)*200/0.05 -100.0,(gpx_location_copy[3*i-2]-longitude_west_min)*400/0.1 -200.0);
    }

    glColor3f(1,0,0);
    for (int i=1000;i<line;i++){
        glVertex2f((gpx_location_copy[3*i]-latitude_south_min)*200/0.05 -100.0,(gpx_location_copy[3*i+1]-longitude_west_min)*400/0.1 -200.0);
        glVertex2f((gpx_location_copy[3*i-3]-latitude_south_min)*200/0.05 -100.0,(gpx_location_copy[3*i-2]-longitude_west_min)*400/0.1 -200.0);
    }
    glEnd();

    glutSwapBuffers();
}

void keyboard3(unsigned char c,int x,int y){
    switch(c) {
        case 27 : exit(0); break;
    }
}

void reshape3(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-110.0,110.0,-220.0,220.0);
    glMatrixMode(GL_MODELVIEW);
}

void initialize3(){
    glClearColor(0,0,0,1);
}

void animate(){
    if (mode==0){
        for(int loop = 0; loop < 1; ++loop){
		glutSetWindow(winID[loop]);
		glutPostRedisplay(); //再描画 (※display()関数を呼び出す関数 )
	    }
    } else {
        for(int loop = 0; loop < 3; ++loop){ //３ウィンドウ制御
		    glutSetWindow(winID[loop]);
		    glutPostRedisplay(); //再描画 (※display()関数を呼び出す関数 )
	    }
    }
}


int main(int argc,char **argv){
    printf("モードを選択してください：{０...視点操作モード / １...経路追跡モード / ２...地べたモード(工事中)}");
    do {
        scanf("%d",&mode);
    } while (mode<0 || mode>1);
    if (mode==0) line=10000;
    printf("描画パターンを選択してください：{０...塗り潰し / １...網目}");
    do {
        scanf("%d",&draw_pattern);
    } while (draw_pattern<0 || draw_pattern>1);

    glutInit(&argc,argv);
    
//Window1
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(1800,900);
    winID[0]=glutCreateWindow(WindowName[0]);
    glutDisplayFunc(display1);
    glutKeyboardFunc(keyboard1);
    glutReshapeFunc(reshape1);
    initialize1();

//Window2 & Window3
    if (line!=10000){
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowPosition(50,50);
        glutInitWindowSize(500,500);
        winID[1]=glutCreateWindow(WindowName[1]);
        glutDisplayFunc(display2);
        glutKeyboardFunc(keyboard2);
        glutReshapeFunc(reshape2);
        initialize2();

        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInitWindowPosition(575,50);
        glutInitWindowSize(250,500);
        winID[2]=glutCreateWindow(WindowName[2]);
        glutDisplayFunc(display3);
        glutKeyboardFunc(keyboard3);
        glutReshapeFunc(reshape3);
        initialize3();
    }

    glutIdleFunc(animate);

    glutMainLoop();
    return 0;
}
