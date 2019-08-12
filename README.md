# 42img ![build status](https://travis-ci.com/emiflake/42img.svg?token=j91nc4qbU7R8WZBqwW4m&branch=master)
A minimalist image loading libary written in Norminette C89

# Usage
```c
t_bitmap	*bmp; // Generic image type

bmp = img_load("test.bmp"); // Load from file
if (!bmp) // Might fail
	perror("Could not load 'test.bmp'");
```
