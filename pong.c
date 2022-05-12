#include <stdio.h>
#include <unistd.h>
#define V 21
#define H 75
#include <termios.h>
#include <fcntl.h>
#include <time.h>

main(){
int X,Y, inijug, finjug, iniia, finia;
int movx, movy, movia;
char campo[V][H];
int i,j;
int level;

srand(time(NULL));

X=37;
Y=rand()%17 +2;

inijug = 8;
finjug = 12;

iniia = 8;
finia = 16;

movx = -1;
movy = -1;

movia = -1;

do{
system("clear");
printf("\nElige el nivel de dificultad:\n\n");
printf("1.- Fácil\n");
printf("2.- Medio\n");
printf("3.- Dicil\n\n");

scanf ("%d", &level);   
       }while (level < 1 || level > 3);

       switch (level){
          case 1:{
                   level=100000;
                   inicio (campo, X, Y, inijug, finjug, iniia, finia);
   loop (campo, X, Y, inijug, finjug, iniia, finia, movx, movy, movia, level);
                   return 0;
                   break;                 
                  }

          case 2:{
                   level=75000;
                   inicio (campo, X, Y, inijug, finjug, iniia, finia);
     loop (campo, X, Y, inijug, finjug, iniia, finia, movx, movy, movia,level);
                   return 0;
                   break;
                  }

          case 3:{
                   level=50000;
                   inicio (campo, X, Y, inijug, finjug, iniia, finia);
     loop (campo, X, Y, inijug, finjug, iniia, finia, movx, movy, movia, level);
                   return 0;
                   break;
                  }
               }
}

inicio (char campo[V][H], int X, int Y, int inijug, int finjug, int iniia, int finia){
borde (campo);
raqjug (campo, inijug, finjug);
raqia (campo, iniia, finia);
pel (campo, X, Y);
}

borde (char campo[V][H]){
int i,j;

  for (i = 0; i < V; i++){
    for (j = 0; j < H; j++){
         if (i == 0 || i == V-1){
              campo[i][j] = '-';
           }
         else if (j == 0 || j == H-1){  
                campo [i][j] = '|';
              } 
         else{
               campo[i][j] = ' ';
             }
     }
   }
}

raqjug (char campo[V][H], int inijug, int finjug){
    int i,j;

    for (i = inijug; i <= finjug; i++){
           for (j = 2; j <= 3; j++){
                 campo[i][j] = 'X';
              }
        } 
}

raqia (char campo[V][H], int iniia, int finia){
   int i,j;

   for (i = iniia; i <= finia; i++){
       for (j = H -4; j <= H - 3; j++){
           campo [i][j] = 'X';
          }
      }
}

pel (char campo[V][H], int X, int Y){
    campo[Y][X] = 'O';
}

impcamp (char campo[V][H]){
    int i, j;

    for (i = 0; i < V; i++){
        for (j = 0; j < H; j++){
            printf ("%c", campo[i][j]);
           }
           printf ("\n");
       }
}

loop (char campo[V][H], int X, int Y, int inijug, int finjug, int iniia, int finia, int movx, int movy, int movia, int level){
      int gol;
      gol = 0;

    do{
        dib (campo);
        pos (campo, &X, &Y, &inijug, &finjug, &iniia, &finia, &movx, &movy, &movia, &gol);
        act (campo, X, Y, inijug, finjug, iniia, finia);
        usleep (level);
      }while(gol == 0);
}

dib (char campo[V][H]){
     system ("clear");
     impcamp (campo);
}

pos (char campo[V][H], int *X, int *Y, int *inijug, int *finjug, int *iniia, int *finia, int *movx, int *movy, int *movia, int *gol){
     int i ;
     char tec;

     if ( *Y == 1 || *Y == V -2){
          *movy *= -1;
        }     
     if ( *X == 1 || *X == H - 2){
          *gol = 1;
        }
     if (*X == 4){
         for (i = (*inijug); i<= (*finjug); i++){
              if (i== (*Y)){
                  *movx *= -1;
                }
            }
        }

     if (*X == 	H - 5){
         for (i = (*iniia); i <= (*finia); i++){
              if (i == (*Y)){
                  *movx *= -1;
                }
            }
       }

     if (*iniia == 1 || *finia == V - 2){
           *movia *= -1;
        }

     if (*gol == 0){

          *X += (*movx);
          *Y += (*movy);

          *iniia += (*movia);
          *finia += (*movia);

        if (kbhit() == 1){
             tec = getchar();//Lo mismo que scanf sin enter 
             
             if (tec == 'w'){
               if (*inijug != 1){
                   *inijug -= 1;
                   *finjug -= 1;
                 }
               } 
             if  (tec == 's'){
                 if (*finjug != V -2){
                    *inijug += 1;
                    *finjug += 1;
                   }
                }
          }
      }
}

act(char campo[V][H], int X, int Y, int inijug, int finjug, int iniia, int finia){
borde (campo);
raqjug (campo, inijug, finjug);
raqia (campo, iniia, finia);
pel (campo, X, Y);
}

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

