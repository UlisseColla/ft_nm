/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:13:08 by ucolla            #+#    #+#             */
/*   Updated: 2025/11/26 19:40:01 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int ac, char **av) {
    
    /* if (ac != 2) {
        WRITE(ARGUMENTS_ERROR);
    } */

    int fd = open("./ft_nm.h", O_RDONLY, S_IWUSR | S_IRUSR);
    struct stat file_stat;
    
    if (fstat(fd, &file_stat) == -1) {
        perror("Couldn't get file size\n");
    }
    
    printf("File size is: %ld\n", file_stat.st_size);
    
    char *file_bytes = mmap(file_bytes, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_bytes == MAP_FAILED) {
        strerror(errno);
        return -1;
    }
    
    for(int i = 0; i < file_stat.st_size; i++) {
        printf("%c", file_bytes[i]);
    }
    printf("\n");

    return 0;
}