#include "helpers.h"
#include <math.h>
#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2
#define X 0
#define Y 1
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            uint8_t rgb_final = (uint8_t) round(average);

            image[i][j].rgbtBlue = rgb_final;
            image[i][j].rgbtGreen = rgb_final;
            image[i][j].rgbtRed = rgb_final;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color)
{
    /*
     * getBluer tem a função de receber a posição do pixel que estamos usando (i / j), e qual cor (color);
     * Vai agora passar por todos os pixels envolta dela, tirando os invalidos(fora do limete);
     * Depois vai somar todas as cores igual a cor que estamos trabalhando;
     * Por fim, vai retornar a media dessa cor;
     */

    float count = 0; // Numero de pixels vizinhos
    int soma = 0;    // Total de Bytes daquela cor

    // Percorrer todos os byte em volta (indo pra um acima e um abaixo)
    for (int linha = i - 1; linha <= i + 1; linha++)
    {
        // Percorrer todos os byte em volta (indo pra um atras e um a frente)
        for (int coluna = j - 1; coluna <= j + 1; coluna++)
        {
            // Verifica se esta fora dos limetes (limte é height -1 ou width -1) e se for pula;
            if (linha < 0 || linha >= height || coluna < 0 || coluna >= width)
            {
                continue;
            }
            // Soma as cores iguais
            if (color == RED_COLOR)
            {
                soma += image[linha][coluna].rgbtRed;
            }
            else if (color == GREEN_COLOR)
            {
                soma += image[linha][coluna].rgbtGreen;
            }
            else
            {
                soma += image[linha][coluna].rgbtBlue;
            }
            count++;
        }
    }

    return round(soma / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copiando a imagem
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // vai substituir a cor, pela media dela nos pixels vizinhos
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, RED_COLOR);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, GREEN_COLOR);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, BLUE_COLOR);
        }
    }
}

int getEdge(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color, int G)
{
    int soma = 0; // Total de Bytes daquela cor

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Percorrer todos os byte em volta (indo pra um acima e um abaixo)
    for (int linha = i - 1, x = 0; linha <= i + 1; linha++, x++)
    {

        // Percorrer todos os byte em volta (indo pra um atras e um a frente)
        for (int coluna = j - 1, y = 0; coluna <= j + 1; coluna++, y++)
        {
            // Verifica se esta fora dos limetes (limte é height -1 ou width -1) e se for pula;
            if (linha < 0 || linha >= height || coluna < 0 || coluna >= width)
            {
                continue;
            }
            // Soma as cores iguais
            if (color == RED_COLOR)
            {
                if (G == X)
                {
                    soma += (image[linha][coluna].rgbtRed * Gx[x][y]);
                }
                else
                {
                    soma += (image[linha][coluna].rgbtRed * Gy[x][y]);
                }
            }
            else if (color == GREEN_COLOR)
            {
                if (G == X)
                {
                    soma += (image[linha][coluna].rgbtGreen * Gx[x][y]);
                }
                else
                {
                    soma += (image[linha][coluna].rgbtGreen * Gy[x][y]);
                }
            }
            else
            {
                if (G == X)
                {
                    soma += (image[linha][coluna].rgbtBlue * Gx[x][y]);
                }
                else
                {
                    soma += (image[linha][coluna].rgbtBlue * Gy[x][y]);
                }
            }
        }
    }

    return soma;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copiando a imagem
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Percorrendo cada pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Inicializando Gx's
            int redX = getEdge(i, j, height, width, copy, RED_COLOR, X);
            int greenX = getEdge(i, j, height, width, copy, GREEN_COLOR, X);
            int blueX = getEdge(i, j, height, width, copy, BLUE_COLOR, X);

            // Inicializando Gy's
            int redY = getEdge(i, j, height, width, copy, RED_COLOR, Y);
            int greenY = getEdge(i, j, height, width, copy, GREEN_COLOR, Y);
            int blueY = getEdge(i, j, height, width, copy, BLUE_COLOR, Y);

            // Somando os G's
            int red = round(sqrt((redX * redX) + (redY * redY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));

            // Colocando o limete
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // vai substituir a cor, pela media dela nos pixels vizinhos
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}
