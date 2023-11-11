#!/bin/sh
valgrind --leak-check=full --show-leak-kinds=all bin/debug &> .valgrindlog.txt
