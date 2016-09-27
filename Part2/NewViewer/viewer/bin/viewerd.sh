#! /bin/bash

export LD_LIBRARY_PATH=~/dades/G/Part2/NewViewer/viewer/bin/
export LC_NUMERIC="C"
export MAKEFLAGS=--quiet
export VIMAGE=firefox
export VEDITOR=gedit
export VTEXTURES=/assig/grau-g/Textures
export VMODELS=/assig/grau-g/models
export VTESTS=/assig/grau-g/tests
export VPLUGINS="libdraw-vbo-ext.so;librenderdefault.so;libnavigatedefault.so"

~/dades/G/Part2/NewViewer/viewer/bin/viewerd
