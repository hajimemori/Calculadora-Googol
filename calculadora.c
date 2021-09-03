/*
 Victor Hideki Fujii
 Rafael Hajime Mori
*/
#include <stdio.h>
#include <string.h>

/*Zera os vetores de inteiros pra receber a proxima chamada*/
void zeraVetor(int vetor[], int tamV){
    int i;
    for(i=0; i<tamV; i++){
        vetor[i]=0;
    }
}

/*Cria numerao int ja invertido (para facilitar as operaçoes) a partir de uma
  string*/
int criaNumeraoDeString(char str[], int num[]){
    int i, j=1, tamanho;
    /*Para indicar se o numero é negativo ou positivo, utilizamos o primeiro
      espaço do vetor (v[0]). Caso o numero for negativo v[0]=0 e caso for
      positivo v[0]=1 */
    if(str[0] == '-'){
        num[0] = 0;
        i=1;
        tamanho = strlen(str) - 2;
        j=tamanho;
        for(i; i <= tamanho; i++){
        num[j]=str[i] - '0';
        j--;
       }
    }
    else{
        num[0] = 1;
        i=0;
        tamanho = strlen(str) - 1;

        j=tamanho;
        for(i; i < tamanho; i++){
        num[j]=str[i] - '0';
        j--;
       }
    }
    return tamanho;
}

/*Imprime Numerao*/
void imprimeNumerao(int num[], int tamNum){
    int i;
    /*Para imprimir */
    if(num[0] == 0){
        printf ("-");
    }
    for (i=tamNum; i>=1 ; i--){
        printf ("%d", num[i]);
    }

    printf ("\n");
}

