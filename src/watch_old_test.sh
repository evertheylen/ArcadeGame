#!/bin/bash
watch -n 0.1 -c ./ArcadeMain "read_board\ ./tests/filetests_old/$1/Speelveld.xml\;read_actions\ ./tests/filetests_old/$1/Acties.xml\;show\;a:simulate\;show"
