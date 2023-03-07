![github repo badge: Language](https://img.shields.io/badge/Language-C-181717?color=blue) ![github repo badge: Testing](https://img.shields.io/badge/Testing-Criterion-181717?color=orange) ![github repo badge: OS](https://img.shields.io/badge/OS-Unix-181717?color=yellow) [![test](https://github.com/daminals/Fliki/actions/workflows/test.yml/badge.svg)](https://github.com/daminals/fliki/actions/workflows/test.yml)
# Fliki

fliki is a command line function that reads a diff file and an input file from stdin, and applies a patch using the diff file to read the new output to stdout. The function is based on the "patch" utility, and is written in C.

> a diff file is a difference file, or a file specifying the differences between two files. You can create your own diff file by running the linux function ```diff file1 file2``` in your terminal

It uses an "On-the-fly" operation style, where files are processed character by character. It breaks up the diff files into 'hunks', or sections of the diff file characterized by a change mode, append mode, and delete mode.

It processes hunks through their headers in `hunk_next`. Then the hunk is looped through with `hunk_getc`, which returns the proper character to append or delete in the output file, and returns EOS (end of section) when a hunk is completed. Lastly, `patch` is designated as the function which will take in a diff and input file and print the appropriate characters to the output, successfully applying all changes defined in the diff file to the input. 

Argument validity is checked in the `valid_args` function, and reads the three flags accepted by fliki, -h (help), -q (quiet mode | no errors printed), -n (no patch mode | dry run of program without writing to stdout)

## Installation

To use Fliki, you will need to have C installed on your computer. You can download the source code from the GitHub repository, or you can clone the repository using the following command:

```bash
git clone https://github.com/daminals/fliki.git
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
