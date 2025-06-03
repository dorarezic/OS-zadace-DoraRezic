#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define OBRADA_DAT "obrada.txt"
#define STATUS_DAT "status.txt"

int trenutni_broj = 1;

void handle_sigusr1(int sig) {
    char buffer[100];
    int len = snprintf(buffer, sizeof(buffer), "Trenutni broj u obradi: %d\n", trenutni_broj);
    write(STDOUT_FILENO, buffer, len);  // sig-safe ispis
}

void handle_sigterm(int sig) {
    FILE *status_file = fopen(STATUS_DAT, "w");
    if (status_file == NULL) {
        perror("Otvaranje status.txt");
        exit(1);
    }
    fprintf(status_file, "%d\n", trenutni_broj - 1);
    fclose(status_file);

    char buffer[100];
    int len = snprintf(buffer, sizeof(buffer), "Program zavrsava, zadnji broj: %d\n", trenutni_broj - 1);
    write(STDOUT_FILENO, buffer, len);
    exit(0);
}

void handle_sigint(int sig) {
    const char *msg = "Program prekinut (SIGINT), status ostaje 0.\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    exit(0);
}

int zadnji_broj_obrada() {
    FILE *obrada_file = fopen(OBRADA_DAT, "r");
    if (obrada_file == NULL) {
        return 0;
    }
    int zadnji = 0;
    int broj;
    while (fscanf(obrada_file, "%d", &broj) != EOF) {
        zadnji = broj;
    }
    fclose(obrada_file);
    return zadnji;
}

int main() {
    // Isključi buffering na stdout
    setvbuf(stdout, NULL, _IONBF, 0);

    // Poveži signale
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGTERM, handle_sigterm);
    signal(SIGINT, handle_sigint);

    printf("Prvi zadatak startovao\n");
    printf("PID programa: %d\n", getpid());

    int status = 0;
    FILE *status_file = fopen(STATUS_DAT, "r");
    if (status_file != NULL) {
        fscanf(status_file, "%d", &status);
        fclose(status_file);
    }

    int zadnji = zadnji_broj_obrada();

    if (status > 0) {
        if (zadnji == status * status) {
            trenutni_broj = status + 1;
        } else {
            trenutni_broj = status;
        }
    } else {
        trenutni_broj = (int)sqrt(zadnji) + 1;
    }

    status_file = fopen(STATUS_DAT, "w");
    if (status_file == NULL) {
        perror("Otvaranje status.txt");
        return 1;
    }
    fprintf(status_file, "0\n");
    fclose(status_file);

    while (1) {
        FILE *obrada_file = fopen(OBRADA_DAT, "a");
        if (obrada_file == NULL) {
            perror("Otvaranje obrada.txt");
            return 1;
        }

        int kvadrat = trenutni_broj * trenutni_broj;
        fprintf(obrada_file, "%d\n", kvadrat);
        fclose(obrada_file);

        printf("Kvadrat broja %d (%d) upisan u obrada.txt\n", trenutni_broj, kvadrat);

        trenutni_broj++;
        sleep(5);
    }

    return 0;
}
