set terminal jpeg
set title 'Função gauss testando TEMPO em Milisegundos'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE.'
set logscale
set output 'imagemTEMPOgauss.jpeg'
plot 'plotTEMPOgauss.txt' title 'T2' with lines, 'plot0TEMPOgauss.txt' title 'T1' with lines
