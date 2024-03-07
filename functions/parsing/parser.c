/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:55:20 by thenwood          #+#    #+#             */
/*   Updated: 2024/03/07 17:43:04 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void add_cmd_cmd(t_node *info, t_cmd **head) {
    // Vérifier si le contenu est déjà alloué
    if (*head == NULL || (*head)->words == NULL) {
        // Si c'est la première commande ou si la commande précédente a été terminée
        // Allouer de la mémoire pour la nouvelle commande
        t_cmd *new_cmd = malloc(sizeof(t_cmd));
        if (!new_cmd) {
            fprintf(stderr, "Erreur nouveau nœud.\n");
            exit(EXIT_FAILURE);
        }

        // Initialiser la liste de mots de la nouvelle commande
        new_cmd->words = NULL;
        new_cmd->next = NULL;

        // Ajouter le nouveau nœud à la fin de la liste
        if (*head == NULL) {
            *head = new_cmd;
        } else {
            t_cmd *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_cmd;
        }

        // Mettre à jour le pointeur vers le dernier nœud de commande
        *head = new_cmd;
        
    }

    // Créer un nouveau mot de commande
    t_cmd_word *new_word = malloc(sizeof(t_cmd_word));
    if (!new_word) {
        fprintf(stderr, "Erreur mot de commande.\n");
        exit(EXIT_FAILURE);
    }

    // Remplir les champs du mot
    new_word->content = malloc(info->len + 1);
    strncpy(new_word->content, info->content, info->len);
    new_word->content[info->len] = '\0';
    new_word->type = info->type;
    new_word->state = info->state;
    new_word->next = NULL;

    // Ajouter le mot à la liste des mots de la commande
    if ((*head)->words == NULL) {
        (*head)->words = new_word;
    } else {
        t_cmd_word *current = (*head)->words;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_word;
    }
} */


void add_cmd_cmd(t_node *info, t_cmd **head) {
    // Vérifier si le contenu est déjà alloué
    if (*head == NULL) {
        // Si c'est la première commande, allouer de la mémoire pour la nouvelle commande
        t_cmd *new_cmd = malloc(sizeof(t_cmd));
        if (!new_cmd) {
            fprintf(stderr, "Erreur lors de l'allocation mémoire pour la nouvelle commande.\n");
            exit(EXIT_FAILURE);
        }
        new_cmd->words = NULL;
        new_cmd->next = NULL;
        *head = new_cmd;
    }
    
    // Créer un nouveau mot de commande
    t_cmd_word *new_word = malloc(sizeof(t_cmd_word));
    if (!new_word) {
        fprintf(stderr, "Erreur lors de l'allocation mémoire pour le nouveau mot de commande.\n");
        exit(EXIT_FAILURE);
    }

    // Remplir les champs du mot
    new_word->content = malloc(info->len + 1);
    strncpy(new_word->content, info->content, info->len);
    new_word->content[info->len] = '\0';
    new_word->type = info->type;
    new_word->state = info->state;
    new_word->next = NULL;

    // Ajouter le mot à la liste des mots de la commande
    if ((*head)->words == NULL) {
        (*head)->words = new_word;
    } else {
        t_cmd_word *current = (*head)->words;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_word;
    }
}


void print_cmd_list(t_cmd *head) {
    t_cmd *current = head;
    int i = 0;

    while (current) {
        t_cmd_word *word = current->words;
        printf("CMD[%d]:\n", i);
        while (word) {
            printf("Content: %s, Type: %d, State: %d\n", word->content, word->type, word->state);
            word = word->next;
        }
        i++;
        current = current->next;
        printf("\n");
    }
}

t_cmd *parser(t_stack *lst) {
    t_cmd *cmd = NULL; // Pointeur vers la première commande
    t_cmd *current_cmd = NULL; // Pointeur vers la commande en cours

    // Parcourir la pile
    t_node *current_node = lst->head;
    while (current_node) {
        // Si le type de noeud n'est pas PIPE_LINE, ajouter le mot à la commande courante
        if (current_node->type != PIPE_LINE) {
            if (!current_cmd) {
                // Si c'est la première commande, créer une nouvelle commande
                t_cmd *new_cmd = malloc(sizeof(t_cmd));
                if (!new_cmd) {
                    fprintf(stderr, "Erreur commande.\n");
                    exit(EXIT_FAILURE);
                }
                new_cmd->words = NULL;
                new_cmd->next = NULL;
                current_cmd = new_cmd;
                if (!cmd) {
                    // Si c'est également la première commande de toutes, mettre à jour cmd
                    cmd = current_cmd;
                }
            }
            // Ajouter le mot à la commande courante
            add_cmd_cmd(current_node, &current_cmd);
        } else {
            // Si c'est un PIPE_LINE, créer une nouvelle commande et passer à celle-ci
            t_cmd *new_cmd = malloc(sizeof(t_cmd));
            if (!new_cmd) {
                fprintf(stderr, "Erreur commande.\n");
                exit(EXIT_FAILURE);
            }
            new_cmd->words = NULL;
            new_cmd->next = NULL;
            if (!cmd) {
                cmd = new_cmd;
            }
            if (current_cmd) {
                current_cmd->next = new_cmd;
            }
            current_cmd = new_cmd;
        }
        current_node = current_node->next;
    }
    /* print_cmd_list(cmd);
    redirection_out(cmd); */
    return cmd;
}






