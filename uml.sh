#!/bin/bash

PLANTUML_PUML="uml.puml"
PLANTUML_TARGET="${PLANTUML_PUML%.puml}.svg"

SOURCE=$(find sources -name "*.hpp" -print)

# Functions

clean_uml() {
  rm -rf documentation/${PLANTUML_TARGET}
  rm -rf ${PLANTUML_PUML}
}

clear_uml() {
  clean_uml
  exit 0
}

generate_uml() {
  if command -v hpp2plantuml &> /dev/null; then
    INPUT_FILES=""
    for HEADER in ${SOURCE}; do
      INPUT_FILES+="-i ${HEADER} "
    done
    echo "@startuml" > ${PLANTUML_PUML}
    hpp2plantuml ${INPUT_FILES} -o ${PLANTUML_PUML}
    echo "@enduml" >> ${PLANTUML_PUML}
    mkdir -p documentation
    plantuml -tsvg -o documentation ${PLANTUML_PUML}
  else
    echo "Erreur: hpp2plantuml n'est pas installé."
    exit 1
  fi
}

# Execution

clean_uml
generate_uml
clear_uml