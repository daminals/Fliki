![github repo badge: Language](https://img.shields.io/badge/Language-C-181717?color=blue) ![github repo badge: Testing](https://img.shields.io/badge/Testing-Criterion-181717?color=orange) ![github repo badge: OS](https://img.shields.io/badge/OS-Unix-181717?color=yellow)
# Fliki

Fliki is a command line function that reads a diff file and an input file from stdin, and applies a patch using the diff file to read the new output to stdout. The function is based on the Unix function "fliki" and is written in C.

## Installation

To use Fliki, you will need to have C installed on your computer. You can download the source code from the GitHub repository, or you can clone the repository using the following command:

```bash
git clone https://github.com/daminals/Fliki.git
```

Once you have downloaded or cloned the repository, navigate to the directory and run the following command to compile the code:

```bash
make all
```

This will create an executable file called "fliki". You can then run the program by typing:

```bash
./bin/fliki
```

## Usage

To use Fliki, you will need to provide a diff file and an input file. These files can be passed to the program using stdin.

Here is an example of how to use Fliki:

```bash
cat input.txt | fliki file.diff > output.out
```

This command will read the contents of the `input.txt` file, apply the patch contained in the `file.diff` file, and output the result to the `output.out` file.

## Testing

This project uses the Criterion testing framework.

Test cases can be run with 

```bash
make clean all && ./bin/fliki_tests
```

They are also attached to a github action and run as a CI/CD workflow upon every commit to ensure proper functionality.
