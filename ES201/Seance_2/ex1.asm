; Naivement : 

andi $t0, $t0, 0 
beq $s5, $t0, Case0 
addi $t0, $t0, 1 
beq $s5, $t0, Case1 
addi $t0, $t0, 1 
beq $s5, $t0, Case2
addi $t0, $t0, 1
beq $s5, $t0, Case3
j End
Case0: 
add $s0, $s3, $s4
j End
Case1: 
add $s0, $s1, $s2
j End
Case2: 
sub $s0, $s1, $s2
j End
Case3:
sub $s0, $s3, $s4
End:
; ...



; Faire la méthode optimisée : regarder correction
; utiliser le fait que dans chaque case il y a 2 instructions : on peut sauter avant les case de Case0 + k * offset
; ; Vérif que k entre 0 et 3

; ; Calcul de l'offset 
; addi $t0, $zero, 8      ; $t0 = offset ; On calcule l'offset entre 2 cases : 8 car 2 instructions de 32 bits
; multu $s5, $t0          ; On multiplie l'offset par k
; mflo $t0                ; $t0 = k * offset
; addi $t0, $t0, Case0    ; $t0 = Case0 + k * offset = l'endroit où sauter ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Ne marche pas : pas le droit de mettre Case0 comme ça
; Case0: 
; add $s0, $s3, $s4
; j End
; ; Case1 pas nécessaire car on saute direct à cet endroit si besoin
; add $s0, $s1, $s2
; j End
; ; Case2: 
; sub $s0, $s1, $s2
; j End
; ; Case3:
; sub $s0, $s3, $s4
; End:
; ; ...