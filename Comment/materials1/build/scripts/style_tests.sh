#!/bin/bash

# Path to folders
script_dir="$(dirname ${BASH_SOURCE[0]})"
project_dir="${script_dir}/.."

python3 ${script_dir}/style_tests.py