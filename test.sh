#!/bin/bash
echo --------test.c---------
./mycompiler -f test.c
echo --------000_main.c---------
./mycompiler -f ./functional/000_main.c
echo --------001_var_defn.c---------
./mycompiler -f ./functional/001_var_defn.c
echo --------002_var_defn2.c---------
./mycompiler -f ./functional/002_var_defn2.c
echo -------003_var_defn3.c----------
./mycompiler -f ./functional/003_var_defn3.c
echo -------004_const_var_defn.c----------
./mycompiler -f ./functional/004_const_var_defn.c
echo --------005_const_var_defn2.c---------
./mycompiler -f ./functional/005_const_var_defn2.c
echo --------008_add.c---------
./mycompiler -f ./functional/008_add.c
echo --------009_add2.c---------
./mycompiler -f ./functional/009_add2.c
echo --------010_addc.c---------
./mycompiler -f ./functional/010_addc.c
echo --------011_sub.c---------
./mycompiler -f ./functional/011_sub.c
echo --------012_sub2.c---------
./mycompiler -f ./functional/012_sub2.c
echo --------013_subc.c---------
./mycompiler -f ./functional/013_subc.c
echo --------014_mul.c---------
./mycompiler -f ./functional/014_mul.c
echo ---------015_mulc.c--------
./mycompiler -f ./functional/015_mulc.c
echo ---------016_div.c--------
./mycompiler -f ./functional/016_div.c
echo --------017_divc.c---------
./mycompiler -f ./functional/017_divc.c
echo --------018_rem.c---------
./mycompiler -f ./functional/018_rem.c
echo --------019_mod.c---------
./mycompiler -f ./functional/019_mod.c
echo --------020_arr_defn.c---------
./mycompiler -f ./functional/020_arr_defn.c
echo --------021_arr_expr_len.c---------
./mycompiler -f ./functional/021_arr_expr_len.c
echo -----------------