#!/bin/bash
# Ce script compile la libft et le programme de test 'full_test.c'.

echo "🚀 Lancement de la compilation..."

# 1. Compile les fichiers .c en .o
cc -Wall -Wextra -Werror -c ft_*.c

# Vérifie si la compilation a réussi
if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de la compilation des fichiers sources de la libft."
    rm -f ft_*.o
    exit 1
fi

# 2. Crée la librairie libft.a
ar rcs libft.a ft_*.o

# 3. Compile le programme de test et le lie avec la libft
cc -Wall -Wextra -Werror full_test.c -o run_tests libft.a

# Vérifie si la compilation du test a réussi
if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de la compilation du programme de test 'full_test.c'."
    rm -f ft_*.o libft.a
    exit 1
fi

# 4. Nettoie les fichiers .o
rm ft_*.o

echo "✅ Compilation terminée avec succès. L'exécutable 'run_tests' est prêt."
echo "➡️  Pour lancer les tests, exécutez : ./run_tests"
