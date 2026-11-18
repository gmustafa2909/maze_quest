#include<stdio.h>
#define rows 9
# define cols 16
int gameRunning = 1;
char maze[rows][cols];
int playerRow = 1;
int playerCol = 1;
int playerScore = 0;
int collectedTreasure = 0;
int playerHealth = 100;
int hasKey = 0;
int currentLevel = 1;
void saveScore();
void loadLevel(int level){
  printf("\nCurrent Level: %d\n",level);
  for(int i = 0; i< rows; i++){
    for(int j = 0; j < cols; j++){
      maze[i][j] = '#';
    }
  }
  if(level == 1){
    char maze1[rows][cols] = {
      {"################"},
      {"#P..#........T.#"},
      {"#.#...#..T.....#"},
      {"#....X.####....#"},
      {"#.#.#....X....F#"},
      {"#T#T############"}
    };
    for(int i = 0; i < 6; i++){
      for(int j = 0; j < cols; j++){
        maze[i][j] = maze1[i][j];
      }
    }
  }
  else if(level == 2){
    char maze2[rows][cols] = {
      {"####T###########"},
      {"#P...#.....K...#"},
      {"###..#.#T......#"},
      {"#....T....X....#"},
      {"#..##.....######"},
      {"#.#....E..D...F#"},
      {"#.T#############"}
    };
    for(int i = 0; i < 7; i++){
      for(int j = 0; j < cols; j++){
        maze[i][j] = maze2[i][j];
      }
    }
  }
  else if(level == 3){
    char maze3[rows][cols] = {
      {"#############T##"},
      {"#P..#..T..E....#"},
      {"#...#..##......#"},
      {"#..T...X.......#"},
      {"#.#.##T#...K...#"},
      {"T.#.D.E#########"},
      {"###.#..T......F#"},
      {"###.T###########"}
    };
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < cols; j++){
        maze[i][j] = maze3[i][j];
      }
    }
  }
  else{
    printf("\nInvalid Level");
    return;
  }
  playerRow = 1;
  playerCol = 1;
  hasKey = 0;
  maze[playerRow][playerCol] = '.';
}
void displayMaze(){
  for(int i =0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(i == playerRow && j == playerCol){
        printf("P");
      }
      else{
        printf("%c",maze[i][j]);
      }
    }
    printf("\n");
  }
}
void movePlayer(){
  int newRow = playerRow;
  int newCol = playerCol;
  char movement;
  printf("\nEnter (w,a,s,d): ");
  scanf(" %c",&movement);
  if(movement == 'w'){
    newRow = playerRow -1;
  }
  else if(movement == 's'){
    newRow = playerRow + 1;
  }
  else if(movement == 'a'){
    newCol = playerCol - 1;
  }
  else if(movement == 'd'){
    newCol = playerCol + 1;
  }
  else{
    printf("\nInvalid movement!\n");
    return;
  }
  if(newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols){
    printf("\nInvalid movement!\n");
    return;
  }
  if(maze[newRow][newCol] == '#'){
    printf("\nYou cannot cross the wall!\n");
    return;
  }
  if(maze[newRow][newCol] == 'T'){
    collectedTreasure ++;
    playerScore += 10;
    maze[newRow][newCol] = '.';
  }
  if(maze[newRow][newCol] == 'X'){
    playerHealth -= 20;
    maze[newRow][newCol] = '.';
    printf("\nYou stepped on a trap! health decreases by 20\n");
  }
  if(maze[newRow][newCol] == 'E'){
    playerHealth -= 30;
    maze[newRow][newCol] = '.';
    printf("\nYou encountered an enemy! health decreases by 30\n");
  }
  if(maze[newRow][newCol] == 'K'){
    hasKey = 1;
    maze[newRow][newCol] = '.';
    printf("\nKey Collected\n");
  }
  if(maze[newRow][newCol] == 'D'){
    if(hasKey == 1){
      maze[newRow][newCol] = '.';
      hasKey = 0;
      printf("\nDoor Unlocked\n");
    }else{
      printf("\nYou need a key to unlock door!\n");
      return;
    }
  }
  if(maze[newRow][newCol] == 'F'){
    printf("\nLevel Completed\n");
    currentLevel ++;
    if(currentLevel > 3){
      printf("\nCongratulations! You have completed MazeQuest\n");
      gameRunning = 0;
      saveScore();
      return;
    }
    loadLevel(currentLevel);
    return;
  }
  playerRow = newRow;
  playerCol = newCol;
}
void saveScore(){
  FILE *fp;
  fp = fopen("highscores.txt","a");
  if(fp == NULL){
    printf("\nFile could not be opened!");
    return;
  }else{
    fprintf(fp,"%d\n",playerScore);
    fclose(fp);
  }
}
void displayHighScores(){
  FILE *fp;
  int temp;
  fp = fopen("highscores.txt","r");
  if(fp == NULL){
    printf("\nNo high scores available yet!");
    return;
  }else{
    int score[100];
    int count = 0;
    while(count < 100 && fscanf(fp, "%d", &score[count]) == 1){
      count ++;
    }
    if(count == 0){
    printf("\nNo scores have been saved yet!");
    fclose(fp);
    return;
    }
    else{
      for(int i = 0; i < count - 1; i++){
        for(int j = 0 ; j < count - i - 1; j++){
          if(score[j] < score[j+1]){
            temp = score[j];
            score[j] = score[j+1];
            score[j+1] = temp;
          }
        }
      }
      for(int i = 0; i < count && i < 5; i++){
        printf("\n%d. %d",i+1,score[i]);
      }
      fclose(fp);
    }
  }
}
int main(){
  int choice = 0;
  int playerLives = 3;
  printf("WELCOME TO MAZEQUEST");
  while(choice !=4){
    printf("\n1-Start Game");
    printf("\n2-Instructions");
    printf("\n3-High Scores");
    printf("\n4-Exit");
    printf("\nEnter choice: ");
    scanf("%d",&choice);
    switch(choice){
      case 1:
      if(gameRunning == 0){
      printf("\nGame has already ended. Please restart the program.");
      break;
      }
      loadLevel(currentLevel);
      while(gameRunning){
        displayMaze();
        printf("\nScore: %d", playerScore);
        printf("\nTreasures Collected: %d",collectedTreasure);
        printf("\nPlayer Health: %d",playerHealth);
        printf("\nPlayer Lives: %d\n",playerLives);
        movePlayer();
        if(playerHealth <= 0){
          playerLives --;
          if(playerLives > 0){
            playerHealth = 100;
            continue;
          }
          else{
            printf("\nGame Over!");
            printf("\nFinal Score: %d", playerScore);
            gameRunning = 0;
            saveScore();
            break;
          }
        }
      }
      break;
      case 2:
      printf("\n==========Instructions Menu==========");
      printf("\n1.Use W to move up.");
      printf("\n2.Use S to move down.");
      printf("\n3.Use A to move left.");
      printf("\n4.Use D to move right.");
      printf("\n5.Collect treasures(T) to earn 10 points.");
      printf("\n6.Avoid traps(X) and enemies(E).");
      printf("\n7.Collect keys(K) to unlock doors(D)");
      printf("\n8.Reach exit F to complete a level.");
      printf("\n====================================\n");
      break;
      case 3:
      printf("\n========== TOP 5 HIGH SCORES ==========\n");
      displayHighScores();
      printf("\n=======================================\n");
      break;
      case 4:
      printf("\nYou are exiting the game");
      break;
      default:
      printf("\nInvalid");
      break;
    }
  }
  return 0;
}