#!/bin/sh

# Créer un répertoire temporaire pour stocker le fichier poc.ppm
temp_output_dir=$(mktemp -d)

# Exécuter le conteneur Docker et monter les répertoires
docker run --rm \
  -v "$(pwd)":/app \
  -v ${temp_output_dir}:/app/output \
  clemlgss/my-raytracer \
  sh -c "cd /app && cmake . && make -j 16 && ./raytracer POCGraph --test && cp poc.ppm /app/output/"

# Copier le fichier poc.ppm du répertoire temporaire vers le répertoire courant
cp ${temp_output_dir}/poc.ppm .

# Supprimer le répertoire temporaire
rm -rf ${temp_output_dir}


mv poc.ppm ./tests/poc.ppm.expected
rm -rf ./tests/poc.ppm
