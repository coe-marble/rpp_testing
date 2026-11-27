#!/usr/bin/env bash
# Build the complete, precompiled RPP test fixture for publication.
#
# The output is consumed directly from rpp_testing/rpp_autogen by rpp_cpp test
# builds. Pass --local to reuse the already-built workspace that contains this
# checkout of rpp_testing.
set -euo pipefail

readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly RPP_TESTING_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
readonly RPP_TESTING_PACKAGE_DIR="${RPP_TESTING_DIR}/rpp_testing"
readonly AUTOGEN_DIR="${RPP_AUTOGEN_DIR:-${RPP_TESTING_PACKAGE_DIR}/rpp_autogen}"
readonly RPP_DEV_REPOSITORY="${RPP_DEV_REPOSITORY:-https://github.com/coe-marble/rpp_dev.git}"
readonly RPP_DEV_REF="${RPP_DEV_REF:-main}"
readonly ROS_DISTRO_NAME="${ROS_DISTRO:-lyrical}"
readonly ROS_SETUP="${ROS_SETUP:-/opt/ros/${ROS_DISTRO_NAME}/setup.bash}"
LOCAL=false

usage() {
  cat <<'EOF'
Usage: build_rpp_autogen.sh [--local]

Without options, clone rpp_dev into a disposable workspace and build it with
tests disabled. With --local, reuse the ROS workspace containing this
rpp_testing checkout; rpp_cpp must already have been built there.
EOF
}

while (($#)); do
  case "$1" in
    --local) LOCAL=true ;;
    --help|-h) usage; exit 0 ;;
    *) echo "Unknown option: $1" >&2; usage >&2; exit 2 ;;
  esac
  shift
done

if [[ ! -f "${ROS_SETUP}" ]]; then
  echo "ROS setup file does not exist: ${ROS_SETUP}" >&2
  exit 1
fi

TEMP_WORKSPACE=""
RPP_CONFIG_HOME="$(mktemp -d -t rpp-autogen-config-XXXXXX)"
cleanup() {
  rm -rf "${RPP_CONFIG_HOME}"
  if [[ -n "${TEMP_WORKSPACE}" ]]; then
    rm -rf "${TEMP_WORKSPACE}"
  fi
}
trap cleanup EXIT

if [[ "${LOCAL}" == true ]]; then
  RPP_DEV_DIR="$(cd "${RPP_TESTING_DIR}/../.." && pwd)"
  WORKSPACE="$(cd "${RPP_DEV_DIR}/../.." && pwd)"
  if [[ ! -f "${WORKSPACE}/install/setup.bash" || ! -d "${WORKSPACE}/build/rpp_cpp" ]]; then
    echo "--local requires an existing rpp_cpp build in: ${WORKSPACE}" >&2
    exit 1
  fi
else
  TEMP_WORKSPACE="$(mktemp -d -t rpp-autogen-XXXXXX)"
  WORKSPACE="${TEMP_WORKSPACE}"
  mkdir -p "${WORKSPACE}/src"
  git clone --recurse-submodules --branch "${RPP_DEV_REF}" \
    "${RPP_DEV_REPOSITORY}" "${WORKSPACE}/src/rpp_dev"
fi
source_setup() {
  # ROS/ament setup scripts intentionally inspect optional unset variables.
  set +u
  # shellcheck disable=SC1090
  source "$1"
  set -u
}

source_setup "${ROS_SETUP}"
pushd "${WORKSPACE}" >/dev/null
# The C++ build also calls the CLI; keep that configuration in the disposable home.
export RPP_HOME="${RPP_CONFIG_HOME}"

if [[ "${LOCAL}" == false ]]; then
  # rpp_dev/COLCON_IGNORE blocks recursive discovery. Start at the runtime package.
  colcon build --base-paths "${WORKSPACE}/src/rpp_dev/src/rpp_cpp" \
    --packages-select rpp_cpp --cmake-args -DBUILD_TESTING=OFF
fi

export RPP_CPP_CORE_PATH="${WORKSPACE}/build/rpp_cpp"
for runtime_library in librpp_cpp.so librpp_cpp_core.so; do
  if [[ ! -f "${RPP_CPP_CORE_PATH}/${runtime_library}" ]]; then
    echo "Missing runtime library: ${RPP_CPP_CORE_PATH}/${runtime_library}. Build rpp_cpp before generating fixtures." >&2
    exit 1
  fi
done

source_setup "${WORKSPACE}/install/setup.bash"
export RPP_USE_ROS2_COMPILATION=true

rpp registry config set RPP_CPP_CORE_PATH "${RPP_CPP_CORE_PATH}"
rpp registry config set USE_ROS2_COMPILATION true
mkdir -p "${AUTOGEN_DIR}"
rpp test setup_tmp_rpp_with_test_plugins "${AUTOGEN_DIR}" --override

# Catch an outdated schema checkout before publishing a fixture rpp_cpp cannot use.
for sample in AllocationFixedSample AllocationEnvelope AllocationEvolvedSample AllocationHintedSample; do
  header="${AUTOGEN_DIR}/.rpp/interfaces/cpp/rpp_schema/rpp_testing/${sample}.hpp"
  if [[ ! -f "${header}" ]]; then
    echo "Missing generated fixture header: ${header}. Update rpp_common's test schemas." >&2
    exit 1
  fi
done

popd >/dev/null

echo "Precompiled RPP test fixture written to: ${AUTOGEN_DIR}"
