# ft-script

## Description

This project aims to recode the script command, which is used to record terminal
sessions.

The version of reference is the one from [util-linux 2.37.2](https://github.com/util-linux/util-linux/tree/v2.37.2).

## Roadmap

-   [x] Logging signals on ADVANCED mode
-   [ ] Logging useless stuff that the reference logs (initial terminal settings, etc.)
    -   [x] Begin log in in/out files
    -   [x] End log in in/out files
    -   [ ] Begin log in timing file
    -   [ ] End log in timing file
-   [x] Auto flush on -f
-   [x] Append to file instead of overwriting it on -a
-   [x] Return values on -e
-   [x] Respecting output filesize on -o
-   [x] Logging on -O, -I and -B without multiple file descriptors
-   [x] Lanching with a command on -c
-   [x] Stop echoing on -E never and resetting termios attributes on exit
-   [x] Signal handling (SIGINT, SIGQUIT, SIGTSTP, SIGUSR1)
-   [-] Slower auto flush from write ?

## Known bugs

-   [ ] Weird behavior when input is a closed pipe ? (`make echo | ./ft_script`, when echo is not a valid make target)
