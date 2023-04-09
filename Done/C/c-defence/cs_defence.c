#include <stdio.h>

#define MAP_ROWS 6
#define MAP_COLUMNS 12
#define TOTAL_BLOCKS 72

enum land_type {
    GRASS,
    WATER,
    PATH_START,
    PATH_END,
    PATH_UP,
    PATH_RIGHT,
    PATH_DOWN,
    PATH_LEFT,
    TELEPORTER
};

enum entity {
    EMPTY,
    ENEMY,
    BASIC_TOWER,
    POWER_TOWER,
    FORTIFIED_TOWER,
};
typedef struct point{
    int x;
    int y;
}Point;

typedef struct lake
{
    int row;
    int column;
    int height;
    int width;
}Lake;

struct tile {
    enum land_type land;
    enum entity entity;

    int n_enemies;
};

void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]);
void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS], int lives, int money);
void print_tile(struct tile tile, int entity_print);
int is_valid(int row,int column,int height,int width);
void add_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS],int row,int col,int enemies);
int make_path(struct tile map[MAP_ROWS][MAP_COLUMNS],Point start_point,Point end_point,Point path[TOTAL_BLOCKS],int size_path);
int is_possible(struct tile map[MAP_ROWS][MAP_COLUMNS],int row,int col);
int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS],Point path[TOTAL_BLOCKS],int n,int move,int starting_lives);
int is_possible_to_upgrade(struct tile map[MAP_ROWS][MAP_COLUMNS],int row,int col,int starting_money);
int kill_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS],Point tower[TOTAL_BLOCKS],int n,int kill_time);
int helper(struct tile map[MAP_ROWS][MAP_COLUMNS],int x,int y,int r,int power);
void rain(struct tile map[MAP_ROWS][MAP_COLUMNS],int row_spacing,int col_spacing,int row_offset,int col_offset);
int helper_water(struct tile map[MAP_ROWS][MAP_COLUMNS],Point water[TOTAL_BLOCKS],int count);
int helper_flooding(struct tile map[MAP_ROWS][MAP_COLUMNS],Point water[TOTAL_BLOCKS],int count);


