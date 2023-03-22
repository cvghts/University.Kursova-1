#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;

const int M = 6, N = 9;

//Переглянути файл
void view_file(char* name)
{
    char s[100]; FILE* f;
    f = fopen(name, "rt");
    if (f == NULL) { puts("Неможливо відкрити файл для перегляду"); return; }
    printf("\nПерегляд файлу: %s\n", name);
    while (fgets(s, 100, f))
    {
        s[strlen(s) - 1] = '\0';
        puts(s);
    }
    fclose(f);
}

//Заповнити матрицю значеннями із файлу
void create_matrix(double matr[M][N], char* name)
{
    FILE* f;
    char s[100], * t;
    int i = 0, j;
    f = fopen(name, "rt");
    if (f == NULL) { puts("Неможливо відкрити файл для перегляду"); return; }
    while (fgets(s, 100, f))
    {
        j = 0;
        t = strtok(s, " \t");
        while (t != NULL)
        {
            matr[i][j] = atof(t);
            t = strtok(NULL, " \t");
            j++;
        }
        i++;
    }
    fclose(f);
    return;
}

//Вивести матрицю на екран та у файл
void output_matrix(double matr[M][N], char* name2)
{
    FILE* f2;
    int i, j;
    f2 = fopen(name2, "wt");
    if (f2 == NULL) { puts("Неможливо відкрити файл"); return; }
    printf("\n\nПерегляд матрицi:\n");
    fprintf(f2, "Перегляд матрицi:\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%7.1f\t", matr[i][j]);
            fprintf(f2, "%7.1f\t", matr[i][j]);
        }
        puts("");
        fprintf(f2, "%s", "\n");
    }
    fclose(f2);
    return;
}

//Обчислити значення кількості елементів матриці, абсолютне значення яких менше 1
void kilkist(double matr[M][N], char* name2)
{
    FILE* f2;
    int i, j, h = 0;
    f2 = fopen(name2, "at");
    if (f2 == NULL)
    {
        puts("Не вдається відкрити файл для додавання даних\n"); return;
    }
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matr[i][j] < 1) h++;
        }
    }
    printf("\nКількість елементів менших за 1:  %i\t", h);
    fprintf(f2, "\nКількість елементів менших за 1: %i\n", h);
    fclose(f2);
}

/*Визначити кількість ненульових елементів лише у тих рядках, які не містять від’ємних елементів*/
void kilkist2(double matr[M][N], char* name2)
{
    FILE* f2;
    f2 = fopen(name2, "at");
    if (f2 == NULL)
    {
        puts("Не вдається відкрити файл для додавання даних\n"); return;
    }
    puts("\nКількість ненульових елементів:");
    fprintf(f2, "\nКількість ненульових елементів:");
    int kol = 0, h = 0;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matr[i][j] < 0) h = i;
        }
        for (int j = 0; j < N; j++)
        {
            if (i != h && matr[i][j] != 0) kol++;
        }
    }
    printf("%i\t", kol);
    fprintf(f2, "%i\t", kol);
    fclose(f2);
}

/*Обчислити елементи вектора як середнє арифметичне елементів першого та останнього рядків матриці*/
void create_vector(double matr[M][N], double vekt[M], char* name2)
{
    double sum = 0, ser = 0; int p = 0;
    FILE* f2;
    f2 = fopen(name2, "at");
    if (f2 == NULL)
    {
        puts("Не вдається відкрити файл для додавання даних\n"); return;
    }
    puts("\nСтворений вектор:");
    fprintf(f2, "\nСтворений вектор:\n");
    for (int i = 0; i < M; i++)
    {
        sum = 0, ser = 0;
        for (int j = 0; j < N; j++)
        {
            if (i == 0 || i == M - 1)
            {
                sum += matr[i][j]; p = 1;
            }
        }
        if (i == 0 || i == M - 1)
        {
            if (p)
            {
                ser = sum / N;
                vekt[i] = ser;
                printf("%7.1f\t", vekt[i]);
                fprintf(f2, "%7.1f\t", vekt[i]);
            }
        }
    }
    fclose(f2);
}

//Створити нові рядки з малих літер латиниці рядків файлу
void mal(char* name3, char* name2)
{
    FILE* f3, * f2;
    char s[100];
    f3 = fopen(name3, "rt");
    if (f3 == NULL) { puts("Не вдається відкрити файл для перегляду"); return; }
    f2 = fopen(name2, "at");
    if (f2 == NULL) { puts("Не вдається відкрити файл для додавання даних\n"); return; }
    puts("\nНові рядки з малих літер латиниці:");
    fputs("\nНові рядки з малих літер латиниці:\n", f2);
    while (fgets(s, 100, f3))
    {
        for (int i = 0; i < strlen(s); i++)
        {
            if (s[i] >= 'a' && s[i] <= 'z')
            {
                printf("%c", s[i]);
                fprintf(f2, "%c", s[i]);
            }
        }
        printf(" ");
        fprintf(f2, " ");
    }
    fclose(f2);
    fclose(f3);
}

//Вивести рядки, які містять хоча б одне слово лише з великих літер
void vel(char* name3, char* name2)
{
    FILE* f3, * f2;
    f3 = fopen(name3, "rt");
    if (f3 == NULL) { puts("Не вдається відкрити файл для перегляду"); return; }
    f2 = fopen(name2, "at");
    if (f2 == NULL) { puts("Не вдається відкрити файл для додавання даних\n"); return; }
    puts("\nРядки, які містять хоча б одне слово лише з великих літер:");
    fputs("\nРядки, які містять хоча б одне слово лише з великих літер:\n", f2);
    char s[100], rezult[100], word[20], * t; int k = 0;
    bool ch = 0;
    while (fgets(s, 100, f3))
    {
        strcpy(rezult, s);
        t = strtok(s, " ,.:;/\t");

        while (t != NULL)
        {
            strcpy(word, t);
            for (int i = 0; i < strlen(word); i++)
                if ('A' <= t[i] && t[i] <= 'Z' || 'А' <= t[i] && t[i] <= 'Я')
                    k++;

            if (k == strlen(t))
            {
                ch = 1;
                k = 0;
                t = strtok(NULL, " ,.:;/\t");
            }
        }

        if (ch)
        {
            cout << rezult; ch = 0;
            fprintf(f2, "%s", rezult);
        }
    }
    fclose(f2);
    fclose(f3);
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    double A[M][N], B[N];
    char name1[] = "E:\\K1.txt";
    char name2[] = "E:\\K2.txt";
    char name3[] = "E:\\K3.txt";

    //Перегляд файлу
    view_file(name1);
    //Заповнити матрицю числами із файлу
    create_matrix(A, name1);
    //Вивести матрицю на екран та у файл
    output_matrix(A, name2);
    /*Обчислити значення кількості елементів матриці, абсолютне значення яких менше 1*/
    kilkist(A, name2)
        /*Визначити кількість ненульових елементів лише у тих рядках, які не містять від’ємних елементів*/
        kilkist2(A, name2);
    /*Обчислити елементи вектора як середнє арифметичне елементів першого та останнього рядків матриці*/
    create_vector(A, B, name2);
    //Переглянути файл
    view_file(name3);
    //Створити нові рядки з малих літер латиниці рядків файлу
    mal(name3, name2);
    //Вивести рядки, які містять хоча б одне слово лише з великих літер
    vel(name3, name2);
    //Переглянути файл
    view_file(name2);
}

