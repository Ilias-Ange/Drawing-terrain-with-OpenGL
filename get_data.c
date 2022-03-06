#include <stdio.h>
#include <stdlib.h>
#define N 48 //読み込むファイル数
#define A 33750 //225*150


int main(){
    float **w;
    w=calloc(900,sizeof(float *));
    for (int i=0;i<900;i++){
        w[i]=calloc(1800,sizeof(float));
    }

    float **a;
    a=calloc(N,sizeof(float *));
    for (int i=0;i<N;i++){
        a[i]=calloc(33750,sizeof(float));
    }

    FILE* f70=fopen("50-70.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f70,"%f ",&a[0][i]);
    }
    fclose(f70);
    FILE* f71=fopen("50-71.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f71,"%f ",&a[1][i]);
    }
    fclose(f71);
    FILE* f72=fopen("50-72.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f72,"%f ",&a[2][i]);
    }
    fclose(f72);
    FILE* f73=fopen("50-73.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f73,"%f ",&a[3][i]);
    }
    fclose(f73);
    FILE* f74=fopen("50-74.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f74,"%f ",&a[4][i]);
    }
    fclose(f74);
    FILE* f75=fopen("50-75.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f75,"%f ",&a[5][i]);
    }
    fclose(f75);
    FILE* f76=fopen("50-76.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f76,"%f ",&a[6][i]);
    }
    fclose(f76); //57
    FILE* f77=fopen("50-77.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f77,"%f ",&a[7][i]);
    }
    fclose(f77);

    FILE* f60=fopen("50-60.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f60,"%f ",&a[8][i]);
    }
    fclose(f60);
    FILE* f61=fopen("50-61.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f61,"%f ",&a[9][i]);
    }
    fclose(f61);
    FILE* f62=fopen("50-62.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f62,"%f ",&a[10][i]);
    }
    fclose(f62);
    FILE* f63=fopen("50-63.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f63,"%f ",&a[11][i]);
    }
    fclose(f63);
    FILE* f64=fopen("50-64.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f64,"%f ",&a[12][i]);
    }
    fclose(f64);
    FILE* f65=fopen("50-65.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f65,"%f ",&a[13][i]);
    }
    fclose(f65);
    FILE* f66=fopen("50-66.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f66,"%f ",&a[14][i]);
    }
    fclose(f66); //57
    FILE* f67=fopen("50-67.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f67,"%f ",&a[15][i]);
    }
    fclose(f67);

    FILE* f1=fopen("50-50.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f1,"%f ",&a[16][i]);
    }
    fclose(f1);
    FILE* f2=fopen("50-51.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f2,"%f ",&a[17][i]);
    }
    fclose(f2);
    FILE* f3=fopen("50-52.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f3,"%f ",&a[18][i]);
    }
    fclose(f3);
    FILE* f4=fopen("50-53.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f4,"%f ",&a[19][i]);
    }
    fclose(f4);
    FILE* f5=fopen("50-54.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f5,"%f ",&a[20][i]);
    }
    fclose(f5);
    FILE* f6=fopen("50-55.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f6,"%f ",&a[21][i]);
    }
    fclose(f6);
    FILE* f7=fopen("50-56.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f7,"%f ",&a[22][i]);
    }
    fclose(f7); //57
    FILE* f8=fopen("50-57.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f8,"%f ",&a[23][i]);
    }
    fclose(f8);
    
    FILE* f40=fopen("50-40.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f40,"%f ",&a[24][i]);
    }
    fclose(f40);
    FILE* f41=fopen("50-41.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f41,"%f ",&a[25][i]);
    }
    fclose(f41);
    FILE* f42=fopen("50-42.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f42,"%f ",&a[26][i]);
    }
    fclose(f42);
    FILE* f43=fopen("50-43.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f43,"%f ",&a[27][i]);
    }
    fclose(f43);
    FILE* f44=fopen("50-44.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f44,"%f ",&a[28][i]);
    }
    fclose(f44);
    FILE* f45=fopen("50-45.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f45,"%f ",&a[29][i]);
    }
    fclose(f45);
    FILE* f46=fopen("50-46.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f46,"%f ",&a[30][i]);
    }
    fclose(f46);
    FILE* f47=fopen("50-47.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f47,"%f ",&a[31][i]);
    }
    fclose(f47);

    FILE* f30=fopen("50-30.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f30,"%f ",&a[32][i]);
    }
    fclose(f30);
    FILE* f31=fopen("50-31.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f31,"%f ",&a[33][i]);
    }
    fclose(f31);
    FILE* f32=fopen("50-32.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f32,"%f ",&a[34][i]);
    }
    fclose(f32);
    FILE* f33=fopen("50-33.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f33,"%f ",&a[35][i]);
    }
    fclose(f33);
    FILE* f34=fopen("50-34.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f34,"%f ",&a[36][i]);
    }
    fclose(f34);
    FILE* f35=fopen("50-35.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f35,"%f ",&a[37][i]);
    }
    fclose(f35);
    FILE* f36=fopen("50-36.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f36,"%f ",&a[38][i]);
    }
    fclose(f36); //57
    FILE* f37=fopen("50-37.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f37,"%f ",&a[39][i]);
    }
    fclose(f37);

    FILE* f20=fopen("50-20.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f20,"%f ",&a[40][i]);
    }
    fclose(f20);
    FILE* f21=fopen("50-21.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f21,"%f ",&a[41][i]);
    }
    fclose(f21);
    FILE* f22=fopen("50-22.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f22,"%f ",&a[42][i]);
    }
    fclose(f22);
    FILE* f23=fopen("50-23.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f23,"%f ",&a[43][i]);
    }
    fclose(f23);
    FILE* f24=fopen("50-24.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f24,"%f ",&a[44][i]);
    }
    fclose(f24);
    FILE* f25=fopen("50-25.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f25,"%f ",&a[45][i]);
    }
    fclose(f25);
    FILE* f26=fopen("50-26.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f26,"%f ",&a[46][i]);
    }
    fclose(f26); //57
    FILE* f27=fopen("50-27.txt","r");
    for (int i=0;i<A;i++){
        fscanf(f27,"%f ",&a[47][i]);
    }
    fclose(f27);

    for (int row=0;row<6;row++){ //rowを変更すれば良い
        for (int b=150*row;b<150*(row+1);b++){
            for (int d=8*row;d<8*(row+1);d++){
                for (int c=0;c<225;c++){
                    w[b][225*(d-8*row)+c]=a[d][225*(b-150*row)+c];
                }
            }
        }
    }
    FILE* ff=fopen("whole_data.txt","w");
    for (int b=0;b<900;b++){
        for (int c=0;c<1800;c++){
            fprintf(ff,"%.2f ",w[b][c]);
        }
    }

    return 0;
}