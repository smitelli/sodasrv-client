#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include "probetimer.h"

int main(int argc, char *argv[]) {
    int fd = -1;
    int portflags = 0;
    double timestart = 0;
    double timetotal = 0;

    // Usage tests
    if (argc != 2) {
        printf("Usage: %s /dev/ttys0\n", argv[0]);
        return RETURN_FAILURE;
    }

    // Open the serial port
    fd = open(argv[1], O_RDWR | O_NOCTTY | O_SYNC);
    if (fd == -1) {
        printf("Unable to open %s\n", argv[1]);
        return RETURN_FAILURE;
    }

    // Bring RTS high (prevents trigger), wait a second
    portflags |= TIOCM_RTS;
    ioctl(fd, TIOCMSET, &portflags);
    sleep(1);

    // Bring DTR high (powers probe), wait a second
    portflags |= TIOCM_DTR;
    ioctl(fd, TIOCMSET, &portflags);
    sleep(1);

    // Bring RTS low (triggers), stash the start time
    portflags &= ~TIOCM_RTS;
    ioctl(fd, TIOCMSET, &portflags);
    timestart = microtime();

    // Bring RTS high (resets trigger)
    portflags |= TIOCM_RTS;
    ioctl(fd, TIOCMSET, &portflags);

    // Wait for a response
    while (1) {
        timetotal = microtime() - timestart;
        if (timetotal > TIME_MAXWAIT) break;

        // Did the probe respond? (by pulling DCD low)
        ioctl(fd, TIOCMGET, &portflags);
        if ((portflags & TIOCM_CAR) == 0) break;

        usleep(1);
    }

    close(fd);

    printf("%f\n", timetotal);
    return RETURN_SUCCESS;
}

// Returns seconds since Unix epoch with decimal accuracy
double microtime(void) {
    struct timeval time;

    gettimeofday(&time, NULL);
    return time.tv_sec + (time.tv_usec / (double)1000000);
}
