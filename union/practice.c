/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   practice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:31:18 by gpaeng            #+#    #+#             */
/*   Updated: 2021/01/13 16:20:42 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 1번째 2번째 순서대로 문자를 check합니다.
// 그리고 한번 나온 문자는 다시 출력하지 않습니다.

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

        while (argv[1][idx])
        {
            if (arr[(int)argv[1][idx]] == 0)
            {
                ft_putchar(argv[1][idx]);
                arr[(int)argv[1][idx]] = 1;
            }
            idx++;
        }
        idx = 0;
        while (argv[2][idx])
        {
            if (arr[(int)argv[2][idx]] == 0)
            {
                ft_putchar(argv[2][idx]);
                arr[(int)argv[2][idx]] = 1;
            }
            idx++;
        }
    }
    ft_putchar('\n');
}