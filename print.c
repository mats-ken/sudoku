/* テーブルの状態を表示 */
void        print_table(TABLE*t)
{
  int         i;

  for(i = 0; i < 9 * 9; i++){
    if(t[i].fixed)
      printf("%d", t[i].fixed);
    else
      printf(" ");

    if(0 == (i + 1) % 9)
      printf("\n");
    else if(0 == (i + 1) % 3)
      printf("|");
    else
      printf(" ");

    if(0 == (i + 1) % 27 && 80 != i)
      printf("-----+-----+-----\n");
  }
}

/* テーブルの状態を詳しく表示 */
void        print_table_detail(TABLE*t)
{
  int         i, j;

  for(i = 0; i < 9 * 9; i++){
    for(j = 0; j < 9; j++){
      if(t[i].flag[j])
        printf("%d", j + 1);
      else if(t[i].fixed)
        printf(" ");
      else
        printf("*");
    }

    if(0 == (i + 1) % 9)
      printf("\n");
    else if(0 == (i + 1) % 3)
      printf(" # ");
    else
      printf("|");

    if(0 == (i + 1) % 27 && 80 != i){
      for(j = 0; j < 9 * 9 + 8 + 4; j++)
        putchar('#');
      printf("\n");
    }
  }
}
