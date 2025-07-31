# 📦 Projeto 2 – Compactação de Imagens BMP

**Disciplina:** Algoritmos e Programação II – Universidade Presbiteriana Mackenzie  
**Objetivo:** Compactar e descompactar imagens **BMP 24 bits (true color)** utilizando um método **recursivo baseado em quadrantes**.

---

## ✨ Visão Geral

Este projeto implementa um **compactador de imagens BMP** que:

- Lê uma imagem original (`imagemOriginal.bmp`);
- **Compacta** a imagem salvando apenas pixels representativos em quadrantes;
- Gera um arquivo **compactado (`.zmp`)**;
- **Descompacta** o arquivo para gerar uma imagem reconstruída (`imagemDescompactada.bmp`).

---

## 🔹 Como Funciona

### 🔸 Compactação
1. Divide a imagem **recursivamente em 4 quadrantes**.  
2. Quando o quadrante é **≤ 3x3**, salva apenas o **pixel central**.  
3. Armazena os valores RGB em **três vetores**: `vetorR`, `vetorG` e `vetorB`.  
4. Cria o arquivo **`imagemCompactada.zmp`** contendo:  
   - Cabeçalho BMP  
   - Pixels representativos

### 🔸 Descompactação
1. Lê o arquivo **`.zmp`**  
2. Reconstrói a matriz de pixels preenchendo cada quadrante com seu **pixel central**  
3. Salva como **`imagemDescompactada.bmp`**  

---
