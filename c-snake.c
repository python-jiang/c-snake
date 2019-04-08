#include <stdio.h>
#include <windows.h>
#include <conio.h>
#define matsize 20

struct coor{
	int x, y;
};

int len;
char mat[matsize][matsize];
struct coor snake[matsize * matsize], tryhead, food;

void init(){
	int i, j;
	len = 7;
	for(i = 0, j = len - 1; j >= 0; i++, j--){
		snake[i].x = 9, snake[i].y = j;
	}
	for(i = 1; i < len; i++){
		mat[snake[i].x][snake[i].y] = '*';
	}
	mat[snake[0].x][snake[0].y] = 'O';
}

void zero(){
	int i, j;
	for(i = 0; i < matsize; i++){
		for(j = 0; j < matsize; j++){
			mat[i][j] = ' ';
		}
	}
}

int checkneck(){
	if((tryhead.x == snake[1].x) && (tryhead.y == snake[1].y))return 1;
	else return 0;
}

int checkwall(){
	if((tryhead.x < 0) || (tryhead.x >= matsize) || (tryhead.y < 0) || (tryhead.y >= matsize))return 1;
	else return 0;
}

int eatself(){
	int k, flag = 0;
	for(k = 3; k < len - 1; k++){
		if((tryhead.x == snake[k].x) && (tryhead.y == snake[k].y)){
			flag = 1;
			break;
		}
	}
	return flag;
}

void newfood(){
	food.x = (snake[0].x + 9) % matsize;
	food.y = (snake[0].y + 9) % matsize;
}

void update(){
	int k;
	if((tryhead.x == food.x) && (tryhead.y == food.y)){
		len++;
		for(k = len - 1; k; k--){
			snake[k].x = snake[k - 1].x;
			snake[k].y = snake[k - 1].y;
			mat[snake[k].x][snake[k].y] = '*';
		}
		newfood();
	}else{
		for(k = len - 1; k; k--){
			snake[k].x = snake[k - 1].x;
			snake[k].y = snake[k - 1].y;
			mat[snake[k].x][snake[k].y] = '*';
		}
	}
	snake[0].x = tryhead.x;
	snake[0].y = tryhead.y;
	mat[snake[0].x][snake[0].y] = 'O';
}

void showsnake(){
	int i, j;
	system("cls");
	mat[food.x][food.y] = 'F';
	for(i = 0; i < matsize; i++){
		for(j = 0; j < matsize; j++){
			printf(" %c", mat[i][j]);
		}
		printf("|\n");
	}
	for(i = 0; i < matsize * 2; i++){
		printf("-");
	}
	printf("|\n");
	zero();
}

int move(char direc){
	int flag = 1;
	if(direc == 'w'){
		tryhead.x = snake[0].x - 1;
		tryhead.y = snake[0].y;
	}else if(direc == 'a'){
		tryhead.x = snake[0].x;
		tryhead.y = snake[0].y - 1;
	}else if(direc == 's'){
		tryhead.x = snake[0].x + 1;
		tryhead.y = snake[0].y;
	}else if(direc == 'd'){
		tryhead.x = snake[0].x;
		tryhead.y = snake[0].y + 1;
	}else flag = 0;
	return flag;
}

void gameover(){
	printf("Game Over.\nYour score is %d.\n",len);
}

void main()
{
	char direction;
	init();
	newfood();
	showsnake();
	while(1){
		direction = _getch();
		if(move(direction)){
			if(checkneck())continue;
			else if(checkwall() || eatself())break;
			else{
				update();
				showsnake();
			}
		}else continue;
	}
	gameover();

	getchar();
}
