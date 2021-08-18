#!/bin/bash

set -euo pipefail

run() {
  bin=${1}
  shift
  echo -ne "\nTesting ${bin}...\n"
  ../cmake-build-debug/${bin} ${@} # --verbose --filter external/*
}

run "test_ctoi" ${@}
run "test_ndarray" ${@}
run "test_bmh" ${@}
run "test_jaccard_dist" ${@}
run "test_suffix_tree" ${@}

