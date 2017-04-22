/*Trabalho 1 (simulador de elevador) - ED TURMA E - PROFESSOR: George Teodoro
Codigo feito por: Bruno Fernandes e Leonardo Nunes*/

#include "logica.h"

int main(int argc, char **argv)

{
    //declaracao das variaveis usadas no programa
    tipolista lista, listaacao, listaposterior;
    tipoelevador elevador;
    struct timeval inicio, final;
    float tmili;
    int simulacao = 1, muda_andar = 0;
    int zepslon=0;
    int opt;
    FILE *fp;
    struct rusage uso;
    gettimeofday(&inicio, NULL);
    char *nome=NULL, *andar=NULL, *carga=NULL ;
   
    //uso da funcao getopt para receber argumentos da linha de comando   
    while( (opt = getopt(argc, argv, "n:a:c:")) > 0 ) {
        switch ( opt ) {
            case 'n': /* opção -n */
                nome = optarg ;
                break ;
            case 'a': /* opção -a */
                andar = optarg ;
                break ;
            case 'c': /* opção -c */
                carga = optarg ;
                break ;
            default:
                fprintf(stderr, "Opcao invalida ou faltando argumento: `%c'\n", optopt) ;
                return -1 ;
        }
    }
    getrusage(RUSAGE_SELF, &uso);

    if ((nome == NULL )||(andar == NULL )||(carga == NULL )){
        mostra_ajuda(argv[0]);
        return 0;
    }

    printf("Seus dados: \n\
            Nome : %s\n\
            Andar : %s\n\
            Carga : %s\n", nome, andar, carga) ;
   
    if (entrada(nome, &lista) == 0){
        return 0;
    }
    else{
        //se o arquivo de entrada existir, a simulacao comeca
        fp = fopen("saida.txt", "w+");
        fprintf(fp, "Saida dos dados na ordem de atendimento:\n");
        fclose(fp);
        elevador.cap_max = atoi(carga);
        elevador.andar_max = atoi(andar);
        elevador.andar_atual = 0;
        elevador.cap_atual= 0;
        elevador.direcao = 'n';
        flvazia(&listaacao);
        flvazia(&listaposterior);
        while (simulacao == 1){
            chamada(&lista, &listaacao, &listaposterior, &zepslon, &elevador);
            verifica_andar(&lista, &listaacao, &elevador, &listaposterior, fp, &zepslon);
            verifica_direcao(&elevador, &listaacao, &listaposterior, &lista, &simulacao, &muda_andar);
            if(muda_andar == 0){
                move_elevador(&elevador);
            }
            zepslon++;
            muda_andar = 0;
        }
        desaloca(&lista);
        desaloca(&listaacao);
        desaloca(&listaposterior);
    }

    printf("Memoria usada em Kbytes: %ld\n", uso.ru_maxrss);
    gettimeofday(&final, NULL);
    tmili = (float) (((final.tv_sec * 1000000 + final.tv_usec) - (inicio.tv_sec * 1000000 + inicio.tv_usec))/1000);
    printf("Tempo decorrido: %.2fms\n", tmili);
  
   return 0;
}
