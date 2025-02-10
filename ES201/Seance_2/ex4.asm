; v et k seront stockés dans les registres a0 et a1
; on aura besoin de 3 registres pour stocker des valeurs temporaires : il faut sauvegarder 2 registres ($s0, $s1 et $s2)
; $s0 : v[k]
; $s1 : v[k+1]
; $s2 : adresse de v[k] en mémoire

swap:
; Enregistrement du registre sur la pile
subi $sp, $sp, 12
sw $sp, 0($s0)
sw $sp, 4($s1)
sw $sp, 8($s2)
; Execution du code
; On récupère l'adresse pour arriver à v[k], càd v[0] + 4 * k
add $s2, $a1, $a1       ; $s2 = 2*k
add $s2, $s2, $s2       ; $s2 = 4*k
add $s2, $s2, $a0       ; $s2 = 4*k + v[0]
lw $s0, 0($s2)          ; On stocke v[k] dans $s0 (temp)
lw $s1, 4($s2)          ; On stocke v[k+1] dans $s1
sw $s1, 0($s2)          ; On écrit v[k+1] en mémoire à la place de v[k]
sw $s0, 4($s2)          ; On écrit v[k] en mémoire à la place de v[k+1]
; Dépilement du registre enregistré
lw $s0, 0($sp)
lw $s1, 4($sp)
lw $sp, 8($sp)
addi $sp, $sp, 12
; Retour
jr $ra