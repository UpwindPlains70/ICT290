//Aurthor: Peter Neve
//Version: 1
//Date: 26/08/2021
//Reads .obj file with UV coordinates only

#include "ReadOBJfile.h"
#include <stdio.h>
//Future update - allow for non UV .obj files

//Reads an OBJ file storing data in passed Object3D
//Pre-condition: Existing file name and Object3D variable
//Post-condition: populates the passed Object3D
void ReadOBJfile(char* fileName, Object3D* newObj) {

    int v, n, f, u;

    v = n = f = u = 0;

    int trash;

    setArrays(fileName, newObj);

    FILE* in_file = fopen(fileName, "r");

    //test for existing file
    if (in_file == NULL)
    {
        printf("Error! Could not open file: %s\n", fileName);
        exit(-1);
    }

    char lineHeader[bufferLength];
    int res;

    do {
        // read the first word of the line
        res = fscanf(in_file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if (strcmp(lineHeader, "v") == 0) { //Vertex

            fscanf(in_file, "%f %f %f\n", &newObj->vertices[v][0], &newObj->vertices[v][1], &newObj->vertices[v][2]);
            ++v;
        }
        else if (strcmp(lineHeader, "vt") == 0) { //texture coordinate (single vertex)

            fscanf(in_file, "%f %f\n", &newObj->uvs[u][0], &newObj->uvs[u][1]);
            ++u;
        }
        else if (strcmp(lineHeader, "vn") == 0) { //normal (one vertex)

            fscanf(in_file, "%f %f %f\n", &newObj->norms[n][0], &newObj->norms[n][1], &newObj->norms[n][2]);
            ++n;
        }
        else if (strcmp(lineHeader, "f") == 0) { //face (vertex / texture coord / normal) 3 times for triangle face

               //Read for objects with UV
            fscanf(in_file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &newObj->faces[f][0], &newObj->faces[f][1], &newObj->faces[f][2], &newObj->faces[f][3], &newObj->faces[f][4], &newObj->faces[f][5], &newObj->faces[f][6], &newObj->faces[f][7], &newObj->faces[f][8]);
            
            //Read for non UV objects
            //fscanf(in_file, "%d//%d %d//%d %d//%d\n", &newObj->faces[f][0], &newObj->faces[f][2], &newObj->faces[f][3], &newObj->faces[f][5], &newObj->faces[f][6], &newObj->faces[f][8] );
             ++f;
        }
    } while (res != EOF);

    fclose(in_file);
    reIndex(newObj);
}

//Dynamically assign array size for object3D lists
void setArrays(char* fileName, Object3D* newObj) {

    int v, n, f, u;

    v = n = f = u = 0;

    int nNorm = 0;
    int nUV = 0;

    FILE* in_file = fopen(fileName, "r");

    //test for existing file
    if (in_file == NULL)
    {
        printf("Error! Could not open file: %s\n", fileName);
        exit(-1);
    }

    char lineHeader[bufferLength];
    int res;

    do {
        // read the first word of the line
        res = fscanf(in_file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if (strcmp(lineHeader, "v") == 0) { //Vertex
            ++newObj->nverts;

        }
        else if (strcmp(lineHeader, "vt") == 0) { //texture coordinate (single vertex)
            ++nUV;

        }
        else if (strcmp(lineHeader, "vn") == 0) { //normal (one vertex)
            ++nNorm;

        }
        else if (strcmp(lineHeader, "f") == 0) { //face (vertex / texture coord / normal) 3 times for triangle face
            ++newObj->nfaces;

        }
    } while (res != EOF);

    newObj->vertices = (Point3D*)malloc(newObj->nverts * sizeof(Point3D));
    newObj->norms = (Point3D*)malloc(nNorm * sizeof(Point3D));
    newObj->uvs = (Point2D*)malloc(nUV * sizeof(Point2D));
    newObj->faces = (face3D*)malloc(newObj->nfaces * sizeof(face3D));

    fclose(in_file);
}

//.obj index = 1, c = 0 thus 1 needs to be taken from all face indexes
void reIndex(Object3D* obj) {
    for (int f = 0; f < obj->nfaces; f++) {
        --obj->faces[f][0];
        --obj->faces[f][1];
        --obj->faces[f][2];
        --obj->faces[f][3];
        --obj->faces[f][4];
        --obj->faces[f][5];
        --obj->faces[f][6];
        --obj->faces[f][7];
        --obj->faces[f][8];
    }
}

//Manully free memory
void freeObj(Object3D* obj) {
    free(obj->faces);
    free(obj->vertices);
    free(obj->norms);
    free(obj->uvs);
}

//Print all contents of 3D object
void printObjContent(Object3D* newObj) {

    printf("Total vertices: %d\n", newObj->nverts);
    printf("Total faces: %d\n", newObj->nfaces);

    printf("\nVertex values: ********************************************\n");
    for (int v = 0; v < newObj->nverts; v++)
        printf("vertex ID: Va = %f, Vb = %f, Vc = %f\n", newObj->vertices[v][0], newObj->vertices[v][1], newObj->vertices[v][2]);

    printf("\nUV values: ********************************************\n");
    for (int u = 0; u < newObj->nverts; u++)
        printf("UV: Ua = %f, Ub = %f\n", newObj->uvs[u][0], newObj->uvs[u][1]);

    printf("\nNormal values: ********************************************\n");
    for (int n = 0; n < newObj->nverts; n++)
        printf("norm ID: Va = %f, Vb = %f, Vc = %f\n", newObj->norms[n][0], newObj->norms[n][1], newObj->norms[n][2]);

    printf("\nFace values: ********************************************\n");
    for (int f = 0; f < newObj->nverts; f++)
        printf("face ID: Va = %d, Ua = %d, Na = %d, Vb = %d, Ub = %d, Nb = %d, Vc = %d, Uc = %d, Nc = %d,\n", newObj->faces[f][0], newObj->faces[f][1], newObj->faces[f][2], newObj->faces[f][3], newObj->faces[f][4], newObj->faces[f][5], newObj->faces[f][6], newObj->faces[f][7], newObj->faces[f][8]);

}
