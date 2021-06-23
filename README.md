
# EE Jet Analysis Code

## Installation

### Prerequisites

To start running, you will need a few things

1. CERN ROOT with RooFit enabled
   - we need to link to it
   - make sure root-config is in PATH variable
1. fastjet
   - go to fastjet.fr and install it!
   - make sure fastjet-config is in PATH variable
1. helper codes
   - go clone this https://github.com/FHead/fheadhelpercode somewhere
1. (optional) pythia8 installation


### CompileRootMacro script

The script itself is in the fheadhelpercode/RootMacros directory

First make sure this script is in your PATH variable, then modify it to use the correct flags, directories, etc

You can see a bunch of if/else statement, add one for your machine and modify accordingly


### Compile stuff

Go to fheadhelpercode/RootMacros/Code and do 

```shell
bash Compile
```

Then come back here and go into `CommonCode`.  And do

```shell
make
```