int main(void) {

    struct tile map[MAP_ROWS][MAP_COLUMNS];
    initialise_map(map);

    // 1.1
    int starting_lives,starting_money;
    printf("Starting Lives: ");
    scanf("%d",&starting_lives);
    printf("Starting Money($): ");
    scanf("%d",&starting_money);

    Point start_point,end_point;
    printf("Start Point: ");
    scanf("%d %d",&start_point.x,&start_point.y);
    printf("End Point: ");
    scanf("%d %d",&end_point.x,&end_point.y);

    map[start_point.x][start_point.y].land = PATH_START;
    map[end_point.x][end_point.y].land = PATH_END;
    print_map(map,starting_lives,starting_money);

    // 1.2
    int num;
    printf("Initial Enemies: ");
    scanf("%d",&num);

    add_enemies(map,start_point.x,start_point.y,num);
    print_map(map,starting_lives,starting_money);

    // 1.3
    Lake lake;
    printf("Enter Lake: ");
    scanf("%d %d %d %d",&lake.row,&lake.column,&lake.height,&lake.width);

    if(is_valid(lake.row,lake.column,lake.height,lake.width))
    {
        for(int i=lake.row;i<(lake.row+lake.height);i++)
        {
            for(int j=lake.column;j<(lake.column+lake.width);j++)
            {
                map[i][j].land = WATER;
            }
        }
    }
    print_map(map,starting_lives,starting_money);


    Point tower[TOTAL_BLOCKS];
    int number_of_tower = 0;

    Point path[TOTAL_BLOCKS];
    path[0] = start_point;

    // 2.1
    int size_path = make_path(map,start_point,end_point,path,1);
    print_map(map,starting_lives,starting_money);

    while(1)
    {
        getchar();

        printf("Enter Command: ");
        char input;
        int n = scanf("%c",&input);

        if(n==-1)break;
        else if(input=='e')
        {
            int num1;
            scanf("%d",&num1);
            add_enemies(map,start_point.x,start_point.y,num1);
            print_map(map,starting_lives,starting_money);
        }
        else if(input=='t')
        {
            int row,col;
            scanf("%d %d",&row,&col);

            tower[number_of_tower].x = row;
            tower[number_of_tower].y = col;

            number_of_tower++;
            if(starting_money>=200 && is_possible(map,row,col))
            {
                starting_money = starting_money-200;
                map[row][col].entity = BASIC_TOWER;
            }
            else
            {
                printf("Error: Tower creation unsuccessful. Make sure you have at least $200 and that the tower is placed on a grass block with no entity.\n");
            }
            print_map(map,starting_lives,starting_money);
        }
        // 3.1
        else if(input=='m')
        {
            int number_of_steps;
            scanf("%d",&number_of_steps);

            int count = move_enemies(map,path,size_path,number_of_steps,starting_lives);

            if(count==-1)
            {
                printf("Oh no, you ran out of lives!");
                break;
            }
          
            starting_lives = starting_lives-count;
            print_map(map,starting_lives,starting_money);
            if(starting_lives<=0)
            {
                printf("Oh no, you ran out of lives!");
                break;
            }
        }
        // 3.2
        else if(input=='u')
        {
            int row1,col1;
            scanf("%d %d",&row1,&col1);
            
            if(is_possible_to_upgrade(map,row1,col1,starting_money))
            {
                if(map[row1][col1].entity==BASIC_TOWER)
                {
                    map[row1][col1].entity = POWER_TOWER;
                    starting_money = starting_money - 300;
                }
                else if(map[row1][col1].entity==POWER_TOWER)
                {
                    map[row1][col1].entity = FORTIFIED_TOWER;
                    starting_money = starting_money - 500;
                }
                printf("Upgrade Successful!\n");
            }
                print_map(map,starting_lives,starting_money);
        }
        // 3.3
        else if(input=='a')
        {
            int kill_time;
            scanf("%d",&kill_time);

            int total_enemies_killed = kill_enemies(map,tower,number_of_tower,kill_time);
            printf("%d enemies destroyed!\n",total_enemies_killed);

            starting_money = starting_money + (5*total_enemies_killed);
            print_map(map,starting_lives,starting_money);
        }
        // 3.4
        else if(input=='r')
        {
            int row_spacing,col_spacing,row_offset,col_offset;
            scanf("%d %d %d %d",&row_spacing,&col_spacing,&row_offset,&col_offset);

            rain(map,row_spacing,col_spacing,row_offset,col_offset);
            print_map(map,starting_lives,starting_money);
        }
        
    }
    printf("\nGame Over!\n");
}

int is_valid(int row,int column,int height,int width)
{
    if(row<0 || (row+height-1)>=MAP_ROWS)
    {
        printf("Error: Lake out of bounds, ignoring...\n");
        return 0;
    }
    if(column<0 || (column+width-1)>=MAP_COLUMNS)
    {
        printf("Error: Lake out of bounds, ignoring...\n");
        return 0;
    }
    return 1;
}

void add_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS],int row,int col,int enemies)
{
    int total_enemies = map[row][col].n_enemies+enemies;
    if(total_enemies>0)
    {
        map[row][col].entity = ENEMY;
        map[row][col].n_enemies = total_enemies;
    }
}

int make_path(struct tile map[MAP_ROWS][MAP_COLUMNS],Point start_point,Point end_point,Point path[TOTAL_BLOCKS],int size_path)
{
    printf("Enter Path: ");
    
    int x = start_point.x;
    int y = start_point.y;

     while(1)
    {
        char input;
        if(x==end_point.x && y==end_point.y)break;
        scanf(" %c",&input);
        if(input=='u')
        {
            map[x][y].land = PATH_UP;
            x--;
        }
        else if(input=='d')
        {
            map[x][y].land = PATH_DOWN;
            x++;
        }
        else if(input=='l')
        {
            map[x][y].land = PATH_LEFT;
            y--;
        }
        else if(input=='r')
        {
            map[x][y].land = PATH_RIGHT;
            y++;
        }

        path[size_path].x = x;
        path[size_path].y = y;

        size_path++;
    }
    return size_path;
}

int is_possible(struct tile map[MAP_ROWS][MAP_COLUMNS],int row,int col)
{
    if(row>=0 && row<MAP_ROWS && col>=0 && col<MAP_COLUMNS)
    {
        if(map[row][col].entity==EMPTY && map[row][col].land==GRASS)
        {
            printf("Tower successfully created!\n");
            return 1;
        }
    }
    return 0;
}


