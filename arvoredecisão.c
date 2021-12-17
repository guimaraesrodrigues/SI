#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int ind1 (double avancas)
{
    int band ;
    double temp;
    temp = avancas;
    if (temp >= 0 && temp < 1)
     band = 1;
    else if (temp >= 1.01 && temp < 2)
     band = 2;
    else
     band = 3;
    return band;
}

int ind2 (double avanlei)
{
    int band ;
    double temp;
    temp = avanlei;
    if (temp >= 0 && temp < 1)
     band = 1;
    else if (temp >= 1.01 && temp < 2)
     band = 2;
    else
     band = 3;
    return band;
}

int ind3 (double avanutisrag)
{
    int band ;
    double temp;
    temp = avanutisrag;
    if (temp >= 0 && temp < 1)
     band = 1;
    else if (temp >= 1.01 && temp < 2)
     band = 2;
    else
     band = 3;
    return band;
}

int ind4 (double avanuti)
{
    int band ;
    double temp;
    temp = avanuti;
    if (temp >= 0 && temp < 1)
     band = 1;
    else if (temp >= 1.01 && temp < 2)
     band = 2;
    else
     band = 3;
    return band;
}

int ind5 (double casospop)
{
    int band ;
    double temp;
    temp = casospop;
    if (temp > 55 )
     band = 1;
    else if (temp >= 28 && temp < 55)
     band = 2;
    else
     band = 3;
    return band;
}

int ind6 (double obitospop)
{
    int band;
    double temp;
    temp = obitospop;
    if (temp >= 0.00 && temp < 1.00)
     band = 1;
    else if (temp >= 1.01 && temp < 2.50)
     band = 2;
    else
     band = 3;
    return band;
}

int ind7 (double capleitos)
{
    int band,temp;
    temp = capleitos;
    if (temp >= 0,00 && temp < 1.00)
     band = 1;
    else if (temp >= 1,01 && temp < 2.50)
     band = 2;
    else
     band = 3;
    return band;
}

int ind8 (int peroc)
{
    int band,temp;
    temp = peroc;
    if (temp < 91 )
     band = 1;
    else if (temp >= 91 && temp <= 95)
     band = 2;
    else
     band = 3;
    return band;
}

int ind9 (int percenf)
{
    int band ,temp;
    temp = percenf;
    if (temp < 91 )
     band = 1;
    else if (temp >= 91 && temp <= 95)
     band = 2;
    else
     band = 3;
    return band;
}

int formfinal(int indic1,int indic2,int indic3,int indic4,int indic5,int indic6,int indic7, int indic8,int indic9)
{
    int band;
    float res;
    res = (((indic1 * 0.375) + (indic2 * 0.375) + (indic3 * 0.375) + (indic4 * 0.375) + (indic5 * 1.75) + (indic6 * 1.75) + (indic7 * 1) + (indic8 * 2) + (indic9 * 2)) / 10);
    if(res < 2)
      band = 1;
    else if(res >=2 && res < 2.1)
      band = 2;
    if(res >= 2.1)
      band = 3;
    return band;
}

int main ()
{
    int num7,num7ant,paciutisrag,paciutiantsrag,paclei,pacleiant,pacuti,pacutiant,casos,obitos,capleitos,capat,caputi,peroc,percenf,bandfin,indic1,indic2,indic3,indic4,indic5,indic6,indic7,indic8,indic9,i;
    float avancas,avanutisrag,avanlei,avanuti,casospop,obitospop;
    char cor_bandeira[9];
    FILE *arq_dados;

    srand(time(NULL));
    arq_dados = fopen("dados_arvore_decisao.","w");
    for(i=0;i < 500;i++)
    {
        num7 = (rand() % 300);
        num7ant = (rand() % 300)+1;
        avancas = (num7 / (num7ant+1));
        paciutisrag = (rand() % 300);
        paciutiantsrag = (rand() % 300);
        avanutisrag = (paciutisrag / (paciutiantsrag+1));
        paclei= (rand() % 300);
        pacleiant = (rand() % 300)+1;
        avanlei = (paclei / (pacleiant+1));
        pacuti = (rand() % 300);
        pacutiant = (rand() % 300)+1;
        avanuti = (pacuti / (pacutiant+1));
        casos = (rand() % 300);
        casospop = (casos / 1948.626) * 100000;
        obitos = (rand() % 300);
        obitospop = (obitos / 1498.626) * 100000;
        caputi = (rand() % 300);
        capleitos = rand () % 300;
        peroc = (rand() % 100) ;
        percenf = (rand() % 100);
        indic1= ind1(avancas);
        indic2= ind2(avanlei);
        indic3= ind3(avanutisrag);
        indic4= ind4(avanuti);
        indic5= ind5(casospop);
        indic6= ind6(obitospop);
        indic7= ind7(capleitos);
        indic8= ind7(peroc);
        indic9= ind8(percenf);
        bandfin = formfinal(indic1,indic2,indic3,indic4,indic5,indic6,indic7,indic8,indic9);
        printf(" %d \n",bandfin);
        fprintf(arq_dados,"%d,%d,%d,%d,%d,%d,%d,%d,%.2f,%.2f,%d, %d,%d,%d \n",num7,num7ant,paciutisrag,paciutiantsrag,paclei,pacleiant,pacuti,pacutiant,casospop,obitospop,capleitos,peroc,percenf,bandfin);

    }
    fclose(arq_dados);
    return 0;
}
