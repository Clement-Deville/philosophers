/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:46:08 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/24 16:51:57 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

sem_t *sem;

void child_process() {
    // Open the semaphore created by the parent process
    sem = sem_open("/mysem", 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("Child process waiting for semaphore...\n");
    sem_wait(sem);
    printf("Child process got the semaphore!\n");
    // Perform some work
    sleep(2); // Simulating work
    printf("Child process completed work\n");

    // Close semaphore
    sem_close(sem);
}

int main() {
    // Create a semaphore with an initial value of 0
    sem = sem_open("/mysem", O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
	sem_wait(sem);
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        child_process();
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process doing some work...\n");
        sleep(3); // Simulating work
        printf("Parent process signaling semaphore...\n");
        sem_post(sem);
        wait(NULL); // Wait for child process to finish

        // Clean up semaphore
        sem_close(sem);
        sem_unlink("/mysem");
    }

    return 0;
}

