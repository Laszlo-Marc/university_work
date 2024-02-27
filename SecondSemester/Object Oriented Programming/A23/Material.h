#pragma once

typedef struct
{
    char name[50];
    char supplier[50];
    int quantity;
    char date[10];

} Material;

Material createMaterial(char name[], char supplier[], int quantity, char date[]);
char* getName(Material* material);
char* getSupplier(Material* material);
int getQuantity(Material* material);
char* getDate(Material* material);
void assignValues(Material* newMaterial, Material material);