int move_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS],Point path[TOTAL_BLOCKS],int n,int move,int starting_lives)
{
    n = n-1;
    
    int temp[TOTAL_BLOCKS];
    for(int i=0;i<n;i++)
    {
        int row = path[i].x;
        int col = path[i].y;
        if(map[row][col].entity==ENEMY) temp[i]=1;
        else temp[i]=0;
    }
    
    int count = 0;
    for(int i=n-1;i>=0;i--)
    {
        int row = path[i].x;
        int col = path[i].y;
        if(temp[i])
        {
            int steps = move+i;
            
            if(steps>=n)
            {
                if(starting_lives>0)
                {
                    starting_lives = starting_lives-map[row][col].n_enemies;
                    map[row][col].entity = EMPTY;
                    count = count + map[row][col].n_enemies;
                    map[row][col].n_enemies = 0;
                }
                else return -1;
            }
            else
            {
                int new_row = path[steps].x;
                int new_col = path[steps].y;
                map[new_row][new_col].entity = ENEMY;
                map[new_row][new_col].n_enemies = map[row][col].n_enemies;
                map[row][col].entity = EMPTY;
                map[row][col].n_enemies = 0;
            }
        }
    }
    printf("%d enemies reached the end!\n",count);
    return count;
}


int is_possible_to_upgrade(struct tile map[MAP_ROWS][MAP_COLUMNS],int row,int col,int starting_money)
{
    if(row<0 || row>=MAP_ROWS || col<0 || col>=MAP_COLUMNS)
        {
            printf("Error: Upgrade target is out-of-bounds.\n");
            return 0;
        }
    if(map[row][col].entity!=BASIC_TOWER && map[row][col].entity!=POWER_TOWER && map[row][col].entity!=FORTIFIED_TOWER)
        {
            printf("Error: Upgrade target contains no tower entity.\n");
            return 0;
        }
    if(map[row][col].entity==FORTIFIED_TOWER)
        {
            printf("Error: Tower cannot be upgraded further.\n");
            return 0;
        }
    if(map[row][col].entity==BASIC_TOWER && starting_money<300)
        {
            printf("Error: Insufficient Funds.\n");
            return 0;
        }
    if(map[row][col].entity==POWER_TOWER && starting_money<500)
        {
            printf("Error: Insufficient Funds.\n");
            return 0;
        }
    return 1;
}


int kill_enemies(struct tile map[MAP_ROWS][MAP_COLUMNS],Point tower[TOTAL_BLOCKS],int n,int kill_time)
{
    int kill = 0;
    
    while(kill_time--)
    {
        for(int i=0;i<n;i++)
        {
            int x = tower[i].x;
            int y = tower[i].y;

            if(map[x][y].entity==BASIC_TOWER || map[x][y].entity==POWER_TOWER)
            {
                int power = 1;
                if(map[x][y].entity==POWER_TOWER)power = 2;
                
                kill = kill + helper(map,x,y,1,power);
            }
            else
            {
                kill = kill + helper(map,x,y,2,3);
            }
        }
    }
    return kill;
}

int helper(struct tile map[MAP_ROWS][MAP_COLUMNS],int x,int y,int r,int power)
{
    int kill_count = 0;

    int left = 0;
    if((y-r)>0)left = y-r;

    int right = MAP_COLUMNS-1;
    if((y+r)<right)right = y+r;

    int top = 0;
    if((x-r)>0)top = x-r;

    int bottom = MAP_ROWS-1;
    if((x+r)<bottom)bottom = x+r;

    for(int j=top;j<=bottom;j++)
    {
        for(int k=left;k<=right;k++)
        {
            if(map[j][k].entity==ENEMY)
            {
                int remaining_enemies = map[j][k].n_enemies-power;
                if(remaining_enemies<=0)
                {
                    kill_count = kill_count + map[j][k].n_enemies;
                    map[j][k].entity = EMPTY;
                    map[j][k].n_enemies = 0;
                }
                else
                {
                    kill_count = kill_count + power;
                    map[j][k].n_enemies = map[j][k].n_enemies-power;
                }
            }
        }
    }
    return kill_count;
}

