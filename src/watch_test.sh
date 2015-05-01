#!/bin/bash
watch -n 0.1 -c ./ArcadeMain "read_board\ ./tests/filetests/$1/Speelveld.xml\;read_actions\ ./tests/filetests/$1/Acties.xml\;show\;simulate\ 999\;show"
