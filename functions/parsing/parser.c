/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:20 by thenwood          #+#    #+#             */
/*   Updated: 2024/02/24 19:03:31 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_cmd_cmd(t_node *info, t_cmd **head)
{
    // Vérifier si le contenu est déjà alloué
    if (*head == NULL || (*head)->content == NULL) {
        // Si c'est la première commande ou si la commande précédente a été terminée
        // Allouer de la mémoire pour la nouvelle commande
        t_cmd *new_node = malloc(sizeof(t_cmd));
        if (!new_node) {
            fprintf(stderr, "Erreur lors de l'allocation mémoire pour le nouveau nœud.\n");
            exit(EXIT_FAILURE);
        }

        new_node->content = malloc(info->len + 1);
        if (!new_node->content) {
            fprintf(stderr, "Erreur lors de l'allocation mémoire pour la commande.\n");
            exit(EXIT_FAILURE);
        }
        
        // Copier le contenu du token actuel
        strncpy(new_node->content, info->content, info->len);
        new_node->content[info->len] = '\0'; // Assurez-vous que la chaîne est correctement terminée
        new_node->next = NULL;

        // Ajouter le nouveau nœud à la fin de la liste
        if (*head == NULL) {
            *head = new_node;
        } else {
            t_cmd *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }

        // Mettre à jour le pointeur vers le dernier nœud de commande
        *head = new_node;
    } else {
        // Concaténer le contenu du token actuel à la commande existante
        // Recherchez la dernière commande dans la liste
        t_cmd *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }

        // Allouer de la mémoire pour la nouvelle taille de la commande
        size_t new_len = strlen(current->content) + info->len + 2; // +2 pour l'espace et le caractère nul
        current->content = realloc(current->content, new_len);
        if (!current->content) {
            fprintf(stderr, "Erreur lors de la réallocation mémoire pour la commande.\n");
            exit(EXIT_FAILURE);
        }

        // Concaténer le contenu du token actuel
        strncat(current->content, info->content, info->len);
    }
}

void	print_cmd_list(t_cmd *head)
{
	t_cmd	*current;
	int i = 0;

	current = head;
	while (current != NULL)
	{
		printf("CMD[%d] : '%s'\n", i,current->content);
		i++;
		current = current->next;
	}
}

void parser(t_stack *lst)
{
    t_cmd *cmd = NULL; // Pointeur de liste de commandes initialisé à NULL
    t_cmd *first_cmd = NULL; // Pointeur vers le premier nœud de commande
    t_node *current_node = lst->head; // Démarre à la tête de la pile

    while (current_node)
    {
        if (current_node->type != PIPE_LINE) {
            // Si le type de nœud n'est pas PIPE_LINE, ajoutez le contenu à la liste de commandes
            if (cmd == NULL) {
                // Si c'est la première commande, allouez de la mémoire pour la liste de commandes
                cmd = malloc(sizeof(t_cmd));
                if (!cmd) {
                    fprintf(stderr, "Erreur lors de l'allocation mémoire pour la liste de commandes.\n");
                    exit(EXIT_FAILURE);
                }
                cmd->content = NULL;
                cmd->next = NULL;
                first_cmd = cmd; // Mettez à jour le pointeur vers le premier nœud de commande
            }
            add_cmd_cmd(current_node, &cmd); // Ajoutez la commande à la liste de commandes
        } else {
            cmd = first_cmd; // Revenez au premier nœud de commande pour afficher toutes les commandes
        }
        current_node = current_node->next;
    }
    print_cmd_list(first_cmd); // Imprimez la liste des commandes après avoir terminé la boucle
}




