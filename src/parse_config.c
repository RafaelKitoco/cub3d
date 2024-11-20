#include "./headers/cub3d.h"

static void pad_lines_with_spaces(char **lines, int max_length) {
    for (int i = 0; lines[i]; i++) {
        int len = strlen(lines[i]);
        if (len < max_length) {
            char *padded_line = malloc(max_length + 1);
            if (!padded_line) {
                fprintf(stderr, "Error: Failed to allocate memory for padded line.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(padded_line, lines[i]);
            for (int j = len; j < max_length; j++) {
                padded_line[j] = ' ';
            }
            padded_line[max_length] = '\0';
            //free(lines[i]);
            lines[i] = padded_line;
        }
    }
}

int	first_line(char *str)
{
	if (str[0] == '1')
	{
		return (1);
	}
	return (0);
}

static void sanitize_map_lines(char **lines) {
    for (int i = 0; lines[i]; i++) {
        // Remover espaços e tabulações do início
        while (lines[i][0] == ' ' || lines[i][0] == '\t') {
            memmove(lines[i], lines[i] + 1, strlen(lines[i]));
        }
        
        // Remover espaços e tabulações do final
        int len = strlen(lines[i]);
        while (len > 0 && (lines[i][len - 1] == ' ' || lines[i][len - 1] == '\t')) {
            lines[i][--len] = '\0';
        }
    }
}


static char **ft_split(char *str, char delimiter) {
    int i = 0, j = 0, k = 0, count = 1;
    while (str[i]) {
        if (str[i] == delimiter)
            count++;
        i++;
    }

    char **result = malloc((count + 1) * sizeof(char *));
    result[count] = NULL;

    for (i = 0; i < count; i++) {
        result[i] = malloc(256);
        j = 0;
        while (str[k] && str[k] != delimiter)
            result[i][j++] = str[k++];
        result[i][j] = '\0';
        k++;
    }

    return result;
}

static void parse_color(const char *str, int *color) {
    char **colors = ft_split((char *)str, ',');
    if (colors) {
        color[0] = atoi(colors[0]);
        color[1] = atoi(colors[1]);
        color[2] = atoi(colors[2]);

        for (int i = 0; colors[i] != NULL; i++) {
            free(colors[i]);
        }
        free(colors);
    }
}

static void calculate_map_size(char **lines, int *width, int *height) {
    *height = 0;
    *width = 0;
    for (int i = 0; lines[i] != NULL; i++) {
        if (strchr(lines[i], '1')) {
            (*height)++;
            int line_length = strlen(lines[i]);
            if (line_length > *width) {
                *width = line_length;
            }
        }
    }
}

int	find_firts(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

static void parse_map(char **lines, t_vars *vars, int start) {
    vars->map.worldMap = malloc(vars->map.height * sizeof(int *));
    if (!vars->map.worldMap) {
        fprintf(stderr, "Error: Failed to allocate memory for map.\n");
        exit(EXIT_FAILURE);
    }

    int playerCount = 0;
    for (int i = 0; i < vars->map.height; i++) {
        vars->map.worldMap[i] = malloc(vars->map.width * sizeof(int));
        if (!vars->map.worldMap[i]) {
            fprintf(stderr, "Error: Failed to allocate memory for map row.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < vars->map.width; j++) {
            if (lines[start + i][j] == ' ') {
                vars->map.worldMap[i][j] = -1;
            } else if (lines[start + i][j] == '1') {
                vars->map.worldMap[i][j] = 1;
            } else if (lines[start + i][j] == '0') {
                vars->map.worldMap[i][j] = 0;
            } else if (find_firts(lines[start + i][j])) {
                vars->player.posX = i + 0.5;
                vars->player.posY = j + 0.5;
                if (lines[start + i][j] == 'N') {
                    vars->player.dirX = -1; 
                    vars->player.dirY = 0; 
                    vars->player.planeX = 0; 
                    vars->player.planeY = 0.66;
                } else if (lines[start + i][j] == 'S') {
                    vars->player.dirX = 1;
                    vars->player.dirY = 0;
                    vars->player.planeX = 0;
                    vars->player.planeY = -0.66;
                } else if (lines[start + i][j] == 'E') {
                    vars->player.dirX = 0;
                    vars->player.dirY = 1;
                    vars->player.planeX = 0.66;
                    vars->player.planeY = 0;
                } else if (lines[start + i][j] == 'W') {
                    vars->player.dirX = 0;
                    vars->player.dirY = -1;
                    vars->player.planeX = -0.66;
                    vars->player.planeY = 0;
                }
                // Certifique-se de não marcar a célula como 2, mantenha-a como '0' para permitir a movimentação
                vars->map.worldMap[i][j] = 0;
                playerCount++;
            }
        }
    }

    if (playerCount != 1) {
        fprintf(stderr, "Error: Mapa deve ter exatamente uma posição inicial do jogador.\n");
        exit(EXIT_FAILURE);
    }
}


static int is_map_closed(t_vars *vars)
{ 
    for (int i = 0; i < vars->map.height; i++) 
    { 
        for (int j = 0; j < vars->map.width; j++)
        { 
            if (vars->map.worldMap[i][j] == 0 || strchr("NSEW", vars->map.worldMap[i][j]))
            { 
                if (i == 0 || i == vars->map.height - 1 || j == 0 || j == vars->map.width - 1 || vars->map.worldMap[i-1][j] == ' ' || vars->map.worldMap[i+1][j] == ' ' || vars->map.worldMap[i][j-1] == ' ' || vars->map.worldMap[i][j+1] == ' ')
                {
                    return 0;
                } 
            }
        }
    } 
    return 1; 
}

static void parse_line(t_vars *vars, char *line) {
    if (strncmp(line, "NO ", 3) == 0)
        vars->no_texture = ft_strdup(&line[3]);
    else if (strncmp(line, "SO ", 3) == 0)
        vars->so_texture = ft_strdup(&line[3]);
    else if (strncmp(line, "WE ", 3) == 0)
        vars->we_texture = ft_strdup(&line[3]);
    else if (strncmp(line, "EA ", 3) == 0)
        vars->ea_texture = ft_strdup(&line[3]);
    else if (strncmp(line, "F ", 2) == 0)
        parse_color(&line[2], vars->floor_color);
    else if (strncmp(line, "C ", 2) == 0)
        parse_color(&line[2], vars->ceiling_color);
}

void parse_config(char *path, t_vars *vars) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char buffer[4096];
    ssize_t bytes_read;
    char *line = malloc(1);
    line[0] = '\0';

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        line = realloc(line, strlen(line) + bytes_read + 1);
        strcat(line, buffer);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    
    
    
    char **lines = ft_split(line, '\n');
    sanitize_map_lines(lines);
    
    int n = 0;
    int l = 0;
    while (lines[n])
    {
    	l = 0;
    	while (lines[n][l])
    	{
    		printf("%c", lines[n][l]);
    		l++;
    	}
    	printf("\n");
    	n++;
    }
    int i = 0;
    while (lines[i] && !first_line(lines[i])) {
        parse_line(vars, lines[i]);
        free(lines[i]);
        i++;
    }
    
    calculate_map_size(lines, &vars->map.width, &vars->map.height);
    pad_lines_with_spaces(lines, vars->map.width);
    int	k = 0;
    int	j = 0;
    
    while (lines[k])
    {
    	j = 0;
    	while (lines[k][j])
    	{
    		printf("%c", lines[k][j]);
    		j++;
    	}
    	printf("\n");
    	k++;
    }
    
    parse_map(lines, vars, i);

    if (!is_map_closed(vars)) {
        fprintf(stderr, "Error: Mapa não está cercado por paredes.\n");
        exit(EXIT_FAILURE);
    }

    while (lines[i]) {
        free(lines[i]);
        i++;
    }
    free(lines);
    free(line);
}

