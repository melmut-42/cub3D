#ifndef ERROR_LOGS_H
# define ERROR_LOGS_H

// ====================== General Messages ======================

# define ERROR "Error"
# define BAR "====================================="


// ====================== Specific Messages ======================

# define GAME_ERR "Game initialization failed!"
# define FILE_ERR "Map file could not open!"
# define INV_EXT "Invalid map file extension! Expected .cub"
# define INV_DATA "Invalid data found in the map file!"
# define INV_RGB_VAL "Invalid RGB value in the map file!"
# define INV_MAP_ELEMENT "Invalid map element found in the map!"
# define LACK_TEXTURE "Lack of texture data in the map file!"
# define DUP_DATA "Duplicate data found in the map file!"
# define MAP_ACCESS_ERR "Map accessability is incorrect!"
# define EMPTY_MAP_ERR "Map does not exist in the file!"
# define MULTI_PLAYER "Multiple player found in the map!"
# define PLAYER_NOT_EXIST_ERR "Player does not exist in the file"

#endif