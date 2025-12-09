/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucolla <ucolla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:15:55 by ucolla            #+#    #+#             */
/*   Updated: 2025/12/09 17:50:52 by ucolla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/** 
 * Handling flags 'a g u r p'
 * 
 * a: all symbols, even debugging ones      FILTER
 * g: only external ones                    FILTER
 * u: undefined only                        FILTER  
 * r: reverse sorting order                 SORTING
 * p: symbols not sorted                    SORTING
 * 
 * -u wins on -g, which wins on -a | u -> g -> a
 * -p wins on -r, which wins on no sorting flag | p -> r -> no flag
 * 
 * '--', or more dashes, trigger an error message and stop the execution of the command
 * multiple flags can be considered if concatenated, before, between or after files
 * same flag multiple times count as one flag of that type -> -uuuuu --> -u
 * 
 * !! no flag means the symbols must be sorted in alphabetical order !!
 */

void clear_list(t_list **list) {
    t_list *a;
    
    while (*list) {
        a = (*list)->next;
        free(*list);
        *list = a;
    }
}

void print_error_message(char *error) {
    ft_printf("nm: invalid option %s\n", error);
    ft_printf("%s", ARGUMENTS_ERROR);
}

bool set_flag_if_valid(char c, Flags *flags) {
    switch(c) {
        case 'a':
            if (flags->filter == DEFAULT) {
                flags->filter = ALL;
            }
            return true;
        case 'g':
            if (flags->filter != UNDEFINED) {
                flags->filter = EXTERNAL;
            }
            return true;
        case 'u':
            flags->filter = UNDEFINED;
            return true;
        case 'r':
            if (flags->sort != UNSORTED) {
                flags->sort = REVERSE;
            }
            return true;
        case 'p':
            flags->sort = UNSORTED;
            return true;
        default:
            return false;
    }
}

enum lexer_status is_flag(char *str, Flags *flags) {
    int i = 0;

    if (str[0] != '-') {
        return FILENAME;
    }

    while(str[i] == '-') {
        i++;
    }

    if (i > 2) {
        print_error_message(str);
        return ERROR;
    }

    while(str[i]) {
        if (!set_flag_if_valid(str[i], flags)) {
            print_error_message(&str[i]);
            return ERROR;
        }
        i++;
    }

    return OK;
}

t_list *args_lexer(char **av, int ac, Flags *flags) {
    t_list *head = NULL;
    t_list *new;

    for (int i = 1; i < ac; i++) {
        switch(is_flag(av[i], flags)) {
            case OK:
                break;
            case FILENAME:
                new = ft_lstnew(av[i]);
                if (head != NULL) {
                    ft_lstadd_front(&head, new);
                }
                break;
            case ERROR:
                if (head != NULL) {
                    clear_list(&head);
                }
                exit(1);
        }
    }

    return head;
}