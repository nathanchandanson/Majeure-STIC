set terminal pngcairo size 1000,500 enhanced font 'Verdana,10'
set output 'exercice3-cpi.png'

set grid xtics ytics ls 3 lw 1 lc rgb 'gray'

set style line 11 lc rgb "#EA4335" #red
set style line 12 lc rgb "#4285F4" #blue
set style line 13 lc rgb "#FBBC05" #yellow
set style line 14 lc rgb "#34A853" #green

set boxwidth 0.25
set style fill solid

set datafile separator ","

set xtics 1 nomirror ("1" 1, "2" 2, "4" 3, "8" 4)
set ytics nomirror

set xlabel "M"
set ylabel "CPI"

plot 'exercice3-result-cpi.dat' using ($1-0.25):($2) with boxes title "PageRank Min" ls 11,\
     'exercice3-result-cpi.dat' using ($1):($3) with boxes title "PageRank Med" ls 12,\
     'exercice3-result-cpi.dat' using ($1+0.25):($4) with boxes title "PageRank Max" ls 13

reset
set terminal pngcairo size 1000,500 enhanced font 'Verdana,10'
set output 'exercice3-min-cpi.png'

set grid xtics ytics ls 3 lw 1 lc rgb 'gray'

set style line 11 lc rgb "#EA4335" #red
set style line 12 lc rgb "#4285F4" #blue
set style line 13 lc rgb "#FBBC05" #yellow
set style line 14 lc rgb "#34A853" #green

set boxwidth 0.25
set style fill solid

set datafile separator ","

set xtics 1 nomirror ("1" 1, "2" 2, "4" 3, "8" 4)
set ytics nomirror

set xlabel "M"
set ylabel "CPI"

plot 'exercice3-result-cpi.dat' using ($1):($2) with boxes title "PageRank Min" ls 11

reset
set terminal pngcairo size 1000,500 enhanced font 'Verdana,10'
set output 'exercice3-med-cpi.png'

set grid xtics ytics ls 3 lw 1 lc rgb 'gray'

set style line 11 lc rgb "#EA4335" #red
set style line 12 lc rgb "#4285F4" #blue
set style line 13 lc rgb "#FBBC05" #yellow
set style line 14 lc rgb "#34A853" #green

set boxwidth 0.25
set style fill solid

set datafile separator ","

set xtics 1 nomirror ("1" 1, "2" 2, "4" 3, "8" 4)
set ytics nomirror

set xlabel "M"
set ylabel "Kilo Cycles"

plot 'exercice3-result-cpi.dat' using ($1):($3) with boxes title "PageRank Med" ls 12

reset
set terminal pngcairo size 1000,500 enhanced font 'Verdana,10'
set output 'exercice3-max-cpi.png'

set grid xtics ytics ls 3 lw 1 lc rgb 'gray'

set style line 11 lc rgb "#EA4335" #red
set style line 12 lc rgb "#4285F4" #blue
set style line 13 lc rgb "#FBBC05" #yellow
set style line 14 lc rgb "#34A853" #green

set boxwidth 0.25
set style fill solid

set datafile separator ","

set xtics 1 nomirror ("1" 1, "2" 2, "4" 3, "8" 4)
set ytics nomirror

set xlabel "M"
set ylabel "CPI"

plot 'exercice3-result-cpi.dat' using ($1):($4) with boxes title "PageRank Max" ls 13

reset
