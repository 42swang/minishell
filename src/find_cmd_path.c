#include "../include/minishell.h"

char *find_cmd_path(char **arr, char *cmd)
{
	int i = 0;
	char *path;

	path = 0;
	while (arr[i])
	{
		// "bin/run/hello/ + world"
		path = ft_strjoin(arr[i], cmd);
	//	printf("		in find\n");
	//	printf("		test_path : {%s}\n", path);
		if (access(path, X_OK | F_OK) == 0) //내가만든 경로가 실행가능한 알맞은 경로인지
			return (path);
		free(path);
		path = 0;
		i++;
	}
	return (NULL);
}