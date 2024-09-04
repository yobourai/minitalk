int ft_power(unsigned int k, unsigned int n)
{
    if (n == 0)
        return 1;
    if (k == 0)
        return 0; 

    int result = 1;            // 5 3
								// 3 
    while (n > 0) // 1
    {
        if (n % 2 == 1) //true  
            result *= k; // result == 45
        k *= k; // 9
        n/= 2; // 1
    }
    return result;
}
int main()
{
    printf("%d\n", ft_power(2,5));
}
