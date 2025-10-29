# ft-script

## Description

This project aims to recode the script command, which is used to record terminal
sessions.

The version of reference is the one from [util-linux 2.37.2](https://github.com/util-linux/util-linux/tree/v2.37.2).

## Roadmap

-   [ ] Logging signals on ADVANCED mode
-   [ ] Logging headers on ADVANCED mode
-   [ ] Auto flush on -f
-   [ ] Append to file instead of overwriting it on -a
-   [ ] Return values on -e (and on errors prolly)
-   [ ] Respecting output filesize on -o
-   [x] Logging on -O, -I and -B without multiple file descriptors
-   [x] Lanching with a command on -c
-   [ ] Stop echoing on -E never and resetting termios attributes on exit
-   [x] Signal handling (SIGINT, SIGQUIT, SIGTSTP, SIGUSR1)
-   [ ] Slower auto flush from write ?
