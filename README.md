Sodasrv Client
==============

Compilation is straightforward:

    $ gcc -o probetimer src/probetimer.c

Crontabs look something like this:

    */1  * * * * scripts/cron.sh
    */30 * * * * scripts/alarm.sh

Lotsa stuff is hardcoded in lotsa places. You're smart; you'll figure it out.
