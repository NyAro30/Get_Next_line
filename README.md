*This project has been created as part of the 42 curriculum by mny-aro-.*

# 📖 Description
The Get Next Line project is a fundamental part of the 42 curriculum. The goal is to write a C function that reads a line ending with a newline character from a file descriptor.

This project taught me essential concepts in C programming:

- Static Variables: Understanding variable lifetime and scope to persist data between function calls.
- Dynamic Memory Management: Using malloc and free correctly to avoid memory leaks.
- File Descriptors: Interacting with the file system using the read function.
- Pointer Manipulation: Handling pointers and double pointers to manipulate strings efficiently.
# ⚙️ Algorithm Explanation

The function uses a static variable (stash) to retain leftover characters between successive calls. The algorithm works as follows:

- **Read Loop:** The function calls read() to fetch chunks of data of size BUFFER_SIZE into a temporary buffer.
- **Accumulation:** The content of the temporary buffer is appended to stash using a custom ft_strjoin.
- **Check for Newline:** A check is performed (ft_strchr) to see if stash contains a newline character.
- **Extraction:** If a newline is found, the line is extracted (ft_substr) up to that point. The remaining characters are saved back into stash for the next call.
- **Cleanup:** Memory is freed appropriately to prevent leaks.

# 🚀 Instructions
## Cloning the Repository

To evaluate this project, first clone the repository to your local machine using the following command:
```c
bash

git clone <repository_url> filename.
```
 
## Pre-compilation Checks 
Before compiling, please verify the following essential files are present in the directory: 
    Check Mandatory Files: 
    bash
```c
bash

    ls
	-> get_next_line.c get_next_line_utils.c get_next_line.h ... 
```
Expected output: The three filenames must be displayed.  
### Check File Structure:
Ensure there are no forbidden functions (like lseek) or global variables. You can quickly check for forbidden terms with grep: 	
```c
bash

    grep -r "lseek" .
    grep -r "get_next_line(int fd, char **line)" . # Check for bonus prototype if not doing bonus
```     

### Verify Buffer Size Definition:
Open `get_next_line.h` to confirm that `BUFFER_SIZE` has a default value defined (e.g., `#ifndef BUFFER_SIZE` block exists).  
## Compilation
To compile with a custom buffer size (for testing): 
```c
bash
 
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
``` 
 
 
#### Usage 

Call the function with a valid file descriptor: 
```c
c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error : Can't open the file\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Readed lign : %s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```
 
# 🔗 Resources

 - https://www.geeksforgeeks.org/c/variadic-functions-in-c/
 - https://www.geeksforgeeks.org/c/static-variables-in-c/    
AI Usage 

AI assistance was used in this project strictly for educational support: 

- Understanding Concepts: Explaining the role and behavior of static variables.
- Debugging Logic: Identifying issues with pointer arithmetic and memory leaks.
- Creating a README.md : Helping on the structure of the Readme file.

## Testing & Proof of Concept 

Below is a comprehensive main.c and a list of commands to prove the robustness of the implementation. 
The Main Test File (main.c) 

Save this code as main.c in your repository. It includes tests for files, standard input, and error handling. 
```c
 c
  
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void	test_file(const char *filename)
{
    int		fd;
    char	*line;

    printf("\n--- Testing File: %s ---\n", filename);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Could not open file.\n");
        return ;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line: %s", line);
        free(line);
    }
    close(fd);
    printf("\n--- End of File ---\n");
}

void	test_stdin(void)
{
    char	*line;

    printf("\n--- Testing Standard Input (stdin) ---\n");
    printf("Type something and press Enter (Ctrl+D to exit):\n");
    while ((line = get_next_line(STDIN_FILENO)) != NULL)
    {
        printf("Echo: %s", line);
        free(line);
    }
    printf("End of stdin test.\n");
}

void	test_invalid_fd(void)
{
    char	*line;

    printf("\n--- Testing Invalid FD (-1) ---\n");
    line = get_next_line(-1);
    if (line == NULL)
        printf("Correctly returned NULL for invalid FD.\n");
    else
    {
        printf("Error: Did not handle invalid FD correctly.\n");
        free(line);
    }
}

int	main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            test_file(argv[i]);
    }
    else
    {
        test_invalid_fd();
        test_stdin();
    }
    return (0);
}
 ```
 
 
### Commands to Validate the Project 

Run these commands in your terminal to prove the code handles all cases correctly. 

#### Create test files for different scenarios: 
```bash
bash
 
  
 
# A file with multiple lines
echo -e "Line 1\nLine 2\nLine 3" > test_normal.txt

# A file with newlines at the end (standard)
echo -e "Line A\nLine B" > test_nl_end.txt

# A file WITHOUT a newline at the very end
printf "Last line no NL" > test_no_nl.txt

# An empty file
touch empty.txt
``` 
 
 

#### Test Standard Compilation (BUFFER_SIZE=42): 
```bash
 

cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -g -o gnl_test
./gnl_test test_normal.txt test_no_nl.txt empty.txt

``` 

#### Test Torture (BUFFER_SIZE=1): 
```bash
bash
  
 
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -g -o gnl_test_b1
./gnl_test_b1 test_normal.txt

```

#### Test Huge Buffer (BUFFER_SIZE=999999): 
```bash
 bash
  
 
cc -Wall -Wextra -Werror -D BUFFER_SIZE=999999 get_next_line.c get_next_line_utils.c main.c -g -o gnl_test_big
./gnl_test_big test_normal.txt
```
 
 

#### Check for Memory Leaks (Valgrind):
Essential to prove you have 0 leaks. 
```bash
valgrind --leak-check=full ./gnl_test test_normal.txt
``` 