/*Troca o valor de dois inteiros*/
void troca(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/*Troca o valor de dois vetores de inteiros e seus tamanhos*/
void trocaVetor(int A[], int *tamA, int B[], int *tamB){
    int tam, i;
    if(tamA>=tamB){
        tam = *tamA;
    }
    else{
        tam = *tamB;
    }
    for(i=0; i<=tam; i++){
        troca(&A[i], &B[i]);
    }
}

/*SOMA: Para o resultado da soma iremos apenas alterar o vetor A.
  Portanto, caso o vetor B tenha um tamanho maior que A, iremos troca-los*/
int soma (int A[], int tamA, int B[], int tamB){
    int i;

    if(tamA < tamB){
        for(i=1; i<tamB; i++){
            troca(&A[i], &B[i]);
        }
        troca(&tamA, &tamB);
    }

    /*Soma termo a termo*/
    for(i=1; i<tamA+1; i++){
        A[i] += B[i];


        if(A[i]==10){
            A[i] = 0;
            A[i+1] += 1;
        }
        else if(A[i]>10){
            A[i] -= 10;
            A[i+1] += 1;
        }
    }
    if(A[tamA+1]!=0){
        tamA++;
    }
    /*Caso a soma der 0, devemos nos certificar que não há sinal
      de negativo antecedendo-o*/
    if(tamA==1 && A[1]==0){
	    A[0]=1;
    }
    return tamA;
}

/*Subtrai Termo a termo*/
int subAux(int A[], int B[],int j){
    if(A[j]>B[j]){
        return A[j]-B[j];
    }
    else if(A[j]==B[j]){
        return 0;
    }
    else{
        A[j]+=10;
        A[j+1]--;
        return A[j]-B[j];
    }
}

/*SUBTRAI: Para o resultado da subtração iremos apenas alterar o vetor A.
  Portanto, caso o vetor B seja maior que A, iremos troca-los*/
int subtrai (int A[], int tamA, int B[], int tamB){
    int i, aux;

    if(tamA < tamB){
        for(i=1; i<=tamB; i++){
            troca(&A[i], &B[i]);
        }
        troca(&tamA, &tamB);
        if(A[0]==0){
            A[0]=1;
        }
        else{
            A[0]=0;
        }
    }
    /*Caso os tamanhos dos numeros forem iguais, devemos deixar o maior sendo
      A[A]. Tambem há uma preocupação com o jogo de sinal envolvido (caso haja
      um numero negativo maior que o outro positivo, deve-se deixar o sinal
      negativo e etc)*/
    if (tamA == tamB){
        aux = 0;
        for(i=tamA; i>=1; i--){
            if(B[i]>A[i]){
                aux=1;
                break;
            }
            else if(A[i]>B[i]){
                break;
            }
        }
        if(aux==1){
            for(i=1; i<=tamA; i++){
                troca(&A[i], &B[i]);
            }
            if(A[0]==0){
                A[0]=1;
            }
            else{
                A[0]=0;
            }
        }
    }
    for(i=1; i <= tamA; i++){
        A[i] = subAux(A, B, i);
    }
    /*Devolve o tamanho do vetor*/
    while(A[tamA] == 0){
        tamA--;
        if(tamA==0){
            break;
        }
    }
    /*Caso nulo*/
    if(tamA==0){
        A[0]=1;
        tamA=1;
    }
    return tamA;
}

int multiplica_Aux(int A[], int B[], int j, int tamA, int fim){
    int i, numero=0;
    if(j<=tamA){
        i=1;
        while(j>0){
            numero += (A[j] * B[i]);
            j--;
            i++;
        }
        return numero;
    }
    else if(j<fim){
        numero=0;
        i=tamA;
        j=(j%tamA)+1;
        while(j<=tamA){
            numero += A[i] * B[j];
            j++;
            i--;
        }
        return numero;
    }
    else{
        numero = A[j] * B[j];
        return numero;
    }
}

void empresta (int C[], int tam){
    int i;
    for (i=1; i<=tam; i++){
        if(C[i]>=10){
            C[i+1] += C[i]/10;
            C[i] = C[i]%10;
        }
    }
}

/*Descobre qual vetor é maior. Devolvendo:
  1 se A > B; 
  0 se A < B;
  -1 se A=B.          */
int maior (int A[], int tamA, int B[], int tamB){
    int i;
    if(tamA>tamB){
        return 1;
    }
    else if(tamA<tamB){
        return 0;
    }
    for(i=tamA; i>0; i--){
        if(A[i]<B[i]){
            return 0;
        }
        if(A[i]>B[i]){
            return 1;
        }
    }
    /*Ambos sao iguais!!!!*/
    return -1;
}


/* Multiplica 'a' por 'b' e guarda o resultado (a*b) em 'a' e
 * 'b' não é modificado. Devolve o número de dígitos do resultado. */
/*MULTIPLICA*/
int multiplica(int A[], int tamA, int B[], int tamB, int C[]){
    int i, tamC;

    if(tamA==1 && A[1]==0 || tamB==1 && B[1]==0){
        C[1]=0;
        C[0]=1;
        tamA=1;
        return tamA;
    }
    else if (tamA==1 && A[1]==1){
        trocaVetor(C, &tamB, B, &tamB);
        return tamB;
    }
    else if(tamB==1 && B[1]==1){
        trocaVetor(A, &tamA, C, &tamA);
        return tamA;
    }
    if (tamA < tamB){
        trocaVetor(A, &tamA, B, &tamB);
        troca(&tamA, &tamB);
    }
    /*tamanho maximo possivel do numerao C*/
    tamC = tamA + tamB;
    for(i=1; i<tamC; i++){
        C[i] = multiplica_Aux(A, B, i, tamA, tamC);
    }
    empresta (C, tamC);
    /*Analisando o sinal*/

    if(A[0] == B[0]){
        C[0]=1;
    }
    else{
        C[0]=0;
    }

    /*Encontrar o real tamanho de C*/
    for (i=tamC; C[i]==0 ; i--){
        tamC--;
    }
    return tamC;
}

/* Divide 'a' por 'b' e guarda o resultado (a/b) em 'a' e 'b'
 * não é modificado. Devolve o número de dígitos do resultado. */
/*DIVIDE*/
int divide(int A[], int tamA, int B[], int tamB){
    int i, tamC, cont=0;
    int C [1002];
    zeraVetor(C, 1002);
    tamC = tamB;
    while(maior(C,tamC, A,tamA)!=1){
        tamC = soma(C, tamC, B, tamB);
        cont += 1;
    }
    cont--;
    return cont;
}

/* Divide 'a' por 'b' e guarda o resto da divisão (a%b) em 'a'
 * 'b' não é modificado. Devolve o número de dígitos do resultado. */
/*RESTO*/
int resto(int A[], int tamA, int B[], int tamB);

/*_______________________________________________________________________*/

/* MAIN */
int main(){
    int numeraoA [2002];
    int numeraoB [1001];
    char strNumeraoA [2003];
    char strNumeraoB [1003];
    char sinal;
    int n, tamA, tamB;

    while(0==0){
        zeraVetor(numeraoA, 1002);
        zeraVetor(numeraoB, 1001);

        fgets(strNumeraoA, 1003, stdin);

        if(strNumeraoA[0] == 'F'){
            break;
        }

        /*Transforma vetor de string em inteiro e devolve o tamanho do vetor A*/
        tamA = criaNumeraoDeString(strNumeraoA, numeraoA);

        fgets(strNumeraoB, 1003, stdin);
        tamB = criaNumeraoDeString(strNumeraoB, numeraoB);
        /*Recebe o sinal da operação*/
        scanf ("%c", &sinal);

        /*Foi criado condições utilizando o jogo de sinais para facilitar
          as operações (como por exemplo, uma soma de dois numeros com
          sinais diferentes se transormaria em uma subtração e assim por
          diante)*/

        /*SOMA*/
        if(sinal == '+'){
            if(numeraoA[0]==numeraoB[0]){
                tamA = soma (numeraoA,tamA, numeraoB, tamB);
            }
            else{
                tamA = subtrai (numeraoA,tamA, numeraoB, tamB);
            }
            imprimeNumerao (numeraoA, tamA);
        }
        /*SUBTRACAO*/
        else if (sinal == '-'){
            if(numeraoA[0]==numeraoB[0]){
                tamA = subtrai (numeraoA, tamA, numeraoB, tamB);
            }
            else{
                tamA = soma (numeraoA,tamA, numeraoB, tamB);
            }
            imprimeNumerao (numeraoA, tamA);
        }
        /*MULTIPLICACAO*/
        else if (sinal == '*'){
            int numeraoC [2002];
            zeraVetor(numeraoC, 2002);
            tamA = multiplica (numeraoA, tamA, numeraoB, tamB, numeraoC);
            imprimeNumerao (numeraoC, tamA);
        }

        /*DIVISAO*/
        else if (sinal == '/'){
            if(tamA==1 && numeraoA[1]==0){
                numeraoA[0]=1;
                imprimeNumerao (numeraoA, tamA);
            }
            else if(tamB==1 && numeraoB[1]==1){
                    if(numeraoB[0] != numeraoA[0]){
                        numeraoA[0]=0;
                        imprimeNumerao (numeraoA, tamA);
                    }
                    else{
                        numeraoA[0]=1;
                        imprimeNumerao (numeraoA, tamA);
                    }
            }
            else if(tamA<tamB){
                tamA=1;
                numeraoA[0]=1;
                numeraoA[1]=0;
                imprimeNumerao (numeraoA, tamA);
            }
            else if(tamA==tamB){
                int i, status = 0;
                for(i=tamA; i>0; i--){
                    if(numeraoA[i]<numeraoB[i]){
                        status = 1;
                        tamA=1;
                        numeraoA[0]=1;
                        numeraoA[1]=0;
                        imprimeNumerao (numeraoA, tamA);
                        break;
                    }
                    else if(numeraoA[i]>numeraoB[i]){
                        status = 1;
                        tamA = divide(numeraoA, tamA, numeraoB, tamB);
                        numeraoA[1]=tamA;
                        tamA=1;
                        if(numeraoB[0] != numeraoA[0]){
                            numeraoA[0]=0;
                        }
                        else{
                            numeraoA[0]=1;
                        }
                        imprimeNumerao (numeraoA, tamA);
                        break;
                    }
                }
                if(status == 0){
                    tamA = 1;
                    if(numeraoB[0] != numeraoA[0]){
                        numeraoA[0]=0;
                        numeraoA[1]=1;
                        imprimeNumerao (numeraoA, tamA);
                    }
                    else{
                        numeraoA[0]=1;
                        numeraoA[1]=1;
                        imprimeNumerao (numeraoA, tamA);
                    }
                }
            }
            else{
                tamA = divide(numeraoA,tamA, numeraoB, tamB);
                imprimeNumerao (numeraoA, tamA);
            }
        }
 
        fgets(strNumeraoA, 1003, stdin);

    }
    return 0;
}
