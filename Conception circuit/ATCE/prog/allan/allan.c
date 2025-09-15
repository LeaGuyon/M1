#include <stdlib.h>
#include <stdio.h>

int main() {
    printf("Lancement du script Octave...\n");

    // Appelle Octave avec le script
    int status = system("octave --silent --eval \"allan_manual\"");

    if (status != 0) {
        fprintf(stderr, "Erreur lors de l'appel à Octave\n");
        return 1;
    }

    printf("Script exécuté avec succès.\n");
    return 0;
}
