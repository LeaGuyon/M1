#include <stdio.h>
#include <stdlib.h>

#define FILENAME 'tata.txt' // Ton fichier avec les erreurs
#define OUTPUT_FILENAME "output.csv" // Fichier CSV de sortie

int main() {
    FILE *input_file, *output_file;
    double error;
    int time_step = 0;

    // Ouvrir le fichier d'entrée
    input_file = fopen(FILENAME, "r");
    if (input_file == NULL) {
        printf("Erreur lors de l'ouverture du fichier d'entrée.\n");
        return 1;
    }

    // Ouvrir le fichier de sortie (CSV)
    output_file = fopen(OUTPUT_FILENAME, "w");
    if (output_file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie.\n");
        fclose(input_file);
        return 1;
    }

    // Écrire l'en-tête du fichier CSV
    fprintf(output_file, "Temps,Erreur\n");

    // Lire chaque ligne du fichier et traiter l'erreur
    while (fscanf(input_file, "%lf", &error) == 1) {
        // Écrire le temps et l'erreur dans le fichier CSV
        fprintf(output_file, "%d,%.4f\n", time_step, error);
        time_step++;  // Incrémenter le temps (en secondes, par exemple)
    }

    // Fermer les fichiers
    fclose(input_file);
    fclose(output_file);

    printf("Les données ont été enregistrées dans '%s'.\n", OUTPUT_FILENAME);

    return 0;
}
