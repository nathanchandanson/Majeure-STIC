; Par exemple, dans notre fonction, on va faire res1 = g+h; res2 = i+j; f = res1-res2; On va donc avoir besoin de 3 registres : il faudra les enregistrer dans la pile pour être sûr de ne pas les perdre
; On choisit de prendre $s0, $s1 et $s2

leaf: 
; Stockage des registres utilisés dans la pile 
subi $sp, $sp, 12       ; On update le stack pointer pour tenir compte des registres qu'on va sauvegarder
sw $s0, 0($sp)          ; Save $s0
sw $s1, 4($sp)          ; Save $s1
sw $s2, 8($sp)          ; Save $s2
; Faire les opérations dans la fonction
add $s1, $a0, $a1       ; res1 = g+h
add $s2, $a2, $a3       ; res2 = i+j
sub $s0, $s1, $s2       ; f = res1-res2
; Mettre le résultat dans le registre de retour
add $v0, $s0, $zero
; Recharger les données enregistrées dans la pile et update le pointeur de pile
lw $s0, 0($sp)          ; Retrieve stored $s0
lw $s1, 4($sp)          ; Retrieve stored $s1
lw $s2, 8($sp)          ; Retrieve stored $s2
addi $sp, $sp, 12       ; Update the sp 
; Retourner au code 
jr $ra&



; Q1 : Les appels de fonctions affectent les performances car il est nécessaire de sauvegarder/récupérer des registres en mémoire, ce qui est couteux en performances
; Q2 : Car les lw et sw sont appelés à chaque itération, ce qui fait augmenter exponentiellement le nombre de registres enregistrés