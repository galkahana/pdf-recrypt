A CLI (command line interface) to Extract text from PDF files.
Use from your terminal to dump a PDF file text to the std output.
Options exists to output to file, choose pages range etc.

```bash
Usage: Recrypt inputfilepath outputfilepath <option(s)>
inputfilepath - input pdf file path
outputfilepath - output pdf file path
Options:
        -p, --password password               input pdf password (user or owner). Default is no password
        -v, --version <d>                     output pdf version. Use 10-17 for pdf1.0-pdf1.7. For AES use 16 or 17. Lower is RC4. Default is input pdf version
        -u, --user-password password          output pdf password (user password). Default is no password
        -o, --owner-password password         output pdf owner password. Default is no owner password password
        -f, --user-protection-flag <d>        output pdf user protection flag. Default is 4 (low res print)
        -h, --help                      Show this help message
```

# First time around

This is a C++ Project using CMake as project builder.
To build/develop You will need:

1. a compiler. for win you can use vs studio. choose community version - https://visualstudio.microsoft.com/
2. cmake - download from here - https://cmake.org/


# Building and Installing the project

Once you installed pre-reqs, you can now build the project.

## Create the project files

To build you project start by creating a project file in a "build" folder off of the cmake configuration, like this:

```bash
mkdir build
cd build
cmake ..
```

I won't go on about cmake here, you can check out their website. going forward i'll stick to describing the minimal set of commands
you can use for building and installing.


## Build and install

Once you got the project file, you can now build the project. If you created an IDE file, you can use the IDE file to build the project.
Alternatively you can do so from the command line, again using cmake. 

The following builds the project from its root folder:
```bash
cmake --build build --config release
```

This will build the project inside the build folder. You will be able to look up the result execultable per how you normally do when building with the relevant build environment. For example, for windows,  the Recrypt/Release folder will have the result file.

If you want, you can use the "install" verb of cmake to install a built product. Use the prefix param to specify where you want the result to be installed to

```bash
cmake --install ./build/Recrypt --prefix ./etc/install
```

This will install the Recrypt executable in ./etc/install.

if you do not have `cmake --install` as option, you can use a regular build with install target instead, and specify the install target in configuration stage, like this:

```bash
cd build
cmake .. -DCMAKE_INSTALL_PREFIX="..\etc\install"
cd ..

cmake --build build/Recrypt --config release --target install
```

# Running
The end result is an executable, so just run it from comman line (it's a regular cli).

The minimal run requires an input file path and output file path, say on windows:
```console
etc\install\bin\Recrypt.exe input.pdf output.pdf
```



# Features and implementation details
This implementation is based on hummus PDF library. It is a simple CLI implementation using the `PDFWriter::Recrypt` method. `Recrypt` copies an origin PDF file to a new PDF file by deep copying the original file Root object (the catalog). Given it's a completely new rewrite of the file, and how Hummus parses files, the created file has only PDF Objects actually used in the origin PDF. This means that if the original PDF is an modified PDF file the new file will not include any "documnation" of the midifications. This is very good for create PDF that's compatible with readers that cannot consume modified PDF files. Either user or owner passwords can be used to decrypt the new file, given that either of them provides full access to parse the PDF file, which is the only thing required to recreate a new file.

PDF provides and option to have both a "user" password and an "owner" password. In such a case, a user providing the "user" password will have a more limited access to the PDF file, like not being able to edit it, or print only a lower resolution of the file. If providing "owner" password full access is granted. To control what options are available when providing "user" password use the `--user-protection-flag` option. The flag is a bit field that’s explained in section 3.5.2 in the PDF specs. The short version is provided here:

bit 3 should be 1 if you want to allow the user to print the document
bit 4 should be 1 if you want to allow modification of the document
bit 5 should be 1 if you want to allow copying or extracting text and graphics from the document
bit 6 should be 1 if you want to allow adding text annotations, fill form field. If bit 4 is set it allows to create new fields. like a signature.
bit 9 should be 1 if you want to allow filling forms, even if bit 6 is clear.
bit 10 should be 1 if you want to allow extracting text and graphics in support of accessibility only, even if bit 5 is clear.
bit 11 should be 1 if you want to allow assembling the document. rotate, insert, delete pages, bookmarks and thumbnails.
bit 12 should be 1 if you want to allow printing the document in a good res. Setting just 3 will normally print a low res form.
A good choice for most cases is 4, which means only the low res print is allowed. This is the sort of a safe exchange scenario. Note that Hummus handles the rest of the unexplained fields and also the two complement part that the specs require - so you don’t have to. but it’s ok if you’ll pass a flag in this form too. if you must.
