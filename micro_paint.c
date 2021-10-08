#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void 	print_fd(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

char	**make_tab(char **tab, int width, int height, char background_char)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		tab[i] = malloc(sizeof(char) * width + 1);
		if (tab[i] == NULL)
			return (NULL);
		while (j < width)
		{
			tab[i][j] = background_char;
			j++;
		}
		i++;
	}
	return (tab);
}

void 	print_tab(char **tab, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

void 	free_tab(char **tab, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void 	perimeter_rectangle(char **tab, float x, float y, float width_rect, float height_rect, char form_char, int width, int height)
{
	int i;
	int j;

	j = (int)x;
	i = (int)y;
	while (j < (int)x + width_rect - 1 && j < width)
	{
		tab[i][j] = form_char;
		j++;
	}
	while (i < (int)y + height_rect && i < height)
	{
		tab[i][(int)x] = form_char;
		tab[i][(int)x + (int)width_rect - 1] = form_char;
		i++;
	}
	if (i < height)
	{
		j = (int)x;
		while (j < (int)x + width_rect && j < width)
		{
			tab[i - 1][j] = form_char;
			j++;
		}
	}
}

void 	area_rectangle(char **tab, float x, float y, float width_rect, float height_rect, char form_char, int width, int height)
{
	int i;
	int j;

	j = (int)x;
	i = (int)y;
	while (i < (int)y + height_rect && i < height)
	{
		j = (int)x;
		while (j < (int)x + width_rect && j < width)
		{
			tab[i][j] = form_char;
			j++;
		}
		i++;
	}
}

int		put_form_on_tab(char **tab, char form, float x, float y, float width_rect, float height_rect, char form_char, int width, int height)
{
	if (form == 'r')
	{
		perimeter_rectangle(tab, x, y, width_rect, height_rect, form_char, width, height);
	}
	if (form == 'R')
		area_rectangle(tab, x, y, width_rect, height_rect, form_char, width, height);
	else
		return (-1);
	return (0);
}

int main(int argc, char **argv)
{
	FILE *fd;
	int width;
	int height;
	char background_char;
	char form;
	float x;
	float y;
	float width_rect;
	float height_rect;
	char form_char;
	char **tab;

	if (argc != 2)
	{
		print_fd("Error: argument\n");
		return (-1);
	}
	fd = fopen(argv[1], "r");
	fscanf(fd, "%d %d %c %c %f %f %f %f %c", &width, &height, &background_char, &form, &x, &y, &width_rect, &height_rect, &form_char);
	if (width < 0 || height < 0 || width > 300 || height > 300)
		return (-1);
	tab = malloc(sizeof(char *) * height);
	if (tab == NULL)
		return (-1);
	make_tab(tab, width, height, background_char);
	print_tab(tab, height);
	put_form_on_tab(tab, form, x, y, width_rect, height_rect, form_char, width, height);
	print_tab(tab, height);
	free_tab(tab, width);
}
