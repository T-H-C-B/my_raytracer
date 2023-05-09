#!/bin/sh

# Créer un répertoire temporaire pour stocker le fichier poc.ppm
temp_output_dir=$(mktemp -d)

# Exécuter le conteneur Docker et monter les répertoires
docker run --rm \
  -v "$(pwd)":/app \
  -v ${temp_output_dir}:/app/output \
  clemlgss/my-raytracer \
  sh -c "cd /app && ./build.sh re && ./raytracer POCGraph --test && cp poc.ppm /app/output/ && ./build.sh fclean"

# Copier le fichier poc.ppm du répertoire temporaire vers le répertoire courant
sudo cp ${temp_output_dir}/poc.ppm .

# Supprimer le répertoire temporaire
rm -rf ${temp_output_dir}


mv poc.ppm ./tests/poc.ppm.expected
rm -rf ./tests/poc.ppm
