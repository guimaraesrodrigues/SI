#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double randf(double min,double max)
{
    return min + (rand()/ (RAND_MAX / (max-min)));
}

int main ()
{
    double min,max;
    float dens, curves, incl;
    int i,clima,score;
    FILE *redeneural_dados;
    srand(time(NULL));


    redeneural_dados = fopen("redeneuraldados.txt","w");
    for(i=0;i<91;i++)
    {
        score = rand()%4;
        dens = randf(0,1);
        curves = randf(0,1);
        incl = randf(0,1);
        clima = rand() % 4;
        if((dens >=0 && dens < 0.5) && (curves < 0.4) || (incl >= 0 && incl < 0.4) && (clima < 1))
        {
           score = score;
        }
        else if ((dens >=0.5 && dens < 0.8) && (curves > 0.4 && curves < 0.7) || (incl >= 0.4 && incl < 0.7) && (clima <= 2))
        {
          score = score + 4;
        }
        else if ((dens >=0.8 ) && (curves > 0.7) || (incl >= 0.7) && (clima < 4))
        {
          score = score + 8;
        }
        if(score > 10)
            score  -= 10;
        fprintf(redeneural_dados,"%.3f,%.3f,%.3f,%d,%d \n",dens,curves,incl,clima,score);
        printf("%.2f, %.2f , %.2f, %d, %d \n",dens,curves,incl,clima,score);
    }
    fclose(redeneural_dados);
    return 0;
}
