set terminal jpeg
set title 'Função normaL2 testando L3'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE (Escala log)'
set logscale y
set output 'imagemL3normaL2.jpeg'
plot 'plotL3normaL2.txt' title 'Memory Bandwidth [MBytes/s] T2' with lines, 'plot0L3normaL2.txt' title 'Memory Bandwidth [MBytes/s] T1' with lines
