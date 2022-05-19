#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

/**
 * _strncpy - Copy one string to another.
 * @dest: The first string and the destination.
 * @src: The second string.
 * @n: The number of byte to copy from src.
 * Return: dest + src[0 to n] in dest.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';
	return (dest);
}


/**
 * _strlen - Returns the length of a shell command line.
 * @s: The string whose the length will be returned.
 * @end: The terminating character.
 * Return: The length of s.
 */
int _strlen(char *s, char end)
{
	if (*s == end)
		return (0);
	else
		return (1 + _strlen(s + 1, end));
}


/**
 * _strcmp - Compare one string to another.
 * @s1: The first string and the destination.
 * @s2: The second string.
 * Return: -1 if s1 < s2
 *	  1 if s1 > s2
 *	  0 if s1 = s2
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, m = 0, n = 0, res = 0;

	for (i = 0; s1[i] != '\0'; i++)
		m += (int)s1[i++];
	for (i = 0; s2[i] != '\0'; i++)
		n += (int)s2[i++];
	if (m > n)
		res = -15;
	else if (m < n)
		res = 15;
	return (res);
}

/**
 * main - The program entry point
 * Return: always 0
 */
int main(void)
{
	char *newargv[] = {"", NULL};
	char *newenv[] = {"PATH=/bin/", NULL };
	char buf[256];
	char *cmd = NULL;
	int n;
	pid_t pid;

	while (1)
	{
		write(1, "($)", 3);
		fflush(stdin);
		if (read(2, buf, 256))
		{
			n = _strlen(buf, 10);
			cmd = malloc(n * sizeof(char));
			_strncpy(cmd, buf, n);
			pid = fork();
			if (pid)
			{
				wait(&pid);
			}
			else
			{
				newargv[0] = cmd;
				if (execve(cmd,  newargv, newenv) == -1)
				{
					fflush(stderr);
					perror("Command: ");
				}
				exit(0);
			}
		}
		else
		{
			exit(0);
		}
	}
	free(buf);
	return (0);
}
