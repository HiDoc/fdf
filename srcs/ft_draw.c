/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:12:34 by fmadura           #+#    #+#             */
/*   Updated: 2018/01/02 18:19:44 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_pix_put(t_grid *grid, t_point *point, int xmod, int ymod)
{
	mlx_pixel_put(grid->mlx,
			grid->win,
			point->x + xmod,
			point->y + ymod,
			point->color);
}
#include <stdio.h>
/**
  static void ft_draw_notflat(t_grid *grid, int x, int y)
  {
  int AB;
  int AC;
  int BC;
  int i;
  int j;

  i = 2;
  t_point *A = grid->grid[y][x];
  t_point *B = grid->grid[y][x + 1];
  t_point *C = grid->grid[y + 1][x + 1];
  t_point *D = grid->grid[y + 1][x];
  AC = ft_distance(A,C);
  AB = ft_distance(A, B);
  BC = ft_distance(B, C);
  int maxx = (C->x - B->x > B->x - A->x) ? C->x - B->x : B->x - A->x;
  int maxy = (C->y - B->y > B->y - A->y) ? C->y - B->y : B->y - A->y;
  printf("max x : %d, max y : %d \n", maxx, maxy);
  while (i + 1 < maxx)
  {
  j = 2;
  while (j + 1 < maxy)
  {
  if (A->y == C->y && i >= j)
  ft_pix_put(grid, grid->grid[y][x], i + (j / (AB / RES)), j - i);
  else if (A->y < C->y && B->z > C->z && A->z == B->z && i >= j / (AC / RES))
  ft_pix_put(grid, grid->grid[y][x], i + (j / (AC / RES)), j);
  else if (A->y < C->y && B->z == C->z && A->z == B->z && i >= j && D->z == A->z)
  ft_pix_put(grid, grid->grid[y][x], i + j, j);
  else if (A->y < C->y && B->z > C->z && A->z == C->z && i >= j / (BC / RES))
  ft_pix_put(grid, grid->grid[y][x], i + 1 + j / (BC / RES), j - i * (AB / RES));
  j++;
  }
  i++;
  }
  }

  static void ft_draw_notflat2(t_grid *grid, int x, int y)
  {
  int AB;
  int BC;
  int i;
  int j;

  i = 2;
  AB = ft_distance(grid->grid[y][x], grid->grid[y + 1][x]);
  BC = ft_distance(grid->grid[y + 1][x], grid->grid[y + 1][x + 1]);
  t_point *A = grid->grid[y][x];
  t_point *B = grid->grid[y + 1][x];
  t_point *C = grid->grid[y + 1][x + 1];
  int AC = ft_distance(A,C);
  int maxx = (C->x - B->x > B->x - A->x) ? C->x - B->x : B->x - A->x;
  int maxy = (C->y - B->y > B->y - A->y) ? C->y - B->y : B->y - A->y;
  while (i + 1 < maxx)
  {
  j = 2;
  while (j + 1 < maxy)
  {
  if (A->y == C->y && i < j)
  ft_pix_put(grid, grid->grid[y][x], i + (j / (AB / RES)), j - i);
  else if (A->y != C->y && B->y == C->y && i < j && A->z == B->z)
  ft_pix_put(grid, grid->grid[y][x], i + (j / (AB / RES)), j);
  else if (A->y != C->y && B->y == C->y && i < j / (AC / RES) && A->z != B->z)
  ft_pix_put(grid, grid->grid[y][x], i + (j / (AB / RES)), j);
  j++;
  }
  i++;
  }
  }**/
