//JEFV-Hotel-Ativ04
//João Lucas de Lima Souza
//Eduarda Gabriele Bispo da Silva
//Fatima Franzotti Alochio
//Vinícius de Faria Chiesi	

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <locale.h>
#include <windows.h>

//Define o numero total de andares e apartamentos do hotel
#define ANDARES 20
#define APTOS 14

//Define possiveis status dos apartamentos
typedef enum { LIVRE, RESERVADO, OCUPADO } Status;

//Estrutura que armazena os dados dos Hóspedes
typedef struct {
    char cpf[15];
    char nome[100];
    char endereco[200];
    char celular[20];
    char email[100];
} Hospede;

//Representa as condições de um apartamento
typedef struct {
    Status status;
    Hospede hospede;
    int temHospede;
} Apartamento;

Apartamento hotel[ANDARES][APTOS];

//Função para mudar a cor do texto no Windows
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Função que inicializa todos os apartamentos como livres
void inicializarHotel() {
    for (int i = 0; i < ANDARES; i++) {
        for (int j = 0; j < APTOS; j++) {
            hotel[i][j].status = LIVRE;
            hotel[i][j].temHospede = 0;
        }
    }
}

//Função para mostrar o mapa do hotel
void mostrarMapa() {
    system("cls");
	setColor(11);
	printf("Apto -> ");
    for (int j = 0; j < APTOS; j++) printf("%2d ", j+1);
    printf("\n");

    for (int i = ANDARES - 1; i >= 0; i--) {
        printf("Andar %2d ", i+1);
        for (int j = 0; j < APTOS; j++) {
            if (hotel[i][j].status == LIVRE) printf(".  ");
            else if (hotel[i][j].status == RESERVADO) {
                setColor(14); printf("R  "); setColor(11);
            }
            else {
                setColor(12); printf("O  "); setColor(11);
            }
        }
        printf("\n");
    }
    setColor(7);
}

//Função para cadastrar o hospede
void cadastrarHospede(Hospede *h) {
    printf("Nome: "); fflush(stdin); gets(h->nome);
    printf("CPF: "); gets(h->cpf);
    printf("Endereço: "); gets(h->endereco);
    printf("Celular: "); gets(h->celular);
    printf("Email: "); gets(h->email);
	system("cls");
}

//Função para reservar um apartamento
int reservarApto(int andar, int apto) {
    if (hotel[andar][apto].status == LIVRE) {
        cadastrarHospede(&hotel[andar][apto].hospede);
        hotel[andar][apto].status = RESERVADO;
        hotel[andar][apto].temHospede = 1;
		system("cls");
		setColor(10);
		printf("Reserva feita com sucesso!\n");
		setColor(7);
		return 1;
    }
    system("cls");
	setColor(12);
	printf("Apartamento já está reservado ou ocupado!\n");
	setColor(7);
	return 0;
}

//Função para fazer checkin com reserva
//Função para fazer checkin com reserva
int checkinReserva(int andar, int apto) {
    // Verifica se o apartamento está realmente reservado
    if (hotel[andar][apto].status == RESERVADO) {
        
        char cpf_confirmacao[15]; 
                
        //Solicita o CPF para verificação
        printf("Para confirmar a reserva, digite o CPF do hóspede: ");
        fflush(stdin); 
        gets(cpf_confirmacao);

        //Compara o CPF digitado com o da reserva
        if (strcmp(cpf_confirmacao, hotel[andar][apto].hospede.cpf) == 0) {
            hotel[andar][apto].status = OCUPADO;
            system("cls");
            setColor(10);
            printf("Check-in realizado com sucesso!\n");
            setColor(7);
            return 1;
        } else {
            system("cls");
            setColor(12);
            printf("CPF não coincide com o da reserva. Check-in não efetuado.\n");
            setColor(7);
            return 0;
        }
    }
    
    system("cls");
    setColor(12);
    printf("Apartamento não está reservado.\n");
    setColor(7);
    return 0;
}

//Função para fazer checkin sem reserva
int checkinSemReserva(int andar, int apto) {
    if (hotel[andar][apto].status == LIVRE) {
        cadastrarHospede(&hotel[andar][apto].hospede);
        hotel[andar][apto].status = OCUPADO;
        hotel[andar][apto].temHospede = 1;
        system("cls");
		setColor(10);
		printf("Check-in realizado com sucesso!\n");
		setColor(7);
        return 1;
    }
    system("cls");
	setColor(12);
	printf("Apartamento ocupado ou reservado!\n");
	setColor(7);
    return 0;
}

