/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:31:11 by gpaeng            #+#    #+#             */
/*   Updated: 2021/01/13 15:31:13 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 2번째 문자열에서 각 문자를 저장해 놓은 뒤에
// 1번쨰 문자열에서 각 문자를 확인하는데 2번째 문자열에서 있었던 것을 출력하고 
// 해당 문자는 더이상 출력하지 않는다.

#include <unistd.h>

static void ft_putchar(char c)
{
    write(1, &c, 1);
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        int arr[256] = {0,};
        int idx = 0;

        while (argv[2][idx])
            arr[(int)argv[2][idx++]] = 1;
        idx = 0;
        while (argv[1][idx])
        {
            if (arr[(int)argv[1][idx]] == 1)
            {
                ft_putchar(argv[1][idx]);
                arr[(int)argv[1][idx]] = 0;
            }
            idx++;
        }
    }
    ft_putchar('\n');
    return (0);
}