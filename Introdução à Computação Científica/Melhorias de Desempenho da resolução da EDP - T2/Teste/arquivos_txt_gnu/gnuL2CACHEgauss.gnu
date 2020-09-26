set terminal jpeg
set title 'Função gauss testando L2CACHE'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE (Escala log)'
set logscale y
set output 'imagemL2CACHEgauss.jpeg'
plot 'plotL2CACHEgauss.txt' title 'Data Cache Miss Ratio T2' with lines, 'plot0L2CACHEgauss.txt' title 'Data Cache Miss Ratio T1' with lines
