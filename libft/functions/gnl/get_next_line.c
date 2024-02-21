/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenwood <thenwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:39:43 by thenwood          #+#    #+#             */
/*   Updated: 2023/12/07 13:13:46 by thenwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_rip(char *buff)
{
	free(buff);
	return (NULL);
}

/* Obtient une ligne depuis le buffer :
   détermine la longueur de la ligne, alloue la mémoire nécessaire,
   copie la ligne dans la mémoire allouée et 
   ajoute le caractère de fin de chaîne */
char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/* Obtient la prochaine ligne depuis le buffer :
   détermine la longueur de la ligne ou la fin du buffer,
   alloue la mémoire nécessaire, copie la ligne dans la mémoire allouée
   et ajoute le caractère de fin de chaîne + libère le buffer */
char	*ft_get_next_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_rip(buffer));
	line = malloc((ft_strlen_gnl(buffer) - i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	line[j] = '\0';
	free(buffer);
	return (line);
}

/* Lit un fichier ligne par ligne en utilisant un buffer
 pour stocker temporairement les données lues.
   Utilise read pour lire un bloc de données du fichier,
	gère les erreurs de lecture et concatène
   les blocs lus au fur et à mesure dans une variable 
   res en utilisant ft_strjoin */
void	*ft_read_file(int fd, char *res)
{
	char	*buffer;
	int		n_byte;

	if (!res)
	{
		res = malloc(1);
		if (res)
			res[0] = '\0';
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	n_byte = 1;
	while (n_byte > 0)
	{
		n_byte = read(fd, buffer, BUFFER_SIZE);
		if (n_byte == -1)
			return (ft_rip(buffer));
		buffer[n_byte] = '\0';
		res = ft_strjoin_gnl(res, buffer);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

/* Fonction principale qui gère le flux du fichier :
   appelle ft_read_file pour lire le fichier et 
   récupérer les données dans un buffer statique.
   Utilise ft_get_line pour obtenir la première ligne à partir du buffer,
   met à jour le buffer à l'aide de ft_get_next_line 
   pour pointer vers la prochaine ligne,
   puis retourne la ligne lue */
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_get_next_line(buffer);
	return (line);
}
