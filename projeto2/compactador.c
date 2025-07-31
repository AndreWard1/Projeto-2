//André Ihsan Ward - 10425684
//Projeto2 - AP2



#include <stdio.h>
#include <stdlib.h>

#define ALTURA_MAXIMA 100
#define LARGURA_MAXIMA 100

// Cabeçalho BMP (54 bytes fixos)
unsigned char cabecalho[54];
// Vetores para armazenar os valores RGB compactados
unsigned char vetorR[ALTURA_MAXIMA * LARGURA_MAXIMA];
unsigned char vetorG[ALTURA_MAXIMA * LARGURA_MAXIMA];
unsigned char vetorB[ALTURA_MAXIMA * LARGURA_MAXIMA];
int indiceRGB = 0;

int largura, altura, preenchimento;

// Lê a imagem BMP original e armazena os pixels na matriz
void lerImagemBMP(const char *nomeArquivo, unsigned char imagem[ALTURA_MAXIMA][LARGURA_MAXIMA][3]) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo BMP.\n");
        exit(1);
    }

    fread(cabecalho, sizeof(unsigned char), 54, arquivo);

    largura = *(int*)&cabecalho[18];
    altura = *(int*)&cabecalho[22];

    preenchimento = (4 - (largura * 3) % 4) % 4; // Calcula padding necessário (múltiplo de 4)

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            fread(&imagem[i][j][2], 1, 1, arquivo); // R
            fread(&imagem[i][j][1], 1, 1, arquivo); // G
            fread(&imagem[i][j][0], 1, 1, arquivo); // B
        }
        fseek(arquivo, preenchimento, SEEK_CUR); // Pula padding
    }

    fclose(arquivo);
}

// Compacta a imagem recursivamente dividindo em quadrantes
void compactarImagem(unsigned char imagem[ALTURA_MAXIMA][LARGURA_MAXIMA][3], int x1, int y1, int x2, int y2) {
    if ((x2 - x1 <= 3) || (y2 - y1 <= 3)) {
        // Região base da recursão: salva o pixel central como representativo
        int px = (x1 + x2) / 2;
        int py = (y1 + y2) / 2;

        vetorR[indiceRGB] = imagem[py][px][2];
        vetorG[indiceRGB] = imagem[py][px][1];
        vetorB[indiceRGB] = imagem[py][px][0];
        indiceRGB++;
        return;
    }

    int meioX = (x1 + x2) / 2;
    int meioY = (y1 + y2) / 2;

    // Chamada recursiva para os 4 quadrantes
    compactarImagem(imagem, x1, y1, meioX, meioY); // Q1
    compactarImagem(imagem, meioX, y1, x2, meioY); // Q2
    compactarImagem(imagem, meioX, meioY, x2, y2); // Q3
    compactarImagem(imagem, x1, meioY, meioX, y2); // Q4
}

// Salva os dados compactados no arquivo .zmp
void salvarArquivoCompactado(const char *nomeArquivo) {
    FILE *saida = fopen(nomeArquivo, "wb");
    fwrite(cabecalho, sizeof(unsigned char), 54, saida);
    for (int i = 0; i < indiceRGB; i++) {
        fwrite(&vetorR[i], sizeof(unsigned char), 1, saida);
        fwrite(&vetorG[i], sizeof(unsigned char), 1, saida);
        fwrite(&vetorB[i], sizeof(unsigned char), 1, saida);
    }
    fclose(saida);
}

// Lê os dados RGB compactados do arquivo .zmp
void lerArquivoCompactado(const char *nomeArquivo, unsigned char imagem[ALTURA_MAXIMA][LARGURA_MAXIMA][3]) {
    FILE *entrada = fopen(nomeArquivo, "rb");
    if (!entrada) {
        printf("Erro ao abrir o arquivo .zmp\n");
        exit(1);
    }

    fread(cabecalho, sizeof(unsigned char), 54, entrada);
    largura = *(int*)&cabecalho[18];
    altura = *(int*)&cabecalho[22];

    int totalQuadrantes = (largura * altura) / 9;
    if (totalQuadrantes > ALTURA_MAXIMA * LARGURA_MAXIMA)
        totalQuadrantes = ALTURA_MAXIMA * LARGURA_MAXIMA;

    for (int i = 0; i < totalQuadrantes; i++) {
        fread(&vetorR[i], sizeof(unsigned char), 1, entrada);
        fread(&vetorG[i], sizeof(unsigned char), 1, entrada);
        fread(&vetorB[i], sizeof(unsigned char), 1, entrada);
    }
    fclose(entrada);
}

// Reconstrói a imagem a partir dos dados RGB compactados
void reconstruirImagem(unsigned char imagem[ALTURA_MAXIMA][LARGURA_MAXIMA][3], int x1, int y1, int x2, int y2) {
    if ((x2 - x1 <= 3) || (y2 - y1 <= 3)) {
        // Preenche a região da matriz com o pixel representativo
        for (int i = y1; i < y2; i++) {
            for (int j = x1; j < x2; j++) {
                imagem[i][j][2] = vetorR[indiceRGB];
                imagem[i][j][1] = vetorG[indiceRGB];
                imagem[i][j][0] = vetorB[indiceRGB];
            }
        }
        indiceRGB++;
        return;
    }

    int meioX = (x1 + x2) / 2;
    int meioY = (y1 + y2) / 2;

    // Chamada recursiva para reconstruir os quadrantes
    reconstruirImagem(imagem, x1, y1, meioX, meioY);
    reconstruirImagem(imagem, meioX, y1, x2, meioY);
    reconstruirImagem(imagem, meioX, meioY, x2, y2);
    reconstruirImagem(imagem, x1, meioY, meioX, y2);
}

// Salva a imagem reconstruída no formato BMP
void salvarImagemBMP(const char *nomeArquivo, unsigned char imagem[ALTURA_MAXIMA][LARGURA_MAXIMA][3]) {
    FILE *arquivo = fopen(nomeArquivo, "wb");
    fwrite(cabecalho, sizeof(unsigned char), 54, arquivo);

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            fwrite(&imagem[i][j][2], 1, 1, arquivo);
            fwrite(&imagem[i][j][1], 1, 1, arquivo);
            fwrite(&imagem[i][j][0], 1, 1, arquivo);
        }
        // Preenche a linha com 0s se necessário (padding)
        for (int k = 0; k < preenchimento; k++) {
            fputc(0x00, arquivo);
        }
    }
    fclose(arquivo);
}

int main() {
    unsigned char imagem[ALTURA_MAXIMA][LARGURA_MAXIMA][3];

    // Etapa 1: compactar imagem original
    lerImagemBMP("imagemOriginal.bmp", imagem);
    compactarImagem(imagem, 0, 0, largura, altura);
    salvarArquivoCompactado("imagemCompactada.zmp");
    printf("Compactacao concluida.\n");

    // Etapa 2: descompactar imagem
    indiceRGB = 0;
    lerArquivoCompactado("imagemCompactada.zmp", imagem);
    reconstruirImagem(imagem, 0, 0, largura, altura);
    salvarImagemBMP("imagemDescompactada.bmp", imagem);
    printf("Descompactacao concluida.\n");

    return 0;
}

