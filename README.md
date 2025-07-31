📦 Projeto 2 – Compactação de Imagens BMP
Este projeto foi desenvolvido para a disciplina Algoritmos e Programação II na Universidade Presbiteriana Mackenzie.
O objetivo é compactar e descompactar imagens BMP 24 bits (true color) utilizando um método recursivo baseado em quadrantes.

🔹 Funcionalidades
O programa realiza três etapas principais:

1. Leitura da Imagem
Lê uma imagem BMP original (imagemOriginal.bmp).

Armazena os pixels em uma matriz para processamento.

2. Compactação
Divide a imagem recursivamente em 4 quadrantes.

Quando o quadrante é 3x3 ou menor, salva apenas o pixel central como representativo.

Os valores de cada pixel representativo são armazenados em três vetores: vetorR, vetorG, vetorB.

Gera um arquivo compactado imagemCompactada.zmp contendo:

Cabeçalho BMP.

Pixels representativos da imagem.

3. Descompactação
Lê o arquivo .zmp.

Reconstrói a matriz de pixels preenchendo os quadrantes com a cor do pixel central.

Salva a imagem reconstruída como imagemDescompactada.bmp.

Exibe no terminal informações sobre a conclusão do processo.

🔹 Estrutura de Arquivos
bash
Copiar
Editar
├── compactador.c                # Código-fonte principal
├── imagemOriginal.bmp           # Imagem original para compactação
├── imagemCompactada.zmp         # Arquivo gerado após a compactação
└── imagemDescompactada.bmp      # Imagem reconstruída após descompactação

🔹 Lógica da Compactação
A imagem é dividida recursivamente em 4 quadrantes.

Quadrantes de 3x3 ou menores são representados pelo pixel central.

Cada pixel representativo tem seus valores R, G, B armazenados em vetores separados.

Na descompactação, a imagem é reconstruída preenchendo cada quadrante com a cor do seu pixel central.

