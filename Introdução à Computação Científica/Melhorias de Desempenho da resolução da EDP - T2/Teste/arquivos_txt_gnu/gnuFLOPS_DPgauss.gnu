set terminal jpeg
set title 'Função gauss testando FLOPS_DP'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE (Escala log)'
set logscale y
set output 'imagemFLOPS_DPgauss.jpeg'
plot 'plotFLOPS_DPgauss.txt' title 'FLOPS DP T2' with lines, 'plotAVXFLOPS_DPgauss.txt' title 'AVX FLOPS DP T1' with lines, 'plot0FLOPS_DPgauss.txt' title 'FLOPS DP T1' with lines, 'plot0AVXFLOPS_DPgauss.txt' title 'AVX FLOPS DP T1' with lines
