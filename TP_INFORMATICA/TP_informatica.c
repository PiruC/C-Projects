#include <conio.h>
#include <stdio.h>
#include <string.h>

#define MAX_PELICULAS   100
#define DIAS            7
#define MAX_LONG_NOMBRE     60

// Declaracion de variables globales
typedef struct {
    int ID,Views_dia[DIAS];
    float Punt_dia[DIAS],Views_Total,Punt_Total;
    char Nombre[MAX_LONG_NOMBRE];
}peliculas;

peliculas ListaPeliculas[MAX_PELICULAS];

// Lista de funciones
void Inicializar (void);    // Inicializa la lista de peliculas por archivos basuras
void OPCION1 (void);        // Ingresa a la opcion 1 y realiza el procesamiento de datos
void OPCION2 (void);        // Ingresa a la opcion 2 y realiza ...
void OPCION3 (void);        // ...
void OPCION4 (void);        // ...
void CargarArchivo(FILE *archivo,int num_archiv);
void RANKING(void);
void CargaTotalViews(void);
int BuscaID(int id);

int main ()
{
    FILE *archivo_pelicula,*archivo_datos7dias;
    int opcion;
sds
    prisntf("Bievenidos al programa\n");

    // Inicializamos el registro
    Inicializar();

    // Abre el archivo y carga los datos al registro
    CargarArchivo(archivo_pelicula,1);
    CargarArchivo(archivo_datos7dias,2);

    printf("Menu:\n1:Ranking y top10\n2:Valoracion semanal\n3:Filtro cantidad de visualizaciones\n4:Pico visualizaciones\n0:Cerrar\nOpcion:");
    scanf("%d",&opcion);

    while (opcion != 0)
    {
        switch (opcion)
        {
            case 1:
            {
                OPCION1();
            break;
            }
            case 2:
            {
                OPCION2();
            break;
            }
            case 3:
            {
                OPCION3();
            break;
            }
            case 4:
            {
                OPCION4();
            break;
            }
        }
        printf("Menu:\n1:Ranking y top10\n2:Valoracion semanal\n3:Filtro cantidad de visualizaciones\n4:Pico visualizaciones\n0:Cerrar\nOpcion:");
        scanf("%d",&opcion);
    }

    printf("\nGracias por usar el programa");

    getch();
    return 0;
}

// Cuerpo de funciones //

// --Funciones de inicializacion-- //
void Inicializar (void)
{   
    for (int i = 0; i < MAX_PELICULAS; i++)
    {
        ListaPeliculas[i].ID = 0;
        ListaPeliculas[i].Punt_Total = 0;
        ListaPeliculas[i].Views_Total = 0;
        for (int j = 0; j < DIAS; j++)
        {
            ListaPeliculas[i].Punt_dia[j] = 0;
            ListaPeliculas[i].Views_dia[j] = 0;
        }
    }
    return;
}
void CargarArchivo (FILE *archivo,int num_archivo)
{
    if (num_archivo == 1)
    {
        if ((archivo = fopen("peliculas.txt", "r")) == NULL)
            printf ( "Error en la apertura. Es posible que el fichero no exista \n");
        for (int i = 0;i < MAX_PELICULAS; i++)
        {
            if (!feof(archivo))
            {
                fscanf (archivo, "%d%s\n", &ListaPeliculas[i].ID, ListaPeliculas[i].Nombre);
            }
            printf("\n%d %s",ListaPeliculas[i].ID, ListaPeliculas[i].Nombre);
        }
    }
    else if (num_archivo == 2)
    {
        if ((archivo = fopen("datos_7dias.txt", "r")) == NULL)
            printf ( "Error en la apertura. Es posible que el fichero no exista \n");
        int id_aux,dia,views,lista;
        float punt;
        
        while (!feof(archivo))
        {
            fscanf (archivo, "%d%d%d%f",&id_aux,&dia,&views,&punt);
            lista = BuscaID(id_aux);
            if (lista == MAX_PELICULAS+1)
                printf("La pelicula no existe");
            else
            {
                ListaPeliculas[lista].Views_dia[dia-1] = views;
                ListaPeliculas[lista].Punt_dia[dia-1] = punt;   
            }
        }
        // printf("\n\n");
        // for (int i = 0; i < MAX_PELICULAS; i++)
        // {
        //     printf("Id:\tDia:\tViews:\tPuntuacion:");
        //     for (int dia_ = 0; dia_ < DIAS; dia_++)
        //     {
        //         printf("\n%d\t%d\t%d\t%.2f",ListaPeliculas[i].ID,dia_+1,ListaPeliculas[i].Views_dia[dia_],ListaPeliculas[i].Punt_dia[dia_]);  
        //     }
        //     printf("\n\n");
        // }
    }
    fclose(archivo);
    return;
}

// --Funciones de menu-- //
void OPCION1 (void)
{
    printf("\n\n");
    RANKING();
    return;
}
void OPCION2 (void)
{

    return;
}
void OPCION3 (void)
{

    return;
}
void OPCION4 (void)
{

    return;
}

void RANKING (void)
{
    float Top10_views[10];
    int Top10_id[10];

    //Carga el total de visualizaciones
	CargaTotalViews();
    //Compara todas las visualizaciones del conjunto y genera una nueva lista con el top10 de visualizaciones y de IDs de peliculas 
    //Compara(Top10_views,Top10_id);
    //Muestra por pantalla toda la lista
    //Muestra();
    //Graba todo a un archivo
    //GRABAR_TOP10(Top10_views,Top10_id);

    return;
}

void CargaTotalViews(void)
{
    int dia,lista;

    //Limpia el total de visualizaciones en todo el conjunto de peliculas
    for (lista = 0;lista < MAX_PELICULAS; lista++)
    {
        for ( dia = 0; dia < DIAS; dia++)
        {
            ListaPeliculas[lista].Views_Total = ListaPeliculas[lista].Views_dia[dia] + ListaPeliculas[lista].Views_Total;
        }
    }
    printf("\n\n");
    for (int i = 0; i < MAX_PELICULAS; i++)
    {
        printf("Id:\tDia:\tViews:\tPuntuacion:\tTotal Views:");
        for (int dia_ = 0; dia_ < DIAS; dia_++)
        {
            printf("\n%d\t%d\t%d\t%.2f\t\t%.0f",ListaPeliculas[i].ID,dia_+1,ListaPeliculas[i].Views_dia[dia_],ListaPeliculas[i].Punt_dia[dia_],ListaPeliculas[i].Views_Total);  
        }
        printf("\n\n");
    }
    return;
}

int BuscaID(int id)
{asdasd
	print("ss");
    int indice;

    for (int i = 0; i < MAX_PELICULAS; i++)
    {
        if (ListaPeliculas[i].ID == id)
        {
            indice = i;
            return indice;
        }    
    }
    return MAX_PELICULAS+1;
}
