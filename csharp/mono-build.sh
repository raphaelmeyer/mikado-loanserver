#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
build_dir="${script_dir}/build"
source_dir="${script_dir}/LoanServer"

mkdir -p ${build_dir}
cd ${build_dir}

mcs -out:LoanServer.exe \
    -r:System.Web.Http \
    -r:System.Net.Http \
    -r:System.Json \
    -r:System.Runtime.Serialization \
    ${source_dir}/*.cs

