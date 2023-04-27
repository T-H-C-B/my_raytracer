#!/bin/bash

# Installer Homebrew si ce n'est pas déjà fait
if ! command -v brew &> /dev/null; then
    echo "Homebrew n'est pas installé. Installation en cours..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
else
    echo "Homebrew est déjà installé."
fi

# Mettre à jour Homebrew
echo "Mise à jour de Homebrew..."
brew update

# Installer hpp2plantuml
echo "Installation de hpp2plantuml..."
brew install hpp2plantuml

# Installer PlantUML
echo "Installation de PlantUML..."
brew install plantuml

# Installer OpenJDK
echo "Installation d'OpenJDK..."
brew install openjdk

# Configurer OpenJDK
if ! grep -q "export JAVA_HOME" ~/.zshrc; then
    echo "Configuration d'OpenJDK dans ~/.zshrc..."
    echo 'export JAVA_HOME=$(/usr/libexec/java_home)' >> ~/.zshrc
    echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ~/.zshrc
fi

if ! grep -q "export JAVA_HOME" ~/.bashrc; then
    echo "Configuration d'OpenJDK dans ~/.bashrc..."
    echo 'export JAVA_HOME=$(/usr/libexec/java_home)' >> ~/.bashrc
    echo 'export PATH=$JAVA_HOME/bin:$PATH' >> ~/.bashrc
fi

# Installer Graphviz
echo "Installation de Graphviz..."
brew install graphviz

# Terminé
echo "Toutes les dépendances ont été installées avec succès. Redémarrez votre terminal pour appliquer les modifications."
