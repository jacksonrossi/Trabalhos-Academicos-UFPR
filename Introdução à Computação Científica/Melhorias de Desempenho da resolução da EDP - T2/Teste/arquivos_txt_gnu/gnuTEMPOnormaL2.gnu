set terminal jpeg
set title 'Função normaL2 testando TEMPO em Milisegundos'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE.'
set logscale
set output 'imagemTEMPOnormaL2.jpeg'
plot 'plotTEMPOnormaL2.txt' title 'T2' with lines, 'plot0TEMPOnormaL2.txt' title 'T1' with lines
