cscshell: cscshell.c cscsh_readline.c history.c builtin_lib.c environment.c
	gcc cscshell.c cscsh_readline.c history.c builtin_lib.c environment.c -o cscshell -Wall

cscshell_debug: cscshell.c cscsh_readline.c history.c builtin_lib.c environment.c
	gcc cscshell.c cscsh_readline.c history.c builtin_lib.c environment.c -og cscshell_debug
