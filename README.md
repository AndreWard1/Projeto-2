#📦 Projeto 2 – Compactação de Imagens BMP
Este projeto foi desenvolvido para a disciplina Algoritmos e Programação II na Universidade Presbiteriana Mackenzie.
O objetivo é compactar e descompactar imagens BMP 24 bits (true color) usando um método recursivo baseado em quadrantes.

🔹 O que o programa faz:
-Lê uma imagem BMP original (imagemOriginal.bmp) e guarda seus pixels em uma matriz.

-Compacta a imagem:

-Divide recursivamente em 4 quadrantes.

-Quando o quadrante é menor ou igual a 3x3, salva o pixel central como representante.

-Salva os valores R, G, B em vetores.

-Gera um arquivo compactado (imagemCompactada.zmp) com:

-Cabeçalho BMP

-Pixels representativos da imagem

Descompacta a imagem:

-Lê o arquivo .zmp

-Reconstrói a matriz de pixels preenchendo os quadrantes com seus pixels centrais

-Salva a imagem reconstruída como imagemDescompactada.bmp

-Exibe no terminal informações de conclusão de compactação e descompactação.

🔹 Estrutura de arquivos:
-compactador.c → Código-fonte do projeto.

-imagemOriginal.bmp → Imagem que será compactada.

-imagemCompactada.zmp → Arquivo gerado após compactação.

-imagemDescompactada.bmp → Imagem reconstruída com perda de detalhes.

🔹 Lógica da Compactação:
-O algoritmo divide a imagem em quadrantes recursivamente.

-Quando a área é 3x3 ou menor, escolhe o pixel central como representativo.

-Salva os valores em três vetores: vetorR, vetorG, vetorB.

´-Na descompactação, reconstrói a imagem preenchendo os quadrantes com a cor do pixel central.

