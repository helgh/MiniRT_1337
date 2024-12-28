
void	transpose_matrix(double **a2)
{
	double	tmp[4][4];
	int		i;
	int		s;

	i = -1;
	while (++i < 4)
	{
		s = -1;
		while (++s < 4)
			tmp[i][s] = a2[i][s];
	}
	i = -1;
	while (++i < 4)
	{
		s = -1;
		while (++s < 4)
			a2[s][i] = tmp[i][s];
	}
}

double	**inverse(double **a)
{
	int		row;
	int		col;
	double	**a2;
	double	determinant;

	determinant = det(a);
	if (determinant == 0)
		return (NULL);
	a2 = malloc(sizeof(double *) * count_size(a) + 1);
	if (!a2)
		return (NULL);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		a2[row] = malloc(sizeof(double) * 4);
		while (++col < 4)
			a2[row][col] = cofactor(a, row, col) / determinant;
	}
	a2[row] = NULL;
	transpose_matrix(a2);
	return (a2);
}
