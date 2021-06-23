
# EE Jet Analysis Code

## Installation

### Prerequisites

To start running, you will need a few things

1. CERN `ROOT` with `RooFit` enabled
   - we need to link to it
   - make sure `root-config` is in `PATH` variable
1. fastjet
   - go to fastjet.fr and install it somewhere!
   - make sure `fastjet-config` is in `PATH` variable
1. helper codes
   - go clone this https://github.com/FHead/fheadhelpercode somewhere
1. (optional) `pythia8` installation


### CompileRootMacro script

The script itself is in the `fheadhelpercode/RootMacros` directory

First make sure this script is in your `PATH` variable, then modify it to use the correct flags, directories, etc

You can see a bunch of `if/else` statement, add one for your machine and modify accordingly


### Compile stuff

Go to fheadhelpercode/RootMacros/Code and do 

```shell
bash Compile
```

Then come back here and go into `CommonCode`.  And do

```shell
make
```


## Samples

Then you need a bunch of samples.

Make a `Samples` folder and put the corresponding files as follows

```
Samples/
   ALEPH/
      *.root
   ALEPHMC/
      *.root
   HERWIG7/
      run_00/
         *.root
      run_01/
         *.root
      ...
   HERWIG715/
      run_00/
         *.root
      ...
   SHERPA/
      run_00/
         *.root
      ...
```

And then copy the `PurePythia91.root` into `MCStudies/23417_PythiaWholeEvent/` folder.  (or generate it with `make RunPythiaOnShell` if you have `pythia8` installed)

Ask Yi where to find the root files

