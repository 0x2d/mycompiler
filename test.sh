#!/bin/bash
echo -----------------
./mycompiler -f test.c
echo -----------------
./mycompiler -f ./functional/000_main.c
echo -----------------
./mycompiler -f ./functional/001_var_defn.c
echo -----------------
./mycompiler -f ./functional/002_var_defn2.c
echo -----------------
./mycompiler -f ./functional/003_var_defn3.c
echo -----------------
./mycompiler -f ./functional/004_const_var_defn.c
echo -----------------
./mycompiler -f ./functional/005_const_var_defn2.c
echo -----------------