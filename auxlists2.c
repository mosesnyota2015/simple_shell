#include "main.h"

/**
 * addrvar_node - adds a variable at the end
 * of a rvars list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
rvars *addrvar_node(rvars **head, int lvar, char *val, int lval)
{
	rvars *new, *temp;

	new = malloc(sizeof(rvars));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

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
 * freervarlist - frees a rvars list
 * @head: head of the linked list.
 * Return: no return.
 */
void freervarlist(rvars **head)
{
	rvars *temp;
	rvars *curr;

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
