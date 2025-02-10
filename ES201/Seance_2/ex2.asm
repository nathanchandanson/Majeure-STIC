andi $s1, $s1, 0        ; sum = 0
andi $s2, $s2, 0        ; i = 0
; Bloc pas nécessaire au vu de la remise à zéro pour les boucles à chaque incrémentation
/*   andi $s3, $s3, 0  ; j = 0  
addi $s3, $s3, 500  ; j = j + 500 = 500
andi $s4, $s4, 0  ; k = 0                       */
addi $s5, $zero, 1000   ; imax
addi $s7, $zero, 300    ; kmax

Loop1:
andi $s3, $s3, 0        ; On remet j à sa valeur initiale
addi $s3, $s3, 500
Loop2: 
andi $s4, $s4, 0        ; On remet k à sa valeur initiale
Loop3:
add $s1, $s1, $s2       ; sum += i
add $s1, $s1, $s3       ; sum += j
add $s1, $s1, $s4       ; sum += k
addi $s4, $s4, 10       ; k += 10
bne $s4, $s7, Loop3     ; if(k!=kmax) {aller a Loop3}
subi $s3, $s3, 1        ; i--
bne $s3, $zero, Loop2   ; if(j!=0) {aller a Loop2)
addi $s2, $s2, 1        ; i++
bne $s2, $s5, Loop1     ; if(i!=imax) {aller a Loop1}