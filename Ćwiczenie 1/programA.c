#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>

int main () {

    int UID = getuid();
    int GID = getgid();
    int PID = getpid();
    int PPID = getppid();
    int PGID = getpgid(PID);

    printf ("UID %d / GID %d / PID %d / PPID %d / PGID %d\n", UID, GID, PID, PPID, PGID);

}