static int	ft_get_maxy(t_point *A, t_point *B, t_point *C, t_point *D)
{
	int maxy;

	maxy = 0;
	if (A->z == B->z && C->z == D->z)
		maxy = D->y - A->y;
	else if (A->z == D->z && B->z == C->z && A->z < B->z)
		maxy = A->y - B->y;
	else if (A->z == D->z && A->z == B->z && A->z != C->z)
		maxy = D->y - C->y;
	else if (B->z == D->z && C->z == B->z && A->z != C->z)
		maxy = D->y - A->y;
	else if (A->z == B->z && B->z == C->z && D->z < A->z)
		maxy = D->y - B->y;
	else if (C->z == D->z && C->z == A->z && B->z > A->z)
		maxy = D->y - B->y;
	else if (B->z == D->z && B->z == A->z && A->z > C->z)
		maxy = C->y - B->y;
	else if (B->z == D->z && B->z == C->z && A->z < C->z)
		maxy = A->y - B->y;
	return (maxy);
}
static int	ft_get_pas(t_point *A, t_point *B, t_point *C, t_point *D)
{
	int pas;

	pas = 1;
	if (A->z == B->z && A->z == C->z && A->z > D->z)
		pas = ft_distance(A, D);
	else if (A->z == B->z && A->z == D->z && A->z > C->z)
		pas = ft_distance(A, C);
	else if (A->z == B->z && A->z == D->z && A->z < C->z)
		pas = ft_distance(B, C);
	else if (A->z == C->z && A->z == D->z && A->z < B->z)
		pas = ft_distance(A, B);
	else if (B->z == C->z && B->z == D->z && A->z < C->z)
		pas = ft_distance(A, C);
	else if (A->z == B->z && C->z == D->z)
		pas = ft_distance(A, D);
	else if (B->z == C->z && B->z == D->z && A->z != C->z)
		pas = ft_distance(A, C);
	else if (A->z == D->z && B->z == C->z && A->z < B->z)
		pas = ft_distance(A, B);
	return (pas);
}
static void ft_draw_flat(t_grid *grid, int x, int y)
{
	t_point *A = grid->grid[y][x];
	t_point *B = grid->grid[y][x + 1];
	t_point *C = grid->grid[y + 1][x + 1];
	t_point *D = grid->grid[y + 1][x];
	int i;
	int j;
	int pas;
	int maxx = B->x - A->x;
	int maxy;
	pas = ft_get_pas(A, B, C, D);
	maxy = ft_get_maxy(A, B, C, D);
	i = 0;
	if (A->z == B->z && C->z == D->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				ft_pix_put(grid, A, i + j / (pas /RES), j);
				j++;
			}
			i++;
		}
	}
	i = 0;
	if (A->z == D->z && B->z == C->z && A->z < B->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				ft_pix_put(grid, B, i - j / (pas / RES), j + i);
				if (maxy % maxx == 0)
					ft_pix_put(grid, B, i - j / (pas / RES), j + i + 1);
				j++;
			}
			i++;
		}
	}
	i = 0;
	if (A->z == D->z && A->z == B->z && A->z != C->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				if (i >= j / (pas / RES))
				{
					ft_pix_put(grid, A, i + j / (pas / RES), -j + i);
					if (maxy % maxx == 0)
						ft_pix_put(grid, A, i + j / (pas / RES), -j + i + 1);
				}
				j++;
			}
			i++;
		}
	}
	i = 0;
	if (B->z == D->z && C->z == B->z && A->z != C->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				if (i <= j / (pas / RES))
					ft_pix_put(grid, A, i + j / (pas / RES), j);
				j++;
			}
			i++;
		}
	}
	i = 0;
	if (A->z == B->z && B->z == C->z && D->z < A->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				if (i > (j / (pas / RES)))
					ft_pix_put(grid, A, i, j);
				if (i + j / (pas / RES) < RES)
					ft_pix_put(grid, B, i, j + i);
				j++;
			}
			i++;
		}
	}
	i = 0;
	if (C->z == D->z && C->z == A->z && B->z > A->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				if (i + (j / (pas / RES)) < RES)
				{
					ft_pix_put(grid, A, i + (j / (pas / RES)), i - j);
					if (maxy % maxx == 0)
						ft_pix_put(grid, A, i + (j / (pas / RES)), i - j + 1);
					ft_pix_put(grid, D, i, -j);
				}
				j++;
			}
			i++;
		}
	}
	i = 0;
	if (B->z == D->z && B->z == A->z && A->z > C->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				if (i > (j / (pas / RES)))
					ft_pix_put(grid, A, i + j / (pas / RES) , j);
				j++;
			}
			i++;
		}
	}
	i = 0;
	if (B->z == D->z && B->z == C->z && A->z < C->z)
	{
		while (i < maxx)
		{
			j = 0;
			while (j < maxy)
			{
				if (i < (j / (pas / RES)))
				{
					if (maxy % maxx == 0)
						ft_pix_put(grid, A, i + j / (pas / RES), -j + i + 1);
					ft_pix_put(grid, A, i + j / (pas / RES), -j + i);
				}
				j++;
			}
			i++;
		}
	}
}
static void ft_draw_line_one(t_grid *grid, t_point *p1, t_point *p2, int dir)
{
	int i;
	int pas;
	int cmp;

	i = 0;
	cmp = p1->z - p2->z;
	pas = ft_distance(p1, p2) / RES;
	while (i / pas < RES)
	{
		if (!(cmp))
			ft_pix_put(grid, p1, i / pas, dir ? i : 0);
		else
			ft_pix_put(grid, p1, i / pas, cmp > 0 ? i : (dir ? 0 : -i));
		i++;
	}
}

int			ft_draw_lines(t_grid *grid)
{
	int		y;
	int		x;

	y = 0;
	while (y < grid->size_y)
	{
		x = 0;
		while (x < grid->size_x)
		{
			if (x + 1 < grid->size_x)
				ft_draw_line_one(grid, grid->grid[y][x], grid->grid[y][x + 1], 0);
			if (y + 1 < grid->size_y)
				ft_draw_line_one(grid, grid->grid[y][x], grid->grid[y + 1][x], 1);
			if (y + 1 < grid->size_y && x + 1 < grid->size_x)
			{
				ft_draw_flat(grid, x, y);
				//ft_draw_notflat(grid, x, y);
				//ft_draw_notflat2(grid, x, y);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int			ft_draw(char *file)
{
	t_grid	*grid;

	if ((grid = (ft_read(file))) == NULL)
		return (0);
	ft_draw_lines(grid);
	mlx_loop(grid->mlx);
	return (1);
}
