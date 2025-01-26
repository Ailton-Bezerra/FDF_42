/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:38:53 by ailbezer          #+#    #+#             */
/*   Updated: 2025/01/26 10:17:33 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_line(t_list *list)
{
	t_nod	*temp;
	t_nod	*new_node;
	char	*leftover;
	int		i;
	int		size;

	if (!list || !list->head)
		return ;
	temp = list->tail;
	leftover = temp->content;
	size = temp->length;
	temp->content = NULL;
	ft_lstclear(list);
	i = 0;
	if (leftover[size] != '\0')
	{
		while (leftover[size] != '\0')
			leftover[i++] = leftover[size++];
		leftover[i] = '\0';
		new_node = ft_new_node(leftover);
		ft_append(list, new_node);
	}
	else
		free(leftover);
	list->tail = list->head;
}

static void	ft_build_line(t_list *list, char **line)
{
	t_nod	*temp;
	int		line_size;
	int		i;

	line_size = list->line_size;
	*line = malloc(line_size + 1);
	if (!*line)
		return ;
	line_size = 0;
	temp = list->head;
	while (temp)
	{
		i = 0;
		while (temp->content[i] && i < temp->length)
			(*line)[line_size++] = temp->content[i++];
		temp = temp->next;
	}
	(*line)[line_size] = '\0';
}

static int	ft_check_newline(t_list *list)
{
	int	i;

	if (!list->head || !list->tail)
		return (0);
	i = 0;
	while (list->tail->content[i] != '\0')
	{
		if (list->tail->content[i] == '\n')
			return (list->line_size += list->tail->length = ++i, 1);
		i++;
	}
	return (list->line_size += list->tail->length = i, 0);
}

static void	ft_save_data(t_list *list, int fd)
{
	int		chars;
	t_nod	*new_node;

	while (!ft_check_newline(list))
	{
		new_node = ft_new_node(NULL);
		new_node->content = malloc(BUFFER_SIZE + 1);
		if (!new_node->content)
			return ;
		chars = read(fd, new_node->content, BUFFER_SIZE);
		if (chars <= 0)
		{
			free(new_node->content);
			free(new_node);
			if (chars == -1)
				ft_lstclear(list);
			return ;
		}
		new_node->content[chars] = '\0';
		ft_append(list, new_node);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	line = NULL;
	if (fd == -42)
	{
		ft_lstclear(list);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!list)
		list = ft_new_list();
	ft_save_data(list, fd);
	if (!list || !list->head)
		return (free(list), list = NULL, NULL);
	ft_build_line(list, &line);
	ft_free_line(list);
	return (line);
}
