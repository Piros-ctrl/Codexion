int is_solid_int(char *s)
{
    int i;
    if (!s || s[0] == '\0')
        return (1);
    i = 0;
    if ((s[i] == '-' || s[i] ==  '+') && (s[i + 1] != '\0'))
        i++;
    while (s[i])
    {
        if ((s[i] < '0' || s[i] > '9'))
            return 1;
        i++;
    }
    return 0;
}

long	ft_atoi(char *s)
{
    int		i;
	int		sign;
	long	result;
    
	i = 0;
	sign = 1;
	result = 0;

	if (is_solid_int(s))
        return 0;
	if (s[i] == '-' || s[i] == '+')
	{
        if (s[i] == '-')
            sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
        result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result * sign);
}

int is_itzero(char *str)
{
    long    num = ft_atoi(str);
    return (num == 0);
}

int is_positive(char *str)
{
    long    num = ft_atoi(str);
    return (num > 0);
}
int is_goe_to_zero(char *str)
{
    long    num = ft_atoi(str);
    return (num >= 0);
}
