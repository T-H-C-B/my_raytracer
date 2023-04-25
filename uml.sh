#!/bin/bash

MAIN_PUML="main_uml.puml"
TMP_PUML_DIR="temp_puml"
PLANTUML_TARGET="${MAIN_PUML%.puml}.svg"

SOURCE=$(find sources -name "*.hpp" -print)

# Functions

clean_uml() {
  rm -rf documentation/${PLANTUML_TARGET}
  rm -rf ${MAIN_PUML}
  rm -rf ${TMP_PUML_DIR}
}

clear_uml() {
  rm -rf ${MAIN_PUML}
  rm -rf ${TMP_PUML_DIR}
}

generate_uml() {
  if command -v hpp2plantuml &> /dev/null; then
    mkdir -p ${TMP_PUML_DIR}
    echo "@startuml" > ${MAIN_PUML}
    for HEADER in ${SOURCE}; do
      BASENAME=$(basename ${HEADER%.hpp})
      TMP_PUML="${TMP_PUML_DIR}/${BASENAME}.puml"
      hpp2plantuml -i ${HEADER} -o ${TMP_PUML}
      echo "!include ${TMP_PUML}" >> ${MAIN_PUML}
    done
    echo "@enduml" >> ${MAIN_PUML}
    mkdir -p documentation
    plantuml -tsvg -o documentation ${MAIN_PUML}
  else
    echo "Erreur: hpp2plantuml n'est pas installé."
    exit 1
  fi
}

# Execution

clean_uml
generate_uml
clear_uml
