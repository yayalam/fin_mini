#include "../minishell.h"

void	cd_dir_change_in_env(t_all_env *env, char *cwd, char *owd)
{
	t_env_one_element	*elem;

	elem = search_element_struct_env(env, "PWD");
	if (!elem)
		return ;
	elem->value = ft_strdup(cwd);
	elem = search_element_struct_env(env, "OLDPWD");
	if (!elem)
		return ;
	elem->value = ft_strdup(owd);
}
