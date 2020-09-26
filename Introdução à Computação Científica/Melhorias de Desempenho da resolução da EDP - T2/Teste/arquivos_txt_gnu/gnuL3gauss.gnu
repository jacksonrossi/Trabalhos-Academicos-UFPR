set terminal jpeg
set title 'Função gauss testando L3'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE (Escala log)'
set logscale y
set output 'imagemL3gauss.jpeg'
plot 'plotL3gauss.txt' title 'Memory Bandwidth [MBytes/s] T2' with lines, 'plot0L3gauss.txt' title 'Memory Bandwidth [MBytes/s] T1' with lines
