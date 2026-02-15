/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:13:08 by ucolla            #+#    #+#             */
/*   Updated: 2026/02/15 17:12:25 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int main(int ac, char **av) {

    Flags flags = {};
    t_list *files =  NULL;
    int status = 0;
    
    args_lexer(av, ac, &flags, &files);

    if (ft_lstsize(files) == 0) {
        file_info info = {};
        status = init_elf(&info, "./a.out");
        if (status == 1) return status;
    } else {
        t_list *cursor = files;
        while (cursor) {
            file_info info = {};
            status = init_elf(&info, cursor->content);
            if (status == 1) {
                cursor = cursor->next;
                continue;
            }
            
            status = ft_nm(&info, flags);
            if (cursor->next != NULL) write(1, "\n", 1);

            munmap(info.elf_file, info.file_size);
            cursor = cursor->next;
        }
    }
    
    clear_list(&files);
    return status;
}
