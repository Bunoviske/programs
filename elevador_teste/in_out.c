#include "in_out.h"

void mostra_ajuda(char *name) {
	//mostra o menu de ajuda para iniciar o simulador
    fprintf(stderr, "\
            [uso]%s <opcoes>\n\
            -n Nome do arquivo   Nome do arquivo que descreve a sequência de eventos.\n\
            -a Numero de andares    configura o numero de andares.\n\
            -c Carga maxima do elevador   configura o numero maximo de pessoas no elevador.\n", name) ;
    printf("\n\n             DIGITE OS TRES ARGUMENTOS PARA INICIAR O SIMULADOR\n\n\n");

    exit(-1) ;
}

int entrada (char arq_entrada[], tipolista *lista){
	//funcao que recebe os dados do arquivo texto de entrada e os transfere para uma lista
	//que eh ordenado de forme crescente em relacao ao tempo de chamada
	FILE *fp, *fp1;
	int continua=1;
	fp = fopen(arq_entrada, "r");
	if (fp == NULL){
		printf("Arquivo inexistente\n");
		fclose(fp);
		return 0;
	}
	else {
		flvazia(lista);
		while (continua == 1){
			continua = insere(fp, lista);
	    }
		fclose(fp);
		ordena_tempo(lista);
		return 1;
	}

}

void saida(FILE *fp, apontador aux){
	//imprime a saida de dados do simulador em um arquivo texto
	fp = fopen("saida.txt", "a");
	fprintf(fp, "Andar de chamada: %d Andar de destino: %d Tempo de chamada: %d Tempo de espera: %d Tempo no elevador: %d\n", aux->andar_chamada, aux->andar_destino, aux->tempo_chamada, (aux->tempo_entrada - aux->tempo_chamada),(aux->tempo_saida - aux->tempo_entrada));
	fclose(fp);
}