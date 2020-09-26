set terminal jpeg
set title 'Função normaL2 testando FLOPS_DP'
set key above
set xlabel 'TAMANHO'
set ylabel 'INDICADOR DO TESTE (Escala log)'
set logscale y
set output 'imagemFLOPS_DPnormaL2.jpeg'
plot 'plotFLOPS_DPnormaL2.txt' title 'FLOPS DP T2' with lines, 'plotAVXFLOPS_DPnormaL2.txt' title 'AVX FLOPS DP T1' with lines, 'plot0FLOPS_DPnormaL2.txt' title 'FLOPS DP T1' with lines, 'plot0AVXFLOPS_DPnormaL2.txt' title 'AVX FLOPS DP T1' with lines
