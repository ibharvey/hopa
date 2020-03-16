# hopa - Homogenized orientation using pairwise alignments

## Rationale
De novo sequence assembly and structural variant analyses can generate lists of sequences that are similar, but in arbitrary orientations. HOPA simply takes an input FASTA file and aligns each sequence (forward and reverse complement) against the first sequence in the list to determine the 'best' orientation of each sequence to the first and outputs this oriented file. 



## Installation
### With Docker (from source)
If you are using a Linux/Mac distribution and have a Docker daemon running, you can install with:
```
git clone --recursive https://github.com/ibharvey/hopa
cd hopa/dockerfiles
bash setup_alpine.sh
```
The benefit being that docker will pull all of the necessary dependencies into the separate container, giving you less of a headache.

To run hopa through the Docker image, use:
```
docker run hopa [options]
```

### With CMake (from source)
```
git clone --recursive https://github.com/ibharvey/hopa
cd hopa
mkdir -p build
cd build
cmake ..
make
sudo make install
```

HOPA requires Seqan3 and its respective dependencies. FYI this includes a fairly new compiler.

To run hopa following CMake installation, use either:
```
hopa [options]
#or
./hopa [options]
```
Depending on how you installed the program.
