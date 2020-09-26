import cv2
import numpy as np
from statistics import mean, mode, median
import argparse, sys

'''Leitura dos Parâmetros
'''
parser = argparse.ArgumentParser()
parser.add_argument('-i', '--imagem', required=True)
parser.add_argument('-p', '--porcentagem', type=float, required=True)
parser.add_argument('-t', '--tecnica', required=True,
                    choices=['media', 'moda', 'mediana'])
parser.add_argument('-q', '--quantizacao', type=int, required=True,
                    choices=[2,4,8,16,32,64,128,256])
args = vars(parser.parse_args())

entrada_nivel = args['quantizacao']
arquivo = args['imagem']
porc = args['porcentagem']
if porc <= 0:
    print('Valor para porcentagem inválido')
    sys.exit(2)
funcoes_est = { 'media': mean, 'moda': mode, 'mediana': median }
tecnica = funcoes_est[args['tecnica']]

'''Quantização
'''
niveis_cinza = {}
acumulador = 0
intervalo = 256 / entrada_nivel

#256/2 resulta em 128, e isso me da 3 níveis de cinza (0, 128, 255).
#Logo decrementando 1, temos os 2 níveis de cinza como queremos
sum_acumulador = 255 / (entrada_nivel - 1)

#Cria um mapeamento das escalas de cinza de acordo com os parâmetros
for cinza in range (256):
    if cinza != 0 and cinza % intervalo == 0:
        acumulador += sum_acumulador
    niveis_cinza[cinza] = acumulador

'''Amostragem
'''
pixels = 1 / porc
imagem = cv2.imread(arquivo, 0)
linha, coluna = imagem.shape[:2]
newlinha = int(linha*porc)
newcoluna = int(coluna*porc)
nova_imagem = np.ndarray(shape = (newlinha, newcoluna), dtype = np.dtype('uint8'))

for i in range (newlinha):
    for j in range (newcoluna):
        oldpixel = []
        for x in range (int(i*pixels), int((i+1)*pixels)):
            for y in range (int(j*pixels), int((j+1)*pixels)):
                oldpixel.append(int(imagem[x][y]))
        if len(oldpixel) == 0:
            oldpixel.append(imagem[int(i*pixels)][int(j*pixels)])

        try:
            t = tecnica(oldpixel)
        except:
            t = median(oldpixel)
        #Quantização
        nova_imagem[i][j] = niveis_cinza[int(t)]

cv2.imwrite('saida.png', nova_imagem)
#cv2.imshow('teste', nova_imagem)
#cv2.waitKey()
