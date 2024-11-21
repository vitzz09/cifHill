#include <stdio.h>
#include <string.h>

#define modulo 26 


int det(int chave[2][2])
{
    return (chave[0][0] * chave[1][1] - chave[0][1] * chave[1][0]) % modulo;
}


int moduloInv(int a, int b)
{
    a = a % b;
    
    for(int x = 1; x < b; x++)
    {
        if ((a * x) % b == 1)
        {
            return x;
        }
    }
    return -1;
}


void encript(int chave[2][2], char *textocif, char *textorig)
{
    int comp = strlen(textorig);

    if(comp % 2 != 0)
    {
        textorig[comp] = 'X';
        textorig[comp + 1] = '\0';
        comp++;
    }

    for(int i = 0; i < comp; i+= 2)
    {
        textocif[i] = ((chave[0][0] * (textorig[i] - 'A') + chave[0][1] * (textorig[i + 1] - 'A')) % modulo) + 'A';
        textocif[i + 1] = ((chave[1][0] * (textorig[i] - 'A') + chave[1][1]  * (textorig[i + 1] - 'A')) % modulo) + 'A';
    }

    textocif[comp] = '\0';
}




void descript(int chave[2][2], char *textocif, char *textorig)
{
    int determinante = det(chave);
    int detinverso = moduloInv(determinante, modulo);
    
    if(detinverso == -1)
    {
        printf("A chave nao possui inversa modular");
        return;
    }

    int chaveInv[2][2] = {
    {(chave[1][1] * detinverso) % modulo, (-chave[0][1] * detinverso) % modulo},
    {(-chave[1][0] * detinverso) % modulo, (chave[0][0] * detinverso % modulo)}
    };

    for (int i = 0; i < 2; i++)
    {
       for (int j = 0; j < 2; j++)
       {
        if(chaveInv[i][j] < 0)
            {
                chaveInv[i][j] += modulo;
            }
       } 
    }

    int comp = strlen(textocif);

    for(int i = 0; i < comp; i+= 2)
    {
        textorig[i] = ((chaveInv[0][0] * (textocif[i] - 'A') + chaveInv[0][1] * (textocif[i + 1] - 'A')) % modulo) + 'A';
        textorig[i + 1] = ((chaveInv[1][0] * (textocif[i] - 'A') + chaveInv[1][1]  * (textocif[i + 1] - 'A')) % modulo) + 'A';
    }

    textocif[comp] = '\0';
}




int main()
{
    int chave[2][2] ={
        {3, -1},
        {-5, 2}
    };

    char textorig[100], textocif[100], textoDesc[100];

    printf("digite o texto a ser codificado: \n");
    scanf("%s", textorig);

    encript(chave, textocif, textorig);
    printf("Texto cifrado: %s \n", textocif);

    descript(chave, textocif, textoDesc);
    printf("Texto decifrado: %s \n", textoDesc);

    return 0;
}



