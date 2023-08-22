#include "main.h"

/**
 * add_sep_node_end - adds a separatr found at the end
 * of a seplists.
 * @head: head of the linked list.
 * @sep: separatr found (; | &).
 * Return: address of the head.
 */
seplists *add_sep_node_end(seplists **head, char sep)
{
	seplists *new, *temp;

	new = malloc(sizeof(seplists));
	if (new == NULL)
		return (NULL);

	new->separatr = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_seplists - frees a seplists
 * @head: head of the linked list.
 * Return: no return.
 */
void free_seplists(seplists **head)
{
	seplists *temp;
	seplists *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a cmd_lines_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
cmd_lines_list *add_line_node_end(cmd_lines_list **head, char *line)
{
	cmd_lines_list *new, *temp;

	new = malloc(sizeof(cmd_lines_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_cmd_lines_list - frees a cmd_lines_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_cmd_lines_list(cmd_lines_list **head)
{
	cmd_lines_list *temp;
	cmd_lines_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