//Função para fazer checkout
int checkout(int andar, int apto) {
    if (hotel[andar][apto].status == OCUPADO) {
        hotel[andar][apto].status = LIVRE;
        hotel[andar][apto].temHospede = 0;
        system("cls");
		setColor(10);
		printf("Check-out realizado.\n");
		setColor(7);
        return 1;
    }
    system("cls");
	setColor(12);
	printf("Apartamento não está ocupado.\n");
	setColor(7);
    return 0;
}

//Função para cancelar uma reserva
int cancelarReserva(int andar, int apto) {
    if (hotel[andar][apto].status == RESERVADO) {
        hotel[andar][apto].status = LIVRE;
        hotel[andar][apto].temHospede = 0;
        system("cls");
		setColor(10);
		printf("Reserva cancelada com sucesso.\n");
		setColor(7);
        return 1;
    }
    system("cls");
	setColor(12);
	printf("Apartamento não está reservado.\n");
	setColor(7);
    return 0;
}

//Função para mostrar as taxas de ocupação do hotel
int taxaOcupacao(){
	int ocupados = 0, reservados = 0, livres = 280;

	for (int i = 0; i < ANDARES; i++){
		for (int j = 0; j < APTOS; j++){
			switch(hotel[i][j].status){
				case 1: reservados++; break;
				case 2: ocupados++; break;
				case 3: livres--; break;
			}
		}
	}

	float taxareservados = (((float) reservados / 280)*100 );
	float taxaocupacao = (((float) ocupados / 280)*100 );
	float taxalivres = (((float) (livres - (ocupados + reservados)) / 280)*100 );

	system("cls");
	setColor(11);
	printf("Total de apartamentos: 280\n");
	printf("Taxa de ocupação = %0.2f %%\n", taxaocupacao);
	printf("Taxa de reservados = %0.2f %%\n", taxareservados);
	printf("Taxa de apartamentos livres = %0.2f %%\n", taxalivres);
	setColor(7);
}

//Função que mostra a situação do apartamento
void mostrarHospede() {
    int andar, apto;

    printf("Digite o andar (1-20): ");
    scanf("%d", &andar);
    printf("Digite o apartamento (1-14): ");
    scanf("%d", &apto);

    andar--; apto--;

    if (andar < 0 || andar >= ANDARES || apto < 0 || apto >= APTOS) {
        setColor(12);
        printf("Andar ou apartamento inválido!\n");
        setColor(7);
        return;
    }

    Apartamento a = hotel[andar][apto];

    system("cls");
    setColor(14);
    printf("Status do apartamento: ");
    switch (a.status) {
        case LIVRE: printf("LIVRE\n"); break;
        case RESERVADO: printf("RESERVADO\n"); break;
        case OCUPADO: printf("OCUPADO\n"); break;
    }
    setColor(7);

    if (a.status == RESERVADO || a.status == OCUPADO) {
        printf("\nInformações do hóspede:\n");
        printf("Nome: %s\n", a.hospede.nome);
        printf("CPF: %s\n", a.hospede.cpf);
        printf("Endereço: %s\n", a.hospede.endereco);
        printf("Celular: %s\n", a.hospede.celular);
        printf("Email: %s\n", a.hospede.email);
    } else {
        printf("Nenhum hóspede neste apartamento.\n");
    }
}

//Função para mostrar o menu do hotel
void menu() {
    int op, andar, apto;

    do {
        setColor(14);
		printf("\n--- Menu Hotel PUC-SP ---\n");
        setColor(7);
        printf("1. Mostrar mapa do hotel\n");
        printf("2. Fazer reserva\n");
        printf("3. Check-in com reserva\n");
        printf("4. Check-in sem reserva\n");
        printf("5. Check-out\n");
        printf("6. Cancelar reserva\n");
        printf("7. Taxas de ocupação e reservas do hotel\n");
        printf("8. Informações do hospede\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if (op >= 2 && op <= 6) {
            printf("Informe o andar (1-20): "); scanf("%d", &andar);
            printf("Informe o apartamento (1-14): "); scanf("%d", &apto);
            andar--; apto--;
            if (andar < 0 || andar >= ANDARES || apto < 0 || apto >= APTOS) {
                system("cls");
				setColor(12);
                printf("Andar ou apartamento inválido!\n");
				setColor(7);
                continue;
            }
        }

		switch (op) {
            case 1: mostrarMapa(); break;
            case 2: reservarApto(andar, apto); break;
            case 3: checkinReserva(andar, apto); break;
            case 4: checkinSemReserva(andar, apto); break;
            case 5: checkout(andar, apto); break;
            case 6: cancelarReserva(andar, apto); break;
            case 7: taxaOcupacao(); break;
            case 8: mostrarHospede(); break;
        }

    } while (op != 0);
}

int main() {
	setlocale(LC_ALL,""); //Altera o idioma para português
	inicializarHotel();	  //inicializa o hotel
    menu();				  //inicializa o menu do hotel
    return 0;
}