void rain(struct tile map[MAP_ROWS][MAP_COLUMNS],int row_spacing,int col_spacing,int row_offset,int col_offset)
{
    row_offset = row_offset%row_spacing;
    if(row_offset<0) row_offset = row_offset+row_spacing;

    col_offset = col_offset%col_spacing;
    if(col_offset<0) col_offset = col_offset + col_spacing;

    for(int i = row_offset;i<MAP_ROWS;i+=row_spacing)
    {
        for(int j=col_offset;j<MAP_COLUMNS;j+=col_spacing)
        {
            if(map[i][j].land==GRASS)map[i][j].land = WATER;
            if(map[i][j].entity==BASIC_TOWER || map[i][j].entity==POWER_TOWER)
            {
                map[i][j].entity=EMPTY;
            }
        }
    }
}

// it is used to store the locations of the water tile in the map and store inside 'water' array
int helper_water(struct tile map[MAP_ROWS][MAP_COLUMNS],Point water[TOTAL_BLOCKS],int count)
{
            for(int i=0;i<MAP_ROWS;i++)
        {
            for(int j=0;j<MAP_COLUMNS;j++)
            {
                if(map[i][j].land==WATER)
                {
                    water[count].x = i;
                    water[count].y = j;
                    count++;
                }
            }
        }
        return count;
}

// it is the helper function to expand the water from water tile
int helper_flooding(struct tile map[MAP_ROWS][MAP_COLUMNS],Point water[TOTAL_BLOCKS],int count)
{
    // water can expand in four directions
    // for example .. water is present on (i,j) tile
    // for left : (i,j-1)
    // for right: (i.j+1)
    // for up   : (i-1,j)
    // for down : (i+1,j)
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    int temp = count;
    for(int i=0;i<temp;i++)
    {
        int row = water[i].x;
        int col = water[i].y;
        for(int j = 0;j<4;j++)
        {
            int new_row = row + dx[j];
            int new_col = col + dy[j];
            // check the new point should not be out of bounds of the map
            if(new_row>=0 && new_row<MAP_ROWS && new_col>=0 && new_col<MAP_COLUMNS)
            {
                if(map[new_row][new_col].land==GRASS)
                {
                    map[new_row][new_col].land = WATER;
                    water[count].x = new_row;
                    water[count].y = new_col;
                    count++;
                }
                if(map[new_row][new_col].entity==BASIC_TOWER || map[new_row][new_col].entity==POWER_TOWER)
                {
                    map[new_row][new_col].entity=EMPTY;
                }
            }
        }
    }
    return count;
}

void initialise_map(struct tile map[MAP_ROWS][MAP_COLUMNS]) {
    for (int row = 0; row < MAP_ROWS; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            map[row][col].land = GRASS;
            map[row][col].entity = EMPTY;
            map[row][col].n_enemies = 0;
        }
    }
}

void print_map(struct tile map[MAP_ROWS][MAP_COLUMNS],int lives, int money) {
    printf("\nLives: %d Money: $%d\n", lives, money);
    for (int row = 0; row < MAP_ROWS * 2; ++row) {
        for (int col = 0; col < MAP_COLUMNS; ++col) {
            print_tile(map[row / 2][col], row % 2);
        }
        printf("\n");
    }
}

void print_tile(struct tile tile, int land_print) {
    if (land_print) {
        if (tile.land == GRASS) {
            printf(" . ");
        } else if (tile.land == WATER) {
            printf(" ~ ");
        } else if (tile.land == PATH_START) {
            printf(" S ");
        } else if (tile.land == PATH_END) {
            printf(" E ");
        } else if (tile.land == PATH_UP) {
            printf(" ^ ");
        } else if (tile.land == PATH_RIGHT) {
            printf(" > ");
        } else if (tile.land == PATH_DOWN) {
            printf(" v ");
        } else if (tile.land == PATH_LEFT) {
            printf(" < ");
        } else if (tile.land == TELEPORTER) {
            printf("( )");
        } else {
            printf(" ? ");
        }
    } else {
        if (tile.entity == EMPTY) {
            printf("   ");
        } else if (tile.entity == ENEMY) {
            printf("%03d", tile.n_enemies);
        } else if (tile.entity == BASIC_TOWER) {
            printf("[B]");
        } else if (tile.entity == POWER_TOWER) {
            printf("[P]");
        } else if (tile.entity == FORTIFIED_TOWER) {
            printf("[F]");
        } else {
            printf(" ? ");
        }
    }
}
