# Connect4 in C 
> by Sharp - 1st Year of Master's in Computer Security

## Requirements :

* Linux Environment or an IDE,
* C Environment with gcc compiler,
* libreadline-dev (```sudo apt-get install libreadline-dev``` on Linux)

## How to build the program ?

1. Open the .tar.gz archive in CLI :
    ```tar -xzvf connect4.tar.gz```

2. Go on the directory where the program is via CLI :
    ```cd {your_environment}/connect4/src/```

Don't forget to compile the files of this program before running !

3. C Compiler :
    ```gcc -Wall -o connect4 connect4.c grid.c check.c -l readline```

4. Run the program and start playing! :
    ```./connect4```
