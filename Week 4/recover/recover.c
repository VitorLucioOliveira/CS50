#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define size 512
typedef uint8_t byte;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    // Abriu o arquivo pra ler e vereficou se não é nulo
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    byte buffer[size];
    int img_count = 0;
    char img_name[8];
    FILE *img = NULL;

    while (fread(buffer, sizeof(byte), size, card) == 512)
    {
        // Verificando se é o JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (img_count > 0)
            {
                fclose(img);
            }

            sprintf(img_name, "%03i.jpg", img_count);
            img = fopen(img_name, "w");
            img_count++;
        }
        if (img != NULL)
        {
            fwrite(buffer, sizeof(byte), size, img);
        }
    }

    fclose(card);
    fclose(img);

    return 0;
}
