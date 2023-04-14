#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char title[20];
    float freq_min, freq_max;
    char major_scale[20];
    unsigned short octave;
    char dynamics[20];
} Music;

Music musics[100];
unsigned int musicIdx = 0;

char scales[] = {'C','D','E','F','G','A','B'};
float no69 = 440;

float getFreq(long no) {
    return (float)pow(pow(2.0, 1.0 / 12.0), (double)no) * no69;
}

void getMusic(void) {
    FILE *fp = fopen("music.txt", "r");
    
    if (fp == NULL) {
        printf("No music.txt file exist.\n");
        return;
    }
    
    const int max = 1024;
    char line[max];
    char *pLine;
    
    while (!feof(fp)) {
        pLine = fgets(line, max, fp);
        if (pLine != NULL) {
            char *ptr = strtok(pLine, ",");
            while (ptr != NULL) {
                strcpy(musics[musicIdx].title, ptr);
                
                ptr = strtok(NULL, ",");
                musics[musicIdx].freq_min = atof(ptr);
                
                ptr = strtok(NULL, ",");
                musics[musicIdx].freq_max = atof(ptr);
                
                ptr = strtok(NULL, ",");
                strcpy(musics[musicIdx].major_scale, ptr);
                
                ptr = strtok(NULL, ",");
                musics[musicIdx].octave = (unsigned short)atoi(ptr);
                
                ptr = strtok(NULL, ",");
                short i = 0;
                while (ptr[i++]);
                ptr[i-2] = '\0';
                strcpy(musics[musicIdx++].dynamics, ptr);
                
                ptr = strtok(NULL, ",");
            }
        }
    }
    fclose(fp);
}

Music findMusic(Music m) {
    Music result;
    
    for (int i = 0; i < musicIdx; i++)
        if (musics[i].freq_min >= m.freq_min)
            if (musics[i].freq_max <= m.freq_max)
                if (strcmp(musics[i].major_scale, m.major_scale) == 0)
                    if (musics[i].octave == m.octave)
                        if (strcmp(musics[i].dynamics, m.dynamics) == 0)
                            result = musics[i];
    
    return result;
}

int main(int argc, char *argv[]) {
    getMusic();
    
    float freq_min, freq_max;
    char major_scale[20];
    unsigned short octave;
    char dynamics[20];
    
    printf("Input minimum frequency: ");
    scanf("%f", &freq_min);
    
    printf("Input maximum frequency: ");
    scanf("%f", &freq_max);
    
    getchar();
    printf("Input major scale: ");
    scanf("%[^\n]", major_scale);
    
    printf("Input octave: ");
    scanf("%hd", &octave);
    
    printf("Input dynamics: ");
    scanf("%s", dynamics);
    
    long min = 0, max = 0;
    while (getFreq(min--) > freq_min);
    while (getFreq(max++) < freq_max);
    
    Music music;
    music.freq_min = freq_min;
    music.freq_max = freq_max;
    strcpy(music.major_scale, major_scale);
    music.octave = octave;
    strcpy(music.dynamics, dynamics);
    
    Music result = findMusic(music);
    printf("Title: %s\n", result.title);
}
