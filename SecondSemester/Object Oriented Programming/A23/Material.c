#include "Material.h"
#include <stdio.h>
#include <string.h>

Material createMaterial(char name[], char supplier[], int quantity, char date[])
{

    Material material;
    strcpy(material.name, name);
    strcpy(material.supplier, supplier);
    material.quantity = quantity;
    strcpy(material.date, date);

    return material;
}

void assignValues(Material* newMaterial, Material material)
{
    strcpy(newMaterial->name, material.name);
    strcpy(newMaterial->supplier, material.supplier);
    newMaterial->quantity = material.quantity;
    strcpy(newMaterial->date, material.date);
}

char* getName(Material* material)
{
    return material->name;
}

char* getSupplier(Material* material)
{
    return material->supplier;
}

int getQuantity(Material* material)
{
    return material->quantity;
}

char* getDate(Material* material)
{
    return material->date;
}