void	ft_error(char *name_of_program, char *error_msg, int exit_no)
{
	ft_putstr_fd(name_of_program, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error_msg, 2);
	exit(exit_no);
}
