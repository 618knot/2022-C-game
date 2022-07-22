#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#define DOT 0
#define PLAYER 1
#define GOAL 2
#define UP 3
#define DOWN 4
#define LEFT 5
#define RIGHT 6

struct Player{
    int x;
    int y;
};

struct Key{
    char keyChar;
    int keyCode;
};

void view(int field[10][10]);
void outColorString(char *, char *);
void controlPlayer(struct Player *, int);
void setKey(struct Key *);
void setDirection(int directionKeys[4]);
int inputDirection(struct Key *, int directionKeys[4]);

int main(){
    srand(time(NULL));

    //Playerの初期位置の設定
    struct Player player = {0, 9};
    struct Player *control;
    control = &player;

    //ASCIIコードと文字の設定
    struct Key Key[26];
    setKey(Key);

    //初期位置の設定
    int field[10][10] = {DOT};
    field[9][0] = GOAL;
    field[player.x][player.y] = PLAYER;

    //初期状態の表示
    view(field);

    int tmp;
    int errorStatus = 0;
    int directionKeys[4];
    while(1){
        //上下左右のキーの決定と表示
        setDirection(directionKeys);
        printf("    %c    \n\n%c       %c\n\n    %c    \n", Key[directionKeys[0]].keyChar, Key[directionKeys[1]].keyChar, Key[directionKeys[2]].keyChar, Key[directionKeys[3]].keyChar);
        
        //PLAYERの移動
        field[player.x][player.y] = DOT; //もといた場所はDOTに
        controlPlayer(control, inputDirection(Key, directionKeys)); //PLAYERの移動方向の取得と移動先の指定
        field[player.x][player.y] = PLAYER;//移動完了

        //移動後の画面を表示
        system("cls");//コンソールのクリア
        view(field);
    }

    return 0;
}

void view(int field[10][10]){
    for(int j = 0; j < 10; j++){
        for(int i = 0; i < 10; i++){
            if(field[i][j] == DOT){
                printf(". ");
            }else if(field[i][j] == PLAYER){
                outColorString("\x1b[31m", "P ");
            }else if(field[i][j] == GOAL){
                outColorString("\x1b[32m", "G ");
            }
        }
        printf("\n");
    }
}

void outColorString(char *color, char *string){
    printf("%s", color);
    printf("%s", string);
    printf("\x1b[0m");
}

void controlPlayer(struct Player *player, int direction){

    if(direction == UP && player -> y > 0) player -> y--;
    else if(direction == DOWN &&  player -> y < 9) player -> y++;
    else if(direction == RIGHT && player -> x < 9) player -> x++;
    else if(direction == LEFT && player -> x > 0) player -> x--;
}

void setKey(struct Key *Key){
    for(int i = 0; i < 26; i++){    //97~122 = a~z
        Key[i].keyCode = i + 97;
    }

    int index = 0;
    for(char i = 'a'; i <= 'z'; i++){
        Key[index].keyChar = i;
        index++;
    }

    return;
}

void setDirection(int directionKeys[4]){
    for(int i = 0; i < 4; i++){
        directionKeys[i] = rand() % 26;
    }

    for(int i = 0; i < 4; i++){
        for(int j = i + 1; j < 4; j++){
            if(directionKeys[i] == directionKeys[j]) setDirection(directionKeys); //被ってたらやり直し
        }
    }
}

int inputDirection(struct Key *Key, int directionKeys[4]){
    int tmp = _getch();
        if(tmp == Key[directionKeys[0]].keyCode) return UP;
        else if(tmp == Key[directionKeys[1]].keyCode) return LEFT;
        else if(tmp == Key[directionKeys[2]].keyCode) return RIGHT;
        else if(tmp == Key[directionKeys[3]].keyCode) return DOWN;
        else inputDirection(Key, directionKeys); //該当がなければやり直し
}