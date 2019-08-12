# 42img
A minimalist image loading libary written in Norminette C89

# Usage
```c
t_bitmap	*bmp; // Generic image type

bmp = img_load("test.bmp"); // Load from file
if (!bmp) // Might fail
	perror("Could not load 'test.bmp'");
```