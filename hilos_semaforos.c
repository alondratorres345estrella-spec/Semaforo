#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaforo;

void* contar(void* arg) {
    int id_hilo = *((int*)arg);

    for (int i = 1; i <= 10000; i++) {
        if (i == 4000) {
            sem_wait(&semaforo);
            printf("\n>>> Hilo %d ENTRA a la seccion critica (4000 - 6000) <<<\n", id_hilo);
        }

        printf("Hilo %d: %d\n", id_hilo, i);

        if (i == 6000) {
            printf(">>> Hilo %d SALE de la seccion critica <<<\n\n", id_hilo);
            sem_post(&semaforo);
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilo1, hilo2;
    int id1 = 1, id2 = 2;

    if (sem_init(&semaforo, 0, 1) != 0) {
        perror("Error al inicializar el semaforo");
        return 1;
    }

    pthread_create(&hilo1, NULL, contar, &id1);
    pthread_create(&hilo2, NULL, contar, &id2);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    sem_destroy(&semaforo);
    printf("Ejecucion finalizada correctamente.\n");
    return 0;
}
