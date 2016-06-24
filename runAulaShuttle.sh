#!/bin/bash
set -e
echo -e "\n" >> imove.log 2>&1
date >> imove.log 2>&1
./build/bin/imove ./config/AulaShuttle.yml ./config/sceneconfigAulaShuttle.yml >> imove.log 2>&1
