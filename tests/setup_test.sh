#!/bin/sh

# Exécution du raytracer POCGraph
./raytracer POCGraph
raytracer_exit_code=$?

# Vérification de la sortie du raytracer POCGraph
if [ $raytracer_exit_code -ne 0 ]; then
  echo "Erreur : L'exécution de ./raytracer POCGraph a échoué avec le code de sortie $raytracer_exit_code."
  exit 1
fi

# Changement de répertoire
cd tests
if [ $? -ne 0 ]; then
  echo "Erreur : Impossible de changer de répertoire vers 'tests'."
  exit 2
fi

# Suppression du fichier poc.ppm.expected
rm poc.ppm.expected

# Renommage du fichier poc.ppm en poc.ppm.expected
mv poc.ppm poc.ppm.expected
if [ $? -ne 0 ]; then
  echo "Erreur : Impossible de renommer le fichier poc.ppm en poc.ppm.expected."
  exit 4
fi