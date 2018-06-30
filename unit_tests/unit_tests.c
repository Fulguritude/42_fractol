#include <stdlib.h>

#include "../fractol.h"

void			toggle_debug(t_control *ctrl)
{
	ctrl->debug = !(ctrl->debug);
}

void			exit_error(char *e_msg, int e_no)
{
	if (e_no == 0)
		write(1, e_msg, ft_strlen(e_msg));
	else
		perror(e_msg);
	exit(e_no);
}

int main()
{
	char	*str1;
	char	*str2;
	double 	test = 0.00001234;

	printf("%f  %e  %a\n", test, test, test);
	ft_asprintf(&str1, "%f  %e  %a", test, test, test);
	ft_asprintf(&str2, "%f  %e  %a", test, test, test);
	printf("%s\n", str1);
	printf("%s\n", str2);

	t_poly	real = str_to_poly(str1);
	t_cpoly	comp = str_to_cpoly(str2);
	free(str1);
	free(str2);
	printf("real and comp set\n");
	str1 = poly_to_str(&real);
	str2 = cpoly_to_str(&comp);
	printf("real and comp as strings:\n");
	printf("%s\n", str1);
	printf("%s\n", str2);
	free(str1);
	free(str2);

	return (0);
}
