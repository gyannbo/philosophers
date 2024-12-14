/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_overflow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:21:44 by gbonis            #+#    #+#             */
/*   Updated: 2024/08/26 20:32:49 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isspace(char s)
{
	if ((s >= 9 && s <= 13) || s == ' ')
		return (1);
	else
		return (0);
}

// be careful this function uses the fact that -INT_MIN = INT_MIN 
// car la valeur de -INT_MIN est INT_MAX + 1 donc overflow 
//
//BE CAREFUL NOT PROVIDING AN INT * FOR OVERFLOW WILL SEGFAULT

int	ft_atoi_overflow(const char *nptr, int *overflow)
{
	int	number;
	int	sign;

	number = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -sign;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57 && !(*overflow))
	{
		if (number == INT_MIN && *overflow == 0 && *nptr)
			*overflow = 1;
		if ((((number * 10) + *nptr - '0') < number)
			&& !(((((long)number * 10) + *nptr - '0') == 2147483648)
				&& sign == -1))
			*overflow = 1;
		number = (number * 10) + *nptr - '0';
		nptr++;
	}
	return (number * sign);
}

//int	main()
//{
//	int overflow = 0;
//	//const	char *s = "-214748364";
//	const	char *s = "-00077--0123-4-99-20002";
//
//	printf("%d\n", 	ft_atoi_overflow(s, &overflow));
//	printf("%d\n", 	atoi(s));
//	printf("%d\n", overflow);
//	return(0);
//}
//
//
//	test cases: 
//		trailing zeroes  : 000003
//		several '-' before number : ---45
