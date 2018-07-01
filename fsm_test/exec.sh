#!/bin/bash

gcc fsmlt.c  main.c -I. -o fsmlt -lpthread
sleep 1
./fsmlt