set terminal jpeg
set title 'Função normaL2 testando L2CACHE'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE (Escala log)'
set logscale y
set output 'imagemL2CACHEnormaL2.jpeg'
plot 'plotL2CACHEnormaL2.txt' title 'Data Cache Miss Ratio T2' with lines, 'plot0L2CACHEnormaL2.txt' title 'Data Cache Miss Ratio T1' with